#include <le3.h>
using namespace le3;

class Demo01_HelloOpenGL : public LE3GameLogic {
public:
    LE3Scene m_scene;

    void init() {
        m_scene.addShaderFromFile(
            "hello_opengl",
            "./resources/shaders/hello_opengl/hello_opengl.vs",
            "./resources/shaders/hello_opengl/hello_opengl.fs"
        );
    }
    void update(float deltaTime) {
        ImGui::ShowDemoWindow();
    }
};

int main() {
    LE3Application app(std::make_unique<Demo01_HelloOpenGL>());
    app.run();
    return 0;
}