#pragma once

#include <memory>
#include <stdexcept>

#include "le3_game_logic.h"


namespace le3 {
    class LE3Application {
    public:
        LE3Application(std::unique_ptr<LE3GameLogic> pGameLogic);
        void run(); // Main game loop

    protected:
        std::unique_ptr<LE3GameLogic> m_pGameLogic;

        // Holds handles to window and GPU context
        struct _Internal;
        std::shared_ptr<_Internal> m_pInternal;

        bool m_bShouldRun;
        unsigned int m_prevTime, m_currTime;
        float m_deltaTime;

        void init();
        void handleInput();
        void update();
        void render();
        void shutdown();

    private:
        void _initSDL();
        void _initOpenGL();
        void _initImGui();
    };
}