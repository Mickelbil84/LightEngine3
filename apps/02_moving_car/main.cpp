#include <le3.h>
using namespace le3;

#include <fmt/core.h>
using fmt::print, fmt::format;

#include <glm/gtx/string_cast.hpp>

class Demo02_MovingCar : public LE3GameLogic {
public:
    LE3Scene m_scene;
    glm::vec3 cameraVelocity, cameraRotation;

    float walkSpeed = 2.2f, sensitivity = 0.005f;

    void init() {
        m_scene.init();

        m_scene.addShaderFromFile(
            "hello_opengl",
            "./resources/shaders/moving_car/moving_car.vs",
            "./resources/shaders/moving_car/moving_car.fs"
        );
        m_scene.addMaterial("default", "hello_opengl");

        m_scene.addEmptyObject("player");
        m_scene.getObject("player")->getTransform().setPosition(glm::vec3(0.f, 0.f, 5.f));

        m_scene.addFreeCamera("camera", "player");
        m_scene.getMainCamera()->setAspectRatio(m_engineState.getAspectRatio());
        
        m_scene.addCube("cube", "default", glm::vec3(0.f), glm::vec3(1.f));
    }
    void update(float deltaTime) {
        m_scene.getMainCamera()->addPitchYaw(sensitivity * cameraRotation.y, -sensitivity * cameraRotation.x);
        m_scene.getMainCamera()->moveForward(deltaTime * walkSpeed * cameraVelocity.y);
        m_scene.getMainCamera()->moveRight(deltaTime * walkSpeed * cameraVelocity.x);
        m_scene.getMainCamera()->moveUp(deltaTime * walkSpeed * cameraVelocity.z);
        
        m_scene.update(deltaTime);  
    }
    void render() {
        m_scene.draw();
    }

    void handleInput(LE3Input input) {
        if (input.keys["KEY_ESCAPE"]) m_engineState.notifyWantsQuit();

        ////////////////////////
        // Camera Movement
        ////////////////////////
        cameraVelocity = glm::vec3();
        cameraRotation = glm::vec3();
        if (input.bLeftMouseDown) {
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
};

int main() {
    LE3Application app(std::make_unique<Demo02_MovingCar>());
    app.run();
    return 0;
}