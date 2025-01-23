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
        LE3GetDatFileSystem().addArchive("demos", "demos.dat");

        LE3GetSceneManager().createScene("scene", m_engineState, "");
        LE3GetSceneManager().getActiveScene()->drawDebug = [this]() { this->renderDebug(); };
        LE3GetSceneManager().getActiveScene()->addFreeCamera("camera");
        LE3GetSceneManager().getActiveScene()->setBackgroundColor(glm::vec3(100.f/255.f, 149.f/255.f, 253.f/255.f));

        LE3GetSceneManager().getActiveScene()->addPointCloud("pointcloud");
        // for (int i = -250; i < 250; i++)
        // for (int j = -250; j < 250; j++) {
        //     float x = i / 500.f;
        //     float y = j / 500.f;
        //     float z = sqrtf(1 - x * x - y * y);
        //     glm::vec3 p(x, z, y);
        //     LE3GetSceneManager().getActiveScene()->getObject<LE3PointCloud>("pointcloud")->addPoint(p, p, 0.5f * p + 0.5f);
        // }
        LE3GetSceneManager().getActiveScene()->getObject<LE3PointCloud>("pointcloud")->fromFile("/demos/models/pointclouds/lab446a_aligned.ply", true);
        LE3GetSceneManager().getActiveScene()->getObject<LE3PointCloud>("pointcloud")->create();
        LE3GetSceneManager().getActiveScene()->getObject<LE3PointCloud>("pointcloud")->setPointSize(2.f);
        // LE3GetSceneManager().getActiveScene()->getObject<LE3PointCloud>("pointcloud")->getTransform().setRotationRPY(1.57f, 0.f, 0.f);

        LE3GetSceneManager().getActiveScene()->addAmbientLight("ambient");
        LE3GetSceneManager().getActiveScene()->getObject<LE3AmbientLight>("ambient")->setIntensity(0.8f);
        LE3GetSceneManager().getActiveScene()->addDirectionalLight("sun");
        LE3GetSceneManager().getActiveScene()->getObject<LE3DirectionalLight>("sun")->setIntensity(0.8f);
        LE3GetSceneManager().getActiveScene()->getObject<LE3DirectionalLight>("sun")->getTransform().setRotationRPY(0.f, 0.f, -0.5f);

    }
    void update(float deltaTime) {
        // Setup FPS camera
        LE3GetSceneManager().getActiveScene()->getMainCamera()->addPitchYaw(sensitivity * cameraRotation.y, -sensitivity * cameraRotation.x);
        LE3GetSceneManager().getActiveScene()->getMainCamera()->moveForward(deltaTime * walkSpeed * cameraVelocity.y);
        LE3GetSceneManager().getActiveScene()->getMainCamera()->moveRight(deltaTime * walkSpeed * cameraVelocity.x);
        LE3GetSceneManager().getActiveScene()->getMainCamera()->moveUp(deltaTime * walkSpeed * cameraVelocity.z);

        // Update scenes        
        LE3GetSceneManager().updateScenes(deltaTime);
    }

    void render() {
        LE3GetSceneManager().getScene("scene")->draw();
    }

    void renderDebug() {
        // LE3GetVisualDebug().drawDebugCone(glm::vec3(0.f), 1.f, 2.f, glm::vec3(0.f, 1.f, 0.f));
        LE3GetVisualDebug().drawDebugBox(glm::vec3(0.f), glm::quat(), glm::vec3(0.2f), glm::vec3(0.f, 1.f, 0.f));
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