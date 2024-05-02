#include "le3_scene_manager.h"
using namespace le3;

void LE3SceneManager::createScene(std::string name, LE3EngineState& engineState, std::string scenePath) {
    m_scenes[name] = std::make_shared<LE3Scene>(name);
    m_scenes[name]->init(engineState.getWindowWidth(), engineState.getWindowHeight());
    if (scenePath != "") m_scenes[name]->load(scenePath);
    if (m_activeSceneName == "") m_activeSceneName = name;
}

void LE3SceneManager::createInspectedScene(std::string name, LE3EngineState& engineState, std::string inspected) {
    m_scenes[name] = std::make_shared<LE3Scene>(name);
    m_scenes[name]->init_inspector(engineState.getWindowWidth(), engineState.getWindowHeight(), *m_scenes[inspected]);
}

void LE3SceneManager::updateScenes(float deltaTime) {
    for (auto [name, scene] : m_scenes) {
        if (!scene->isInspected()) scene->preUpdate();
    }
    for (auto [name, scene] : m_scenes) {
        scene->update(deltaTime);
    }
    for (auto [name, scene] : m_scenes) {
        if (!scene->isInspected()) scene->postUpdate();
    }
}