#include "components/le3ed_scenes.h"
#include "le3ed_editor_systems.h"
using namespace le3;


void LE3EditorScenes::loadScene(std::string name) {
    cameraVelocity = glm::vec3();
    cameraRotation = glm::vec3();

    initScenes(name);
    initCameras();
    initGizmo();
}
void LE3EditorScenes::saveScene(std::string name) {
    // LE3GetScriptSystem().doString("print(serialize(LE3Scene))")
}


void LE3EditorScenes::init() {
    loadScene(LE3GetConfig<std::string>("LE3ProjectConfig.LastOpenedScene", ""));

    // Bind scene hotkeys
    LE3EditorSystems::instance().getHotkeysComponent()->bindHotkey({"KEY_UP"}, []() {
        if (LE3GetEditorManager().getSelection().pObjects.size() != 1) return;
        if (LE3ObjectPtr pObject = LE3GetEditorManager().getSelection().getLastSelectedObject().lock()) {
            if (pObject->getParent() && !std::dynamic_pointer_cast<LE3SceneRoot>(pObject->getParent()))
                LE3GetEditorManager().getSelection().selectObject(pObject->getParent());
        }
    });
}
void LE3EditorScenes::update(float deltaTime) {
    // Update camera control
    std::string scene = "scene";
    if (m_engineState.getFocusOverrider() == "ViewportSecondary") scene = "inspector0";
    if (m_engineState.getFocusOverrider() == "ViewportFront") scene = "inspector1";
    if (m_engineState.getFocusOverrider() == "ViewportRight") scene = "inspector2";
    if (m_engineState.getFocusOverrider() == "ViewportTop") scene = "inspector3";
    LE3GetSceneManager().getScene(scene)->getMainCamera()->addPitchYaw(sensitivity * cameraRotation.y, -sensitivity * cameraRotation.x);
    LE3GetSceneManager().getScene(scene)->getMainCamera()->moveForward(deltaTime * walkSpeed * cameraVelocity.y);
    LE3GetSceneManager().getScene(scene)->getMainCamera()->moveRight(deltaTime * walkSpeed * cameraVelocity.x);
    LE3GetSceneManager().getScene(scene)->getMainCamera()->moveUp(deltaTime * walkSpeed * cameraVelocity.z);


    LE3GetSceneManager().updateScenes(deltaTime);

    // Set light sprite visibility
    for (auto& [k, scene] : LE3GetSceneManager().getScenes()) {
        scene->setLightSpriteVisibility(true);
    }

    // Set objects' selected status
    for (auto& [name, obj] : LE3GetActiveScene()->getObjects()) {
        LE3DrawableObjectPtr pObject = std::dynamic_pointer_cast<LE3DrawableObject>(obj);
        if (!pObject) continue;
        pObject->setSelected(false);
    }
    for (int i = 0; i < LE3GetEditorManager().getSelection().pObjects.size(); i++) {
        std::vector<LE3ObjectPtr> queue;
        if (!LE3GetEditorManager().getSelection().pObjects[i].lock()) continue;
        queue.push_back(LE3GetEditorManager().getSelection().pObjects[i].lock());
        while (!queue.empty()) {
            LE3ObjectPtr pObject = queue.back();
            queue.pop_back();
            LE3DrawableObjectPtr pDrawableObject = std::dynamic_pointer_cast<LE3DrawableObject>(pObject);
            if (pDrawableObject) pDrawableObject->setSelected(true);
            for (auto& child : pObject->getChildren()) {
                queue.push_back(child);
            }
        }
    }
}
void LE3EditorScenes::render() {
    LE3GetSceneManager().getScene("scene")->draw();
    // for (int i = 0; i < 4; i++)
    //     LE3GetSceneManager().getScene(fmt::format("inspector{}", i))->draw();
}
void LE3EditorScenes::initCameras() {
    LE3GetSceneManager().getScene("scene")->addFreeCamera(DEFAULT_ENGINE_PREFIX + "mainCamera");
    LE3GetSceneManager().getScene("scene")->addFreeCamera(DEFAULT_ENGINE_PREFIX + "secondaryCamera");
    LE3GetSceneManager().getScene("scene")->addFreeCamera(DEFAULT_ENGINE_PREFIX + "frontCamera");
    LE3GetSceneManager().getScene("scene")->addFreeCamera(DEFAULT_ENGINE_PREFIX + "rightCamera");
    LE3GetSceneManager().getScene("scene")->addFreeCamera(DEFAULT_ENGINE_PREFIX + "topCamera");

    LE3GetSceneManager().getScene("scene")->setMainCamera(DEFAULT_ENGINE_PREFIX + "mainCamera");
    LE3GetSceneManager().getScene("inspector0")->setMainCamera(DEFAULT_ENGINE_PREFIX + "secondaryCamera");
    LE3GetSceneManager().getScene("inspector1")->setMainCamera(DEFAULT_ENGINE_PREFIX + "frontCamera");
    LE3GetSceneManager().getScene("inspector2")->setMainCamera(DEFAULT_ENGINE_PREFIX + "rightCamera");
    LE3GetSceneManager().getScene("inspector3")->setMainCamera(DEFAULT_ENGINE_PREFIX + "topCamera");

    // Offset cameras
    LE3GetSceneManager().getScene("scene")->getMainCamera()->getTransform().setPosition(glm::vec3(0.f, 0.5f, 5.f));
}
void LE3EditorScenes::initScenes(std::string name) {    
    LE3GetSceneManager().createScene("scene", m_engineState, name);
    LE3GetSceneManager().getScene("scene")->setRenderDirectly(false);
    LE3GetSceneManager().getScene("scene")->resize(10, 10);
    LE3GetSceneManager().getScene("scene")->drawDebug = [this]() { this->renderDebug(); };
    LE3GetSceneManager().getScene("scene")->setBackgroundColor(glm::vec3(LE3GetConfig<float>("LE3EditorConfig.DefaultColors.DefaultNewScene")));
    
    // Add four inspector scenes
    for (int i = 0; i < 4; i++) {
        // TODO: Add ortographic cameras
        std::string name = fmt::format("inspector{}", i);
        LE3GetSceneManager().createInspectedScene(name, m_engineState, "scene");
        LE3GetSceneManager().getScene(name)->setRenderDirectly(false);
        LE3GetSceneManager().getScene(name)->drawDebug = [this]() { this->renderDebug(); };
        LE3GetSceneManager().getScene(name)->setBackgroundColor(glm::vec3(0.04f));
    }
    
    // Load post process shader
    LE3GetAssetManager().addShaderFromFile(DEFAULT_ENGINE_PREFIX + "S_le3edpp", "/engine/shaders/postprocess/ppvert.vs", "/editor/shaders/le3edpp.fs");
    for (auto& [k, scene] : LE3GetSceneManager().getScenes()) {
        scene->setPostProcessShader(LE3GetAssetManager().getShader(DEFAULT_ENGINE_PREFIX + "S_le3edpp"));
    }
}
void LE3EditorScenes::initGizmo() {
    LE3GizmoPtr gizmo = std::make_shared<LE3Gizmo>();
    LE3GetSceneManager().getScene("scene")->addCustomObject(DEFAULT_ENGINE_PREFIX + "gizmo", gizmo);
    // for (int i = 0; i < 4; i++)
    //     LE3GetSceneManager().getScene(fmt::format("inspector{}", i))->addInspectedUpdate(DEFAULT_ENGINE_PREFIX + "gizmo");
    LE3GetEditorManager().registerGizmo(gizmo);
    gizmo->setHidden(false);
}

void LE3EditorScenes::handleInput(LE3Input input) {
    if (!m_engineState.getFocusedOverride()) return;

    ////////////////////////
    // Camera Movement
    ////////////////////////
    cameraVelocity = glm::vec3();
    cameraRotation = glm::vec3();
    if (!LE3GetEditorManager().isActiveEdit()) {
        if (input.bRightMouseDown || m_engineState.isRelativeMouse()) {
            if (input.keys["KEY_W"]) cameraVelocity.y = 1.f;
            else if (input.keys["KEY_S"]) cameraVelocity.y = -1.f;
            else cameraVelocity.y = 0.f;

            if (input.keys["KEY_D"]) cameraVelocity.x = 1.f;
            else if (input.keys["KEY_A"]) cameraVelocity.x = -1.f;
            else cameraVelocity.x = 0.f;

            if (input.keys["KEY_E"]) cameraVelocity.z = 1.f;
            else if (input.keys["KEY_Q"]) cameraVelocity.z = -1.f;
            else cameraVelocity.z = 0.f;

            cameraRotation.x = (float)input.xrel;
            cameraRotation.y = -(float)input.yrel;
        }
    }
    // If camera already moves, block edit
    LE3GetEditorManager().setEditBlocked(glm::length(cameraVelocity) > 0.f || glm::length(cameraRotation) > 0.f);
}