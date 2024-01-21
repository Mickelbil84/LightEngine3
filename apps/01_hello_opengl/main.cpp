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

        m_triangle = createHelloOpenGLTriangle();
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