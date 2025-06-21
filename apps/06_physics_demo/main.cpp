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
    
    float walkSpeed = 2.2f, sensitivity = 0.005f;

    void init() {
        // Load the platformer example project
        LE3GetDatFileSystem().addArchive("demos", "demos.dat");
        std::string archives[] = {
            "le3proj", "meshes", "test", "textures"
        };
        for (auto archive : archives)
            LE3GetDatFileSystem().addArchive(archive, fmt::format("../examples/platformer/{}.dat", archive));

        LE3GetPhysicsManager().setPhysicsEnabled(false);

        // Setup the demo scene
        LE3GetSceneManager().createScene("scene", m_engineState, "/le3proj/scenes/physics-test.lua");
        LE3GetActiveScene()->setBackgroundColor(glm::vec3(100.f/255.f, 149.f/255.f, 253.f/255.f));
        LE3GetActiveScene()->drawDebug = [this]() { this->renderDebug(); };

        LE3GetActiveScene()->addFreeCamera("camera");
        LE3GetActiveScene()->getObject("camera")->getTransform().setPosition(glm::vec3(0, 0, 5));
    }
    void update(float deltaTime) {
        // Update
        LE3GetActiveScene()->getMainCamera()->addPitchYaw(sensitivity * cameraRotation.y, -sensitivity * cameraRotation.x);
        LE3GetActiveScene()->getMainCamera()->moveForward(deltaTime * walkSpeed * cameraVelocity.y);
        LE3GetActiveScene()->getMainCamera()->moveRight(deltaTime * walkSpeed * cameraVelocity.x);
        LE3GetActiveScene()->getMainCamera()->moveUp(deltaTime * walkSpeed * cameraVelocity.z);

        // Update scenes        
        LE3GetSceneManager().updateScenes(deltaTime);
    }

    void render() {
        LE3GetSceneManager().getScene("scene")->draw();

        ImGui::Begin("06 - Physics Demo");

            const char* onText = "Turn Physics On";
            const char* offText = "Turn Physics Off";
            if (ImGui::Button(LE3GetPhysicsManager().isPhysicsEnabled() ? offText : onText)) {
                LE3GetPhysicsManager().setPhysicsEnabled(!LE3GetPhysicsManager().isPhysicsEnabled());
            }

            glm::vec3 cameraPos = LE3GetActiveScene()->getObject("camera")->getTransform().getPosition();
            ImGui::Text("Camera pos: %f,%f,%f", cameraPos.x, cameraPos.y, cameraPos.z);

            glm::vec3 wheelPos = LE3GetActiveScene()->getObject("CarWheel_1")->getTransform().getPosition();
            glm::quat wheelRot = LE3GetActiveScene()->getObject("CarWheel_1")->getTransform().getRotation();
            ImGui::Text("Wheel pos: %f,%f,%f", wheelPos.x, wheelPos.y, wheelPos.z);
            ImGui::Text("Wheel rot: %f,%f,%f, %f", wheelRot.x, wheelRot.y, wheelRot.z, wheelRot.w);



        ImGui::End();
    }

    void renderDebug() {
    }

    void handleInput(LE3Input input) {
        if (input.keys["KEY_ESCAPE"]) m_engineState.notifyWantsQuit();

        if (input.isKeyDownEvent("KEY_F")) m_engineState.notifyWantsRelativeMOuse(!m_engineState.isRelativeMouse());

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