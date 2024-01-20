#include <le3.h>
using namespace le3;

#include <fmt/core.h>
using fmt::print, fmt::format;

#include <glm/gtx/string_cast.hpp>

class Demo02_MovingCar : public LE3GameLogic {
public:
    LE3Scene m_scene;
    std::shared_ptr<LE3Mesh<LE3Vertex>> m_mesh;
    std::shared_ptr<LE3Model<LE3Vertex>> m_model;

    std::shared_ptr<LE3OrbitCamera> m_camera;
    glm::vec3 cameraVelocity, cameraRotation;
    float walkSpeed, sensitivity;

    void init() {
        m_scene.addShaderFromFile(
            "hello_opengl",
            "./resources/shaders/moving_car/moving_car.vs",
            "./resources/shaders/moving_car/moving_car.fs"
        );

        m_camera = std::make_shared<LE3OrbitCamera>();
        // m_camera->getTransform().setPosition(glm::vec3(0.f, 0.f, 2.0f));
        m_camera->setAspectRatio(m_engineState.getAspectRatio());
        m_camera->setOffset(glm::vec3(0.f, 0.f, 5.f));
        walkSpeed = 2.2f;
        sensitivity = 0.005f;

        m_mesh = CreateBox(0.f, 0.f, 0.f, 1.f, 1.f, 1.f);
        m_model = std::make_shared<LE3Model<LE3Vertex>>(m_mesh, nullptr);
    }
    void update(float deltaTime) {
        LE3Transform& cameraTranform = m_camera->getTransform();
        cameraTranform.setPosition(
            cameraTranform.getPosition() + 
            (float)deltaTime * walkSpeed * cameraVelocity.y *  cameraTranform.getForward() + 
            (float)deltaTime * walkSpeed * cameraVelocity.x *  cameraTranform.getRight() + 
            (float)deltaTime * walkSpeed * cameraVelocity.z *  glm::vec3(0.f, 1.f, 0.f)
        );
        m_camera->addPitchYaw(sensitivity * cameraRotation.y, -sensitivity * cameraRotation.x);
        m_camera->update(deltaTime);        
    }
    void render() {
        m_scene.getShader("hello_opengl")->use();
        m_scene.getShader("hello_opengl")->uniform("view", m_camera->getViewMatrix());
        m_scene.getShader("hello_opengl")->uniform("projection", m_camera->getProjectionMatrix());

        m_scene.getShader("hello_opengl")->uniform("model", m_model->getTransform().getTransformMatrix());
        m_model->draw();
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