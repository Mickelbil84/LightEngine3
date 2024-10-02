#pragma once

#include <le3.h>
namespace le3 {
    class LE3EditorComponent {
    public:
        LE3EditorComponent(LE3EngineState& engineState) : m_engineState(engineState) {}
        virtual void init() {}
        virtual void update(float deltaTime) {}
        virtual void render() {}
        virtual void renderDebug() {}
        virtual void handleInput(LE3Input input) {}

    protected:
        LE3EngineState& m_engineState;
    };
}

#define LE3ED_COMPONENT_DEAFULT_CTOR(cls) cls(LE3EngineState& engineState) : LE3EditorComponent(engineState) {}