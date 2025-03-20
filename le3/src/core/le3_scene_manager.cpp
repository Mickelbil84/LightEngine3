#include "core/le3_scene_manager.h"
#include "core/le3_engine_systems.h"
using namespace le3;

void LE3SceneManager::reset() {
    m_scenes.clear();
    m_activeSceneName = "";
}

void LE3SceneManager::createScene(std::string name, LE3EngineState& engineState, std::string scenePath) {
    m_scenes[name] = std::make_shared<LE3Scene>(name);
    m_scenes[name]->init(engineState.getWindowWidth(), engineState.getWindowHeight());
    if (m_activeSceneName == "") m_activeSceneName = name;
    if (scenePath != "") m_scenes[name]->load(scenePath);
}

void LE3SceneManager::createInspectedScene(std::string name, LE3EngineState& engineState, std::string inspected) {
    m_scenes[name] = std::make_shared<LE3Scene>(name);
    m_scenes[name]->init_inspector(engineState.getWindowWidth(), engineState.getWindowHeight(), *m_scenes[inspected]);
}

void LE3SceneManager::updateScenes(float deltaTime) {
    // Before even updating any of the scenes, step the physics simulator
    LE3GetPhysicsManager().update(deltaTime);

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