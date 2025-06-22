#include <le3.h>
using namespace le3;

#define _USE_MATH_DEFINES
#include <math.h>
#include <random>

#include <fmt/core.h>

#include <glm/gtx/string_cast.hpp>

#include <imgui_internal.h>

class Demo03_RacingShooter : public LE3GameLogic {
public:
    // LE3Scene m_scene, m_inspector;
    glm::vec3 cameraVelocity, cameraRotation;
    float t = 0.f;
    
    float walkSpeed = 2.2f, sensitivity = 0.005f;

    void init() {
        LE3GetDatFileSystem().addArchive("demos", "demos.dat");

        LE3GetSceneManager().createScene("scene", m_engineState, "");
        LE3GetActiveScene()->drawDebug = [this]() { this->renderDebug(); };
        LE3GetActiveScene()->addFreeCamera("camera");
        LE3GetActiveScene()->setBackgroundColor(glm::vec3(100.f/255.f, 149.f/255.f, 253.f/255.f));

        LE3GetActiveScene()->addAmbientLight("ambient");
        LE3GetActiveScene()->getObject<LE3AmbientLight>("ambient")->setIntensity(0.8f);
        LE3GetActiveScene()->addDirectionalLight("sun");
        LE3GetActiveScene()->getObject<LE3DirectionalLight>("sun")->setIntensity(0.8f);
        LE3GetActiveScene()->getObject<LE3DirectionalLight>("sun")->getTransform().setRotationRPY(0.f, 0.f, -0.5f);

        // LE3GetActiveScene()->addSphere("drone1", "M_DEFAULT", glm::vec3(1.f, 0.f, 0.f), 0.1f);
        // LE3GetActiveScene()->addSphere("drone2", "M_DEFAULT", glm::vec3(1.2f, 0.f, 0.f), 0.1f);
        // LE3GetActiveScene()->addSphere("drone3", "M_DEFAULT", glm::vec3(1.4f, 0.f, 0.f), 0.1f);

    }
    void update(float deltaTime) {
        // Setup FPS camera
        LE3GetActiveScene()->getMainCamera()->addPitchYaw(sensitivity * cameraRotation.y, -sensitivity * cameraRotation.x);
        LE3GetActiveScene()->getMainCamera()->moveForward(deltaTime * walkSpeed * cameraVelocity.y);
        LE3GetActiveScene()->getMainCamera()->moveRight(deltaTime * walkSpeed * cameraVelocity.x);
        LE3GetActiveScene()->getMainCamera()->moveUp(deltaTime * walkSpeed * cameraVelocity.z);

        // Update scenes        
        LE3GetSceneManager().updateScenes(deltaTime);

        t += deltaTime;
    }

    void render() {
        LE3GetSceneManager().getScene("scene")->draw();
    }

    void renderDebug() {
        LE3GetVisualDebug().drawDebugCone(glm::vec3(0.f), 1.f, 2.f, glm::vec3(1.f, 1.f, 0.f));

        
        float r1 = 0.5f, r2 = 0.4f, r3 = 0.5;
        float f1 = 1.f, f2 = 3.f, f3 = 5.f;
        glm::vec3 pos1 = glm::vec3(r1 * cosf(f1 * t), 0.f, r1 * sinf(f1 * t));
        glm::vec3 pos2 = pos1 + glm::vec3(r2 * cosf(f2 * t), 0.f, r2 * sinf(f2 * t));
        glm::vec3 pos3 = pos2 + glm::vec3(r3 * cosf(f3 * t), 0.f, r3 * sinf(f3 * t));


        LE3GetVisualDebug().drawDebugBox(pos1, glm::quat(), glm::vec3(0.15f), glm::vec3(0.f, 1.f, 0.f));
        LE3GetVisualDebug().drawDebugBox(pos2, glm::quat(), glm::vec3(0.15f), glm::vec3(0.f, 1.f, 0.f));
        LE3GetVisualDebug().drawDebugBox(pos3, glm::quat(), glm::vec3(0.15f), glm::vec3(0.f, 1.f, 0.f));
    }

    void handleInput(LE3Input input) {
        if (input.keys["KEY_ESCAPE"]) m_engineState.notifyWantsQuit();

        if (input.isKeyDownEvent("KEY_F")) m_engineState.notifyWantsRelativeMouse(!m_engineState.isRelativeMouse());

        ////////////////////////
        // Camera Movement
        ////////////////////////
        cameraVelocity = glm::vec3();
        cameraRotation = glm::vec3();
        if (!LE3GetEditorManager().isActiveEdit()) {
            if (input.bLeftMouseDown || m_engineState.isRelativeMouse()) {
                if (input.keys["KEY_W"]) cameraVelocity.y = 1.f;
                else if (input.keys["KEY_S"]) cameraVelocity.y = -1.f;
                else cameraVelocity.y = 0.f;

                if (input.keys["KEY_D"]) cameraVelocity.x = 1.f;
                else if (input.keys["KEY_A"]) cameraVelocity.x = -1.f;
                else cameraVelocity.x = 0.f;

                if (input.keys["KEY_E"]) cameraVelocity.z = 1.f;
                else if (input.keys["KEY_Q"]) cameraVelocity.z = -1.f;
                else cameraVelocity.z = 0.f;

                cameraRotation.x = (float)input.xrel;
                cameraRotation.y = -(float)input.yrel;
            }
        }
        // If camera already moves, block edit
        LE3GetEditorManager().setEditBlocked(glm::length(cameraVelocity) > 0.f || glm::length(cameraRotation) > 0.f);
        
    }
};

int main() {
    LE3Application app(std::make_unique<Demo03_RacingShooter>());
    app.run();
    return 0;
}