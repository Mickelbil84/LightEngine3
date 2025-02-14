#include "le3ed_logic.h"
#include "le3ed_cache.h"
#include "le3ed_editor_systems.h"
#include "commands/le3ed_com_property_change.h" // TODO: TEMP
using namespace le3;

#include <fmt/core.h>

LE3EditorLogic::LE3EditorLogic() :
        m_gui(m_engineState), 
        m_scenes(m_engineState),
        m_hotkeys(m_engineState) {
    m_pComponents.push_back(&m_gui);
    m_pComponents.push_back(&m_scenes);
    m_pComponents.push_back(&m_hotkeys);

    LE3EditorSystems::instance().setGUIComponent(&m_gui);
    LE3EditorSystems::instance().setScenesComponent(&m_scenes);
    LE3EditorSystems::instance().setHotkeysComponent(&m_hotkeys);

    // TODO: Move to seperate component if there would be more lua bindings
    LE3EditorComPropertyChange::registerLua();
}

void LE3EditorLogic::init() {
    LE3GetDatFileSystem().addArchive("editor", "editor.dat");
    LE3EditorCache::load();

    // TODO: TEMP
    LE3GetDatFileSystem().addArchive("demos", "demos.dat");

    // Init Subsystems;
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
