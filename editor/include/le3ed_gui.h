#pragma once

#include <le3.h>

namespace le3 {
    class LE3EditorGUI {
    public:
        LE3EditorGUI(LE3EngineState& engineState) : m_engineState(engineState) {}
        void init();
        void update();

    private:
        LE3EngineState& m_engineState;
    };
}