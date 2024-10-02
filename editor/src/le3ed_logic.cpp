#include "le3ed_logic.h"
using namespace le3;

#include <fmt/core.h>

LE3EditorLogic::LE3EditorLogic() :
        m_gui(m_engineState), 
        m_scenes(m_engineState) {
    m_pComponents.push_back(&m_gui);
    m_pComponents.push_back(&m_scenes);
}

void LE3EditorLogic::init() {
    LE3GetDatFileSystem().addArchive("editor", "editor.dat");
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
