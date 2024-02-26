#pragma once

#include "le3_input.h"
#include "le3_engine_state.h"

namespace le3 {
    ////////////////////////////////////////////////////////////
    // Any game implementation should inherit from LE3GameLogic
    ////////////////////////////////////////////////////////////
    class LE3GameLogic {
    public:
        virtual void init() {}
        virtual void handleInput(LE3Input input) {}
        virtual void update(float deltaTime) {}
        virtual void render() {}
        virtual void shutdown() {}

    protected:
        LE3EngineState m_engineState;
    
    public:
        friend class LE3Application;
    };
}