#include <le3.h>
using namespace le3;

#include <fmt/core.h>
using fmt::print;

#include <glm/gtx/string_cast.hpp>

class Demo02_MovingCar : public LE3GameLogic {
public:
    LE3Scene m_scene;
    std::shared_ptr<LE3Mesh<LE3Vertex>> m_mesh;
    std::shared_ptr<LE3Camera> m_camera;

    void init() {
        m_scene.addShaderFromFile(
            "hello_opengl",
            "./resources/shaders/moving_car/moving_car.vs",
            "./resources/shaders/moving_car/moving_car.fs"
        );

        m_camera = std::make_shared<LE3Camera>();
        m_camera->getTransform().setPosition(glm::vec3(0.f, 0.f, 2.0f));
        m_camera->setAspectRatio(m_engineState.getAspectRatio());
        m_mesh = CreateBox(0.f, 0.f, 0.f, 1.f, 1.f, 1.f);
    }
    void update(float deltaTime) {
        // ImGui::ShowDemoWindow();
    }
    void render() {
        m_scene.getShader("hello_opengl")->use();
        m_scene.getShader("hello_opengl")->uniform("model", glm::mat4(1.f));
        m_scene.getShader("hello_opengl")->uniform("view", m_camera->getViewMatrix());
        m_scene.getShader("hello_opengl")->uniform("projection", m_camera->getProjectionMatrix());

        m_mesh->draw();
    }
};

int main() {
    LE3Application app(std::make_unique<Demo02_MovingCar>());
    app.run();
    return 0;
}