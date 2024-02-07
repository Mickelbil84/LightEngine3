#include <le3.h>
using namespace le3;

class Demo01_HelloOpenGL : public LE3GameLogic {
public:
    LE3Scene m_scene;
    std::shared_ptr<LE3Mesh<LE3Vertex3p3c>> m_triangle;

    void init() {
        LE3GetDatFileSystem().addArchive("demos", "demos.dat");

        LE3GetAssetManager().addShaderFromFile(
            "hello_opengl",
            "/demos/shaders/hello_opengl/hello_opengl.vs",
            "/demos/shaders/hello_opengl/hello_opengl.fs"
        );

        m_triangle = createHelloOpenGLTriangle();
    }
    void update(float deltaTime) {
        // ImGui::ShowDemoWindow();
    }
    void render() {
        LE3GetAssetManager().getShader("hello_opengl")->use();
        m_triangle->draw();
    }
};

int main() {
    LE3Application app(std::make_unique<Demo01_HelloOpenGL>());
    app.run();
    return 0;
}