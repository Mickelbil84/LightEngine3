#include "components/le3ed_scenes.h"
using namespace le3;

void LE3EditorScenes::init() {
    initScenes();
    initCameras();
    initGizmo();
}
void LE3EditorScenes::update(float deltaTime) {
    LE3GetSceneManager().updateScenes(deltaTime);
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
}
void LE3EditorScenes::initScenes() {
    LE3GetSceneManager().createScene("scene", m_engineState);
    LE3GetSceneManager().getScene("scene")->setRenderDirectly(false);
    LE3GetSceneManager().getScene("scene")->resize(10, 10);
    LE3GetSceneManager().getScene("scene")->drawDebug = [this]() { this->renderDebug(); };

    // Add four inspector scenes
    for (int i = 0; i < 4; i++) {
        // TODO: Add ortographic cameras
        LE3GetSceneManager().createInspectedScene(fmt::format("inspector{}", i), m_engineState, "scene");
        LE3GetSceneManager().getScene(fmt::format("inspector{}", i))->setRenderDirectly(false);
    }
}
void LE3EditorScenes::initGizmo() {
    LE3GizmoPtr gizmo = std::make_shared<LE3Gizmo>();
    LE3GetSceneManager().getScene("scene")->addCustomObject(DEFAULT_ENGINE_PREFIX + "gizmo", gizmo);
    for (int i = 0; i < 4; i++)
        LE3GetSceneManager().getScene(fmt::format("inspector{}", i))->addInspectedUpdate(DEFAULT_ENGINE_PREFIX + "gizmo");
    LE3GetEditorManager().registerGizmo(gizmo);
    gizmo->setHidden(true);
}
