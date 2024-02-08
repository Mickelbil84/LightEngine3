#include "le3_scene.h"
using namespace le3;

#include <fstream>
#include <sstream>
#include <stdexcept>

#include <gl/glew.h>

#include <fmt/core.h>
using fmt::format, fmt::print;

#include "le3_engine_systems.h"

void LE3Scene::init(int width, int height) {
    m_sceneGraph = std::make_shared<LE3SceneGraph>();
    m_sceneGraph->m_pRoot = std::make_shared<LE3SceneRoot>();
    m_pMainCamera = nullptr;
    resize(width, height);

    // Load post process shader
    m_postProcessShader = LE3GetAssetManager().getShader(DEFAULT_POSTPROCESS_SHADER);
}
void LE3Scene::init_inspector(int width, int height, LE3Scene& original) {
    init(width, height);
    m_sceneGraph = original.m_sceneGraph;
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


void LE3Scene::resize(int width, int height)
{
    m_width = width; m_height = height;
    m_rawBuffer = std::make_shared<LE3Framebuffer>(m_width, m_height, LE3FramebufferType::LE3_FRAMEBUFFER_COLOR_DEPTH_STENCIL, true);
    m_postProcessBuffer = std::make_shared<LE3Framebuffer>(m_width, m_height, LE3FramebufferType::LE3_FRAMEBUFFER_COLOR_DEPTH_STENCIL, true);
    if (m_pMainCamera) {
        m_pMainCamera->setAspectRatio((float)m_width / (float)m_height);
    }
}


void LE3Scene::update(float deltaTime) {
    m_sceneGraph->m_pRoot->update(deltaTime);
}

void LE3Scene::draw() {
    // TODO: Draw the scene once for each shadowmap
    drawLights();

    // Draw the scene as is
    drawObjects();

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
    for (auto light : m_sceneGraph->m_lightManager.getDirectionalLights()) {
        if (!light->getShadowMap()) continue;
        LE3GetAssetManager().getShader(DEFAULT_SHADOWMAP_SHADER)->use();
        LE3GetAssetManager().getShader(DEFAULT_SHADOWMAP_SHADER)->uniform("lightMatrix", light->getViewMatrix(cameraPos));
        drawObjects(LE3GetAssetManager().getShader(DEFAULT_SHADOWMAP_SHADER), light->getShadowMap(), true);
        light->getShadowMap()->setBindIdx(shadowMapIdx++);
    }
    glCullFace(GL_BACK); 
    glDisable(GL_CULL_FACE);
}

void LE3Scene::drawObjects(LE3ShaderPtr shaderOverride, LE3FramebufferPtr buffer, bool depth) {
    if (buffer == nullptr) buffer = m_rawBuffer;
    
    buffer->bind();
    glClearColor(m_backgroundColor.r, m_backgroundColor.g, m_backgroundColor.b, 1.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    glViewport(0, 0, m_rawBuffer->getWidth(), m_rawBuffer->getHeight());
    if (depth) glEnable(GL_DEPTH_TEST); else glDisable(GL_DEPTH_TEST);

    if (shaderOverride == nullptr) for (auto kv : LE3GetAssetManager().getShaders()) {
        applyMainCamera(kv.second);
        m_sceneGraph->m_lightManager.renderLights(kv.second, glm::vec3(m_pMainCamera->getWorldMatrix()[3]));
    }
    else { 
        applyMainCamera(shaderOverride);
        m_sceneGraph->m_lightManager.renderLights(shaderOverride, glm::vec3(m_pMainCamera->getWorldMatrix()[3]));
    }
    m_sceneGraph->m_drawQueue.draw(shaderOverride);
}

void LE3Scene::drawPostProcess() {
    if (!m_postProcessShader) return;
    
    if (m_bRenderDirectly) glBindFramebuffer(GL_FRAMEBUFFER, 0);
    else m_postProcessBuffer->bind();
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); 
    glClear(GL_COLOR_BUFFER_BIT);
    glDisable(GL_DEPTH_TEST);
    glViewport(0, 0, m_postProcessBuffer->getWidth(), m_postProcessBuffer->getHeight());

    m_postProcessShader->use();
    m_rawBuffer->useColorTexture();
    LE3GetAssetManager().getScreenRect()->draw();
}

// -----------

void LE3Scene::addEmptyObject(std::string name, std::string parent) {
    assertObjectName(name);
    LE3ObjectPtr obj = std::make_shared<LE3Object>();
    attachObject(name, obj, parent);
}


void LE3Scene::addBox(std::string name, std::string materialName, glm::vec3 position, glm::vec3 extent, std::string parent) {
    assertObjectName(name);
    LE3BoxPtr obj = std::make_shared<LE3Box>(position.x, position.y, position.z, extent.x, extent.y, extent.z, LE3GetAssetManager().getMaterial(materialName)); // TODO: engine default shader + material
    attachObject(name, obj, parent);
    m_sceneGraph->m_drawQueue.addObject(obj);
}

void LE3Scene::addStaticModel(std::string name, std::string meshName, std::string materialName, std::string parent) {
    assertObjectName(name);
    LE3StaticMeshPtr mesh = LE3GetAssetManager().getStaticMesh(meshName);
    LE3StaticModelPtr obj = std::make_shared<LE3StaticModel>(mesh, LE3GetAssetManager().getMaterial(materialName));
    attachObject(name, obj, parent);
    m_sceneGraph->m_drawQueue.addObject(obj);
}


void LE3Scene::addFreeCamera(std::string name, std::string parent) {
    assertObjectName(name);
    LE3CameraPtr obj = std::make_shared<LE3FreeCamera>();
    attachObject(name, obj, parent);
    attachCamera(obj);
    
}
void LE3Scene::addOrbitCamera(std::string name, std::string parent) {
    assertObjectName(name);
    LE3CameraPtr obj = std::make_shared<LE3OrbitCamera>();
    attachObject(name, obj, parent);
    attachCamera(obj);
}

void LE3Scene::addAmbientLight(std::string name, std::string parent) {
    assertObjectName(name);
    LE3AmbientLightPtr light = std::make_shared<LE3AmbientLight>();
    attachObject(name, light, parent);
    m_sceneGraph->m_lightManager.setAmbientLight(light);
}
void LE3Scene::addDirectionalLight(std::string name, std::string parent) {
    assertObjectName(name);
    LE3DirectionalLightPtr light = std::make_shared<LE3DirectionalLight>();
    attachObject(name, light, parent);
    m_sceneGraph->m_lightManager.addDirectionalLight(light);
}
void LE3Scene::addPointLight(std::string name, std::string parent) {
    assertObjectName(name);
    LE3PointLightPtr light = std::make_shared<LE3PointLight>();
    attachObject(name, light, parent);
    m_sceneGraph->m_lightManager.addPointLight(light);
}
void LE3Scene::addSpotLight(std::string name, std::string parent) {
    assertObjectName(name);
    LE3SpotLightPtr light = std::make_shared<LE3SpotLight>();
    attachObject(name, light, parent);
    m_sceneGraph->m_lightManager.addSpotLight(light);
}

// --------------------------------------------------------------------------------

void LE3Scene::assertObjectName(std::string name) { 
    if (name.size() == 0) throw std::runtime_error(format("Empty name is not allowed"));
    if (m_sceneGraph->m_pObjects.contains(name)) throw std::runtime_error(format("Object '{}' already exists", name));
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

void LE3Scene::applyMainCamera(LE3ShaderPtr shader) {
    if (!m_pMainCamera) return;
    shader->use();
    shader->uniform("view", m_pMainCamera->getViewMatrix());
    shader->uniform("projection", m_pMainCamera->getProjectionMatrix());
    shader->uniform("cameraPos", glm::vec3(m_pMainCamera->getWorldMatrix()[3]));
}

void LE3Scene::setMainCamera(std::string camera) {
    if (!m_sceneGraph->m_pObjects.contains(camera)) throw std::runtime_error(format("Object '{}' does not exist", camera));
    LE3CameraPtr pCamera = std::dynamic_pointer_cast<LE3Camera>(m_sceneGraph->m_pObjects[camera]);
    if (!pCamera) throw std::runtime_error(format("Object '{}' is not a camera", camera));

    if (m_pMainCamera) {
        // Copy old aspect ratio
        pCamera->setAspectRatio(m_pMainCamera->getAspectRatio());
    }

    m_pMainCamera = pCamera;
}