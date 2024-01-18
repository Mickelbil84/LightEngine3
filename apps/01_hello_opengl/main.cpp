#include <le3.h>
using namespace le3;

class Demo01_HelloOpenGL : public LE3GameLogic {
public:
    LE3Scene m_scene;
    std::shared_ptr<LE3Mesh<LE3Vertex3p3c>> m_triangle;

    void init() {
        m_scene.addShaderFromFile(
            "hello_opengl",
            "./resources/shaders/hello_opengl/hello_opengl.vs",
            "./resources/shaders/hello_opengl/hello_opengl.fs"
        );

        std::vector<LE3Vertex3p3c> vertices(3);
        vertices[0].position[0] = .5f * -1.f; vertices[0].position[1] = .5f * -1.f; vertices[0].position[2] = .5f * 0.f;
        vertices[1].position[0] = .5f *  0.f; vertices[1].position[1] = .5f *  1.f; vertices[1].position[2] = .5f * 0.f;
        vertices[2].position[0] = .5f *  1.f; vertices[2].position[1] = .5f * -1.f; vertices[2].position[2] = .5f * 0.f;

        vertices[0].color[0] =  1.f; vertices[0].color[1] =  0.f; vertices[0].color[2] = 0.f;
        vertices[1].color[0] =  0.f; vertices[1].color[1] =  1.f; vertices[1].color[2] = 0.f;
        vertices[2].color[0] =  0.f; vertices[2].color[1] =  0.f; vertices[2].color[2] = 1.f;
        m_triangle = std::make_shared<LE3Mesh<LE3Vertex3p3c>>(vertices);
    }
    void update(float deltaTime) {
        // ImGui::ShowDemoWindow();
    }
    void render() {
        m_scene.getShader("hello_opengl")->use();
        m_triangle->draw();
    }
};

int main() {
    LE3Application app(std::make_unique<Demo01_HelloOpenGL>());
    app.run();
    return 0;
}