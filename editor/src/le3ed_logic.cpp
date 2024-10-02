#include "le3ed_logic.h"
using namespace le3;

#include <fmt/core.h>

LE3EditorLogic::LE3EditorLogic() :
    m_gui(m_engineState) {

}

void LE3EditorLogic::init() {
    LE3GetDatFileSystem().addArchive("editor", "editor.dat");

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

    LE3GizmoPtr gizmo = std::make_shared<LE3Gizmo>();
    LE3GetSceneManager().getScene("scene")->addCustomObject(DEFAULT_ENGINE_PREFIX + "gizmo", gizmo);
    for (int i = 0; i < 4; i++)
        LE3GetSceneManager().getScene(fmt::format("inspector{}", i))->addInspectedUpdate(DEFAULT_ENGINE_PREFIX + "gizmo");
    LE3GetEditorManager().registerGizmo(gizmo);
    gizmo->setHidden(true);

    // Init Subsystems;
    m_gui.init();
}
void LE3EditorLogic::update(float deltaTime) {
    m_gui.update();
}
void LE3EditorLogic::render() {

}
void LE3EditorLogic::renderDebug() {

}
void LE3EditorLogic::handleInput(LE3Input input) {

}
