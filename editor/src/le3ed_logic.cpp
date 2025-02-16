#include "le3ed_logic.h"
#include "le3ed_cache.h"
#include "le3ed_editor_systems.h"

using namespace le3;

#include <fmt/core.h>

LE3EditorLogic::LE3EditorLogic() :
        m_gui(m_engineState), 
        m_scenes(m_engineState),
        m_hotkeys(m_engineState),
        m_scripts(m_engineState) {
    m_pComponents.push_back(&m_scripts); // See comment (*) in le3ed_logic.h
    m_pComponents.push_back(&m_gui);
    m_pComponents.push_back(&m_scenes);
    m_pComponents.push_back(&m_hotkeys);

    LE3EditorSystems::instance().setGUIComponent(&m_gui);
    LE3EditorSystems::instance().setScenesComponent(&m_scenes);
    LE3EditorSystems::instance().setHotkeysComponent(&m_hotkeys);
    LE3EditorSystems::instance().setScriptsComponent(&m_scripts);
}

void LE3EditorLogic::init() {
    LE3GetDatFileSystem().addArchive("editor", "editor.dat");
    LE3GetDatFileSystem().addArchive("demos", "demos.dat"); // Also add demos so that even new projects can have something to play with

    // Init Subsystems;
    assert(dynamic_cast<LE3EditorScripts*>(m_pComponents[0])); // See comment (*) in le3ed_logic.h
    for (auto component : m_pComponents) component->init();
}
void LE3EditorLogic::update(float deltaTime) {
    for (auto component : m_pComponents) component->update(deltaTime);
}
void LE3EditorLogic::render() {
    for (auto component : m_pComponents) component->render();
}
void LE3EditorLogic::renderDebug() {
    for (auto component : m_pComponents) component->renderDebug();
}
void LE3EditorLogic::handleInput(LE3Input input) {
    for (auto component : m_pComponents) component->handleInput(input);
}
