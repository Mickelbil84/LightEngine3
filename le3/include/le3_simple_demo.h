#pragma once

#include "le3_scene.h"
#include "le3_game_logic.h"

namespace le3 {
    class LE3SimpleDemo : public LE3GameLogic {
    public:
        virtual void init();
        virtual void update(float deltaTime);
        virtual void render();
        virtual void renderDebug();
        virtual void handleInput(LE3Input input);

    protected:      
        // Viewport navigation
        glm::vec3 m_cameraVelocity, m_cameraRotation;
        glm::vec3 m_initialPosition = glm::vec3(0.f, 0.5f, 3.f);
        float m_walkSpeed = 2.2f, m_sensitivity = 0.005f;
        
    };
}