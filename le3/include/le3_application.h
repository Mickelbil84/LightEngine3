#pragma once

#include <memory>
#include <stdexcept>

#include "le3_game_logic.h"


namespace le3 {
    class LE3Application {
    public:
        LE3Application(std::unique_ptr<LE3GameLogic> pGameLogic);
        LE3Application(); // Headless version! Beware
        void run(); // Main game loop
        void init();

    protected:
        std::unique_ptr<LE3GameLogic> m_pGameLogic;

        // Holds handles to window and GPU context
        struct _Internal;
        std::shared_ptr<_Internal> m_pInternal;

        bool m_bShouldRun;
        unsigned int m_prevTime, m_currTime;
        float m_deltaTime;
        LE3Input m_lastInput;

        void handleInput();
        void update();
        void render();
        void shutdown();

    private:
        void _initSDL();
        void _initOpenGL();
        void _initImGui();

        void _handleNotifys(); // Handle notify events from the engine state

        void getKeyboardInput(LE3Input& input); // Convert SDL format to LE3 input format
        void createSDLKeyMapping();
        std::map<int, std::string> m_sdlKeyMapping;

        bool m_bHeadless = false;
    };
}