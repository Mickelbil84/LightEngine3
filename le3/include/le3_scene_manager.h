#pragma once

#include <map>

#include "le3_scene.h"
#include "le3_engine_state.h"

namespace le3 {
    class LE3SceneManager {
    public:
        void createScene(std::string name, LE3EngineState& engineState, std::string scenePath = "");
        void createInspectedScene(std::string name, LE3EngineState& engineState, std::string inspected);
        inline LE3ScenePtr getActiveScene() { return m_scenes[m_activeSceneName]; }
        inline LE3ScenePtr getScene(std::string name) { return m_scenes[name]; }
        inline void setActiveScene(std::string name) { m_activeSceneName = name; }

    private:
        std::map<std::string, LE3ScenePtr> m_scenes;
        std::string m_activeSceneName;
    };
}