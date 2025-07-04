#include "core/le3_scene.h"
using namespace le3;

#include <fstream>
#include <sstream>
#include <stdexcept>

#ifdef __linux__
#include <GL/glew.h>
#else
#include <gl/glew.h>
#endif

#include <fmt/core.h>

#include "core/le3_engine_systems.h"
#include "scripting/le3_serialization.h"

void LE3Scene::init(int width, int height) {
    m_sceneGraph = std::make_shared<LE3SceneGraph>();
    m_sceneGraph->m_pRoot = std::make_shared<LE3SceneRoot>();
    m_sceneGraph->m_pRootObj = std::dynamic_pointer_cast<LE3Object>(m_sceneGraph->m_pRoot);
    m_pMainCamera = nullptr;
    resize(width, height);
    m_bInspected = false;

    // Load post process shader
    m_postProcessShader = LE3GetAssetManager().getShader(DEFAULT_POSTPROCESS_SHADER);
}
void LE3Scene::init_inspector(int width, int height, LE3Scene& original) {
    init(width, height);
    m_sceneGraph = original.m_sceneGraph;
    m_bInspected = true;
}
void LE3Scene::reset() {
    m_sceneGraph->m_pObjects.clear();
    init(m_width, m_height);
}

void LE3Scene::load(std::string path) {
    LE3GetScriptSystem().doFile(path); // Load "Scene" variable

    // In lua:
    //  >>  load_LE3Scene(this, Scene)
    LE3GetScriptSystem().getGlobal("load_LE3Scene");
    LE3GetScriptSystem().pushUserType<LE3Scene>(this);
    LE3GetScriptSystem().getGlobal("Scene");
    LE3GetScriptSystem().callFunction(2, 0);
}

void LE3Scene::save(std::string path, bool shared) {
    LE3GetScriptSystem().getGlobal("save_LE3Scene");
    LE3GetScriptSystem().pushUserType<LE3Scene>(this);
    LE3GetScriptSystem().pushBool(shared);
    LE3GetScriptSystem().callFunction(2, 1);
    LE3GetScriptSystem().pop(1); // Anyway there is a global variable "Scene"
    LE3Serialization::dump("Scene", path);
}


void LE3Scene::resize(int width, int height)
{
    m_width = width; m_height = height;
    m_rawBuffer = std::make_shared<LE3Framebuffer>(m_width, m_height, LE3FramebufferType::LE3_FRAMEBUFFER_COLOR_DEPTH_STENCIL, true);
    m_objectIdsBuffer = std::make_shared<LE3Framebuffer>(m_width, m_height, LE3FramebufferType::LE3_FRAMEBUFFER_COLOR_DEPTH_STENCIL, true);
    m_selectedObjectsBuffer = std::make_shared<LE3Framebuffer>(m_width, m_height, LE3FramebufferType::LE3_FRAMEBUFFER_COLOR_DEPTH_STENCIL, true);
    m_postProcessBuffer = std::make_shared<LE3Framebuffer>(m_width, m_height, LE3FramebufferType::LE3_FRAMEBUFFER_COLOR_DEPTH_STENCIL, true);
    if (m_pMainCamera) {
        m_pMainCamera->setAspectRatio((float)m_width / (float)m_height);
    }
}


void LE3Scene::update(float deltaTime) {
    if (LE3GetEditorManager().isPauseSceneUpdates()) return;
    LE3GetSceneManager().setActiveScene(m_name);
    if (!m_bInspected) m_sceneGraph->m_pRoot->update(deltaTime);
    else for (auto obj : m_sceneGraph->m_inspectedUpdate)
        if (auto pObject = obj.lock()) pObject->update(deltaTime);
}

void LE3Scene::preUpdate() {
    LE3GetSceneManager().setActiveScene(m_name);
    m_sceneGraph->m_pRoot->preUpdate();
}

void LE3Scene::postUpdate() {
    LE3GetSceneManager().setActiveScene(m_name);
    m_sceneGraph->m_pRoot->postUpdate();
}

void LE3Scene::draw() {
    LE3GetSceneManager().setActiveScene(m_name);

    // Draw the scene once for each shadowmap
    drawLights();
    // Draw the scene, but only rendering object IDs
    drawObjectIDs();
    updateHoveredObject();
    drawSelected();

    // Draw the scene as is
    // Also, one of the objects might try to do visual debug, so set the active camera
    LE3GetVisualDebug().setActiveCamera(m_pMainCamera);
    drawObjects();
    if (LE3GetEngineDebug().g_bShowColliders) drawColliders();
    if (drawDebug) drawDebug();
    LE3GetVisualDebug().setActiveCamera(nullptr);

    // Draw once again to the post process buffer
    drawPostProcess();

    // Revert back to normal drawing
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void LE3Scene::drawLights() {
    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT); // Solve Peter-Panning
    GLuint shadowMapIdx = SHADOW_MAP_INDEX;
    glm::vec3 cameraPos = m_pMainCamera->getWorldMatrix()[3];
    std::shared_ptr<LE3Shader> shadowmapShader = LE3GetAssetManager().getShader(DEFAULT_SHADOWMAP_SHADER).lock();
    for (auto lightWeak : m_sceneGraph->m_lightManager.getDirectionalLights()) {
        auto light = lightWeak.lock();
        if (!light) continue;
        if (!light->getShadowMap()) continue;
        shadowmapShader->use();
        shadowmapShader->uniform("lightMatrix", light->getViewMatrix(cameraPos));
        drawObjects(shadowmapShader, light->getShadowMap(), true, true);
        light->getShadowMap()->setBindIdx(shadowMapIdx++);
    }
    for (auto lightWeak : m_sceneGraph->m_lightManager.getSpotLights()) {
        auto light = lightWeak.lock();
        if (!light) continue;
        if (!light->getShadowMap()) continue;
        shadowmapShader->use();
        shadowmapShader->uniform("lightMatrix", light->getViewMatrix());
        drawObjects(shadowmapShader, light->getShadowMap(), true, true);
        light->getShadowMap()->setBindIdx(shadowMapIdx++);
    }
    glCullFace(GL_BACK); 
    glDisable(GL_CULL_FACE);
}

void LE3Scene::drawObjects(LE3ShaderPtr shaderOverride, LE3FramebufferPtr buffer, bool depth, bool shadowPhase) {
    if (buffer == nullptr) buffer = m_rawBuffer;
    
    if (m_bCulling) glEnable(GL_CULL_FACE); else glDisable(GL_CULL_FACE);

    buffer->bind();
    glClearColor(m_backgroundColor.r, m_backgroundColor.g, m_backgroundColor.b, 1.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    glViewport(0, 0, buffer->getWidth(), buffer->getHeight());
    if (depth) glEnable(GL_DEPTH_TEST); else glDisable(GL_DEPTH_TEST);

    if (!shaderOverride.lock()) for (auto kv : LE3GetAssetManager().getShaders()) {
        applyMainCamera(kv.second);
        m_sceneGraph->m_lightManager.renderLights(kv.second, glm::vec3(m_pMainCamera->getWorldMatrix()[3]));
    }
    else { 
        applyMainCamera(shaderOverride);
        m_sceneGraph->m_lightManager.renderLights(shaderOverride, glm::vec3(m_pMainCamera->getWorldMatrix()[3]));
    }
    m_sceneGraph->m_drawQueue.draw(shaderOverride, shadowPhase);
}

void LE3Scene::drawObjectIDs() {
    uint32_t drawID = 1;
    // TODO: Update object IDs rarely
    for (auto kv : m_sceneGraph->m_pObjects) {
        if (auto drawableObj = std::dynamic_pointer_cast<LE3DrawableObject>(kv.second)) drawableObj->setDrawID(drawID);
        drawID++;
    }
    glm::vec3 bacgroundColor = getBackgroundColor();
    setBackgroundColor(glm::vec3(0.f));
    drawObjects(LE3GetAssetManager().getShader(DEFAULT_OBJECTID_SHADER), m_objectIdsBuffer, true, false);
    setBackgroundColor(bacgroundColor);
}

void LE3Scene::drawSelected() {
    // Set all non-selected objects to be hidden (but store original hidden value)
    std::map<std::string, bool> hiddenValues;
    for (auto kv : m_sceneGraph->m_pObjects) {
        if (auto drawableObj = std::dynamic_pointer_cast<LE3DrawableObject>(kv.second)) {
            hiddenValues[kv.first] = drawableObj->isHidden();
            drawableObj->setHidden(!drawableObj->isSelected());
        }
    }

    glm::vec3 bacgroundColor = getBackgroundColor();
    setBackgroundColor(glm::vec3(0.f));
    drawObjects(LE3GetAssetManager().getShader(DEFAULT_OBJECTID_SHADER), m_selectedObjectsBuffer, true, false);
    setBackgroundColor(bacgroundColor);

    // Restore original hidden values
    for (auto kv : m_sceneGraph->m_pObjects) {
        if (auto drawableObj = std::dynamic_pointer_cast<LE3DrawableObject>(kv.second)) {
            drawableObj->setHidden(hiddenValues[kv.first]);
        }
    }
}

void LE3Scene::drawPostProcess() {
    if (!m_postProcessShader.lock()) return;
    
    if (m_bRenderDirectly) glBindFramebuffer(GL_FRAMEBUFFER, 0);
    else m_postProcessBuffer->bind();
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); 
    glClear(GL_COLOR_BUFFER_BIT);
    glDisable(GL_DEPTH_TEST);
    glViewport(0, 0, m_postProcessBuffer->getWidth(), m_postProcessBuffer->getHeight());

    m_postProcessShader.lock()->use();

    m_rawBuffer->useColorTexture();
    m_postProcessShader.lock()->uniform("screenTexture", (unsigned int)0);
    m_objectIdsBuffer->useColorTexture(1);
    m_postProcessShader.lock()->uniform("objectIdTexture", (unsigned int)1);
    m_selectedObjectsBuffer->useColorTexture(2);
    m_postProcessShader.lock()->uniform("selectedTexture", (unsigned int)2);

    if (postProcessUniforms) postProcessUniforms(m_postProcessShader.lock());

    LE3GetAssetManager().getScreenRect()->draw();
}

void LE3Scene::drawColliders() {
    glDisable(GL_DEPTH_TEST);
    for (auto kv : m_sceneGraph->m_pObjects) {
        LE3ObjectPtr obj = kv.second; if (!obj) continue;
        if (!obj->getPhysicsComponent().isEnabled()) continue;
        LE3ColliderInfo colliderInfo = obj->getPhysicsComponent().getColliderInfo();

        glm::vec3 color(0.f, 1.f, 0.f);

        if (colliderInfo.colliderType == LE3ColliderType::LE3ColliderType_Box) {
            glm::mat4 localMatrix = glm::translate(colliderInfo.centroid) * glm::scale(colliderInfo.extent);
            LE3GetVisualDebug().drawDebugBox(obj->getWorldMatrix() * localMatrix, color);
        }
        else if (colliderInfo.colliderType == LE3ColliderType::LE3ColliderType_Sphere) {
            glm::mat4 localMatrix = glm::translate(colliderInfo.centroid) * glm::scale(glm::vec3(colliderInfo.radius));
            LE3GetVisualDebug().drawDebugSphere(obj->getWorldMatrix() * localMatrix, color);
        }
        else if (colliderInfo.colliderType == LE3ColliderType::LE3ColliderType_Cone) {
            float radius = 0.5f * (colliderInfo.extent.x > colliderInfo.extent.z ? colliderInfo.extent.x : colliderInfo.extent.z);
            glm::mat4 localMatrix = glm::scale(glm::vec3(radius, colliderInfo.extent.y, radius));
            LE3GetVisualDebug().drawDebugCone(obj->getWorldMatrix() * localMatrix, color);
        }
        else if (colliderInfo.colliderType == LE3ColliderType::LE3ColliderType_Cylinder) {
            float radius = 0.5f * (colliderInfo.extent.x > colliderInfo.extent.z ? colliderInfo.extent.x : colliderInfo.extent.z);
            glm::mat4 localMatrix = glm::scale(glm::vec3(radius, colliderInfo.extent.y, radius));
            LE3GetVisualDebug().drawDebugCylinder(obj->getWorldMatrix() * localMatrix, color);
        }
        else if (colliderInfo.colliderType == LE3ColliderType::LE3ColliderType_Capsule) {
            float radius = 2.f * (colliderInfo.extent.x > colliderInfo.extent.z ? colliderInfo.extent.x : colliderInfo.extent.z);
            glm::mat4 localMatrix = glm::scale(glm::vec3(radius, colliderInfo.extent.y, radius));
            LE3GetVisualDebug().drawDebugCapsule(obj->getWorldMatrix() * localMatrix, color);
        }
        else if (colliderInfo.colliderType == LE3ColliderType::LE3ColliderType_ConvexHull) {
            glm::vec3 centroid = colliderInfo.centroid * obj->getTransform().getScale();
            glm::mat4 model = obj->getTransform().getTransformMatrixNoScale() * glm::translate(centroid);
            LE3GetVisualDebug().drawDebugMesh(obj->getPhysicsComponent().getHullDebugMesh(), model, color);
        }
    }
    glEnable(GL_DEPTH_TEST);
}

// -----------

void LE3Scene::addEmptyObject(std::string name, std::string parent) {
    LE3ObjectPtr obj = std::make_shared<LE3Object>();
    addCustomObject(name, obj, parent);
}


void LE3Scene::addBox(std::string name, std::string materialName, glm::vec3 position, glm::vec3 extent, std::string parent) {
    LE3BoxPtr obj = std::make_shared<LE3Box>(position.x, position.y, position.z, extent.x, extent.y, extent.z, LE3GetAssetManager().getMaterial(materialName)); // TODO: engine default shader + material
    addCustomObject(name, obj, parent);
}


void LE3Scene::addCylinder(std::string name, std::string materialName, glm::vec3 position, float radius, float height, int resolution, bool withCaps, std::string parent) {
    LE3CylinderPtr obj = std::make_shared<LE3Cylinder>(position.x, position.y, position.z, radius, height, resolution, withCaps, LE3GetAssetManager().getMaterial(materialName)); // TODO: engine default shader + material
    addCustomObject(name, obj, parent);
}

void LE3Scene::addCone(std::string name, std::string materialName, glm::vec3 position, float radius, float height, int resolution, bool withCaps, std::string parent) {
    LE3ConePtr obj = std::make_shared<LE3Cone>(position.x, position.y, position.z, radius, height, resolution, withCaps, LE3GetAssetManager().getMaterial(materialName)); // TODO: engine default shader + material
    addCustomObject(name, obj, parent);
}

void LE3Scene::addTorus(std::string name, std::string materialName, glm::vec3 position, float majorRadius, float minorRadius, int resolution, std::string parent) {
    LE3TorusPtr obj = std::make_shared<LE3Torus>(position.x, position.y, position.z, majorRadius, minorRadius, resolution, LE3GetAssetManager().getMaterial(materialName)); // TODO: engine default shader + material
    addCustomObject(name, obj, parent);
}

void LE3Scene::addSphere(std::string name, std::string materialName, glm::vec3 position, float radius, int resolution, std::string parent) {
    LE3SpherePtr obj = std::make_shared<LE3Sphere>(position.x, position.y, position.z, radius, resolution, LE3GetAssetManager().getMaterial(materialName)); // TODO: engine default shader + material
    addCustomObject(name, obj, parent);
}

void LE3Scene::addStaticModel(std::string name, std::string meshName, std::string materialName, std::string parent, LE3DrawPriority priority) {
    LE3StaticMeshPtr mesh; 
    if (meshName != "") mesh = LE3GetAssetManager().getStaticMesh(meshName);
    LE3StaticModelPtr obj = std::make_shared<LE3StaticModel>(mesh, LE3GetAssetManager().getMaterial(materialName), priority);
    addCustomObject(name, obj, parent);
}

void LE3Scene::addSkeletalModel(std::string name, std::string meshName, std::string materialName, std::string parent) {
    LE3SkeletalMeshPtr mesh = LE3GetAssetManager().getSkeletalMesh(meshName);
    LE3SkeletalModelPtr obj = std::make_shared<LE3SkeletalModel>(mesh, LE3GetAssetManager().getMaterial(materialName));
    addCustomObject(name, obj, parent);
}

void LE3Scene::addPointCloud(std::string name, std::string parent) {
    LE3PointCloudPtr obj = std::make_shared<LE3PointCloud>();
    addCustomObject(name, obj, parent);
}

void LE3Scene::addSprite(std::string name, std::string textureName, std::string parent) {
    LE3SpritePtr obj = std::make_shared<LE3Sprite>(LE3GetAssetManager().getTexture(textureName));
    addCustomObject(name, obj, parent);
}

void LE3Scene::addBSPBrush(std::string name, LE3BSPBrushType brushType) {
    LE3BSPBrushPtr obj = std::make_shared<LE3BSPBrush>();
    obj->setBrushType(brushType);
    addCustomObject(name, obj, "");
    m_sceneGraph->m_bspManager.addBrush(obj);
}

void LE3Scene::addScriptObject(std::string name, std::string classname, std::string parent) {
    LE3ScriptObjectPtr obj = std::make_shared<LE3ScriptObject>(classname, name);
    addCustomObject(name, obj, parent);
}

void LE3Scene::addCustomObject(std::string name, std::shared_ptr<LE3Object> obj, std::string parent) {
    assertObjectName(name);
    obj->setName(name);
    attachObject(name, obj, parent);
    LE3DrawableObjectPtr drawableObj = std::dynamic_pointer_cast<LE3DrawableObject>(obj);
    if (drawableObj) m_sceneGraph->m_drawQueue.addObject(drawableObj);
    obj->init();
}

void LE3Scene::addPlayerStart(std::string classname) {
    std::string name = LE3_PLAYERSTART_OBJECT_NAME;
    LE3PlayerStartPtr obj = std::make_shared<LE3PlayerStart>(classname);
    addCustomObject(name, obj, "");
}

void LE3Scene::addFreeCamera(std::string name, std::string parent) {
    LE3CameraPtr obj = std::make_shared<LE3FreeCamera>();
    addCustomObject(name, obj, parent);
    attachCamera(obj);
    
}
void LE3Scene::addOrbitCamera(std::string name, std::string parent) {
    LE3CameraPtr obj = std::make_shared<LE3OrbitCamera>();
    addCustomObject(name, obj, parent);
    attachCamera(obj);
}

void LE3Scene::addAmbientLight(std::string name, std::string parent) {
    LE3AmbientLightPtr light = std::make_shared<LE3AmbientLight>();
    addCustomObject(name, light, parent);
    m_sceneGraph->m_lightManager.setAmbientLight(light);
    if (LE3EngineSystems::instance().isEditModeEngine()) {
        std::string spriteName = fmt::format("{}_sprite_{}_{}", DEFAULT_ENGINE_PREFIX, name, ++m_ticket);
        addSprite(spriteName, SPRITE_AMBIENT_LIGHT, name);
        getObject(spriteName)->setIsDelegate(true);
    }
}
void LE3Scene::addDirectionalLight(std::string name, std::string parent) {
    LE3DirectionalLightPtr light = std::make_shared<LE3DirectionalLight>();
    addCustomObject(name, light, parent);
    m_sceneGraph->m_lightManager.addDirectionalLight(light);
    if (LE3EngineSystems::instance().isEditModeEngine()) {
        std::string spriteName = fmt::format("{}_sprite_{}_{}", DEFAULT_ENGINE_PREFIX, name, ++m_ticket);
        addSprite(spriteName, SPRITE_DIRECTIONAL_LIGHT, name);
        getObject(spriteName)->setIsDelegate(true);
    }
}
void LE3Scene::addPointLight(std::string name, std::string parent) {
    LE3PointLightPtr light = std::make_shared<LE3PointLight>();
    addCustomObject(name, light, parent);
    m_sceneGraph->m_lightManager.addPointLight(light);
    if (LE3EngineSystems::instance().isEditModeEngine()) {
        std::string spriteName = fmt::format("{}_sprite_{}_{}", DEFAULT_ENGINE_PREFIX, name, ++m_ticket);
        addSprite(spriteName, SPRITE_POINT_LIGHT, name);
        getObject(spriteName)->setIsDelegate(true);
    }
}
void LE3Scene::addSpotLight(std::string name, std::string parent) {
    LE3SpotLightPtr light = std::make_shared<LE3SpotLight>();
    addCustomObject(name, light, parent);
    m_sceneGraph->m_lightManager.addSpotLight(light);
    if (LE3EngineSystems::instance().isEditModeEngine()) {
        std::string spriteName = fmt::format("{}_sprite_{}_{}", DEFAULT_ENGINE_PREFIX, name, ++m_ticket);
        addSprite(spriteName, SPRITE_SPOT_LIGHT, name);
        getObject(spriteName)->setIsDelegate(true);
    }
}

// --------------------------------------------------------------------------------

void LE3Scene::assertObjectName(std::string name) { 
    if (name.size() == 0) throw std::runtime_error(fmt::format("Empty name is not allowed"));
    if (m_sceneGraph->m_pObjects.contains(name)) throw std::runtime_error(fmt::format("Object '{}' already exists", name));
}

void LE3Scene::attachObject(std::string name, LE3ObjectPtr obj, std::string parent) {
    m_sceneGraph->m_pObjects[name] = obj;
    LE3ObjectPtr pParent = m_sceneGraph->m_pRoot;
    if (m_sceneGraph->m_pObjects.contains(parent)) pParent = m_sceneGraph->m_pObjects[parent];
    obj->reparent(pParent);
}

void LE3Scene::attachCamera(LE3CameraPtr pCamera) {
    if (m_pMainCamera == nullptr) m_pMainCamera = pCamera;
}

void LE3Scene::applyMainCamera(LE3ShaderPtr shaderWeak) {
    if (!m_pMainCamera) return;
    std::shared_ptr<LE3Shader> shader = shaderWeak.lock();
    if (!shader) return;
    shader->use();
    shader->uniform("view", m_pMainCamera->getViewMatrix());
    shader->uniform("projection", m_pMainCamera->getProjectionMatrix());
    shader->uniform("cameraPos", glm::vec3(m_pMainCamera->getWorldMatrix()[3]));
}

void LE3Scene::setMainCamera(std::string camera) {
    if (!m_sceneGraph->m_pObjects.contains(camera)) throw std::runtime_error(fmt::format("Object '{}' does not exist", camera));
    LE3CameraPtr pCamera = std::dynamic_pointer_cast<LE3Camera>(m_sceneGraph->m_pObjects[camera]);
    if (!pCamera) throw std::runtime_error(fmt::format("Object '{}' is not a camera", camera));

    if (m_pMainCamera) {
        // Copy old aspect ratio
        pCamera->setAspectRatio(m_pMainCamera->getAspectRatio());
    }

    m_pMainCamera = pCamera;
}

void LE3Scene::buildBSP() {
    m_sceneGraph->m_bspManager.build();
    LE3StaticMeshPtr mesh = m_sceneGraph->m_bspManager.getGeometryMesh();
    if (m_sceneGraph->m_pObjects.contains(LE3_BSP_MESH_NAME)) m_sceneGraph->m_pObjects[LE3_BSP_MESH_NAME]->reparent(nullptr); // TODO: Call scene's "delete" method
    m_sceneGraph->m_pObjects[LE3_BSP_MESH_NAME] = std::make_shared<LE3StaticModel>(mesh, LE3GetAssetManager().getMaterial("M_default")); // TODO: Make sure we have some default material
    m_sceneGraph->m_pObjects[LE3_BSP_MESH_NAME]->reparent(m_sceneGraph->m_pRoot);
    m_sceneGraph->m_drawQueue.addObject(std::dynamic_pointer_cast<LE3DrawableObject>(m_sceneGraph->m_pObjects[LE3_BSP_MESH_NAME]));
}

glm::vec3 LE3Scene::getCursorLocation() {
    return LE3GetImGuiUtils().getRelativeCursor(m_width, m_height, m_offsetX, m_offsetY);
}

void LE3Scene::updateOffset(int offsetX, int offsetY) {
    m_offsetX = offsetX; m_offsetY = offsetY;
}

LE3ObjectPtr LE3Scene::getObjectByID(uint32_t oid) {
    if (oid == 0) return nullptr;

    for (auto kv : m_sceneGraph->m_pObjects) {
        if (auto drawableObj = std::dynamic_pointer_cast<LE3DrawableObject>(kv.second)) {
            if (drawableObj->getDrawID() == oid) return drawableObj;
        }
    }

    return nullptr;
}
LE3ObjectPtr LE3Scene::getObjectByID(glm::vec4 color) {
    // Based on http://www.opengl-tutorial.org/miscellaneous/clicking-on-objects/picking-with-an-opengl-hack/
    int oid = color[0] + color[1] * 256 + color[2] * 256 * 256;
    return getObjectByID(oid);
}

// std::string LE3Scene::getObjectName(LE3ObjectPtr obj) {
//     // for (auto& it : m_sceneGraph->m_pObjects) {
//     //     if (it.second == obj) return it.first;
//     // }
//     // return "";
//     return obj->getName();
// }

void LE3Scene::updateHoveredObject() {
    glm::vec3 mouse = 0.5f * (getCursorLocation() + 1.f);
    mouse.x *= m_width; mouse.y *= m_height;

    if (mouse.z > 0.f) {
        glm::vec4 pixel = m_objectIdsBuffer->readPixel(mouse) * 255.f;
        LE3ObjectPtr obj = getObjectByID(pixel);
        LE3GetEditorManager().setHoveredObject(obj);
    }

    // if (LE3GetEditorManager().getHoveredObject().lock())
    //     fmt::print("{}\n", LE3GetEditorManager().getHoveredObject().lock()->getName());
}

void LE3Scene::deleteObject(std::string name) {
    if (!m_sceneGraph->m_pObjects.contains(name)) return;
    for (auto child : m_sceneGraph->m_pObjects[name]->getChildren()) 
        deleteObject(child->getName());
    m_sceneGraph->m_pObjects[name]->reparent(nullptr);
    m_sceneGraph->m_pObjects[name]->getPhysicsComponent().disable();
    m_sceneGraph->m_lightManager.deleteLight(name); // Hotfix for deleting lights (when drawing shadows)
    m_sceneGraph->m_pObjects.erase(name);
}

void LE3Scene::renameObject(std::string oldName, std::string newName) {
    if (!m_sceneGraph->m_pObjects.contains(oldName)) return;
    if (m_sceneGraph->m_pObjects.contains(newName)) return;
    m_sceneGraph->m_pObjects[newName] = m_sceneGraph->m_pObjects[oldName];
    m_sceneGraph->m_pObjects.erase(oldName);
    m_sceneGraph->m_pObjects[newName]->setName(newName);
    std::pair<std::string, std::string> data(oldName, newName);
    LE3GetEventManager().notify(LE3SceneEvents::LE3_EVENT_OBJECT_RENAME, (void*)&data);
}

void LE3Scene::rebuild() {
    m_sceneGraph->m_drawQueue.clear();
    for (auto obj : m_sceneGraph->m_pObjects) {
        if (auto drawableObj = std::dynamic_pointer_cast<LE3DrawableObject>(obj.second)) {
            m_sceneGraph->m_drawQueue.addObject(drawableObj);
        }
    }
}

void LE3Scene::propagateDeleteMaterial(std::string name) {
    if (name == "") return;
    for (auto obj : m_sceneGraph->m_pObjects) {
        if (auto drawableObj = std::dynamic_pointer_cast<LE3DrawableObject>(obj.second)) {
            if (drawableObj->getMaterial().expired() || 
                drawableObj->getMaterial().lock()->name == name) {
                drawableObj->setMaterial(LE3GetAssetManager().getErrorMaterial());
            }
        }
    }
}

std::string LE3Scene::getNextAvailableName(std::string objectName) {
    // First, split by "_" and get the last number, if there is one
    std::string prefix;
    int idx = 0;

    size_t lastUnderscorePos = objectName.rfind('_');
    if (lastUnderscorePos != std::string::npos) {
        prefix = objectName.substr(0, lastUnderscorePos);
        std::string number = objectName.substr(lastUnderscorePos + 1);
        try {
            idx = std::stoi(number);
        } catch (...) {
            prefix = objectName;
        }
    }
    else prefix = objectName;

    while (true) {
        std::string newName = fmt::format("{}_{}", prefix, ++idx);
        if (!m_sceneGraph->m_pObjects.contains(newName)) return newName;
    }
}