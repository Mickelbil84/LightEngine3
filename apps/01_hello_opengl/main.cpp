#include <le3.h>
using namespace le3;

class Demo01_HelloOpenGL : public LE3GameLogic {
public:
    void update(float deltaTime) {
        ImGui::ShowDemoWindow();
    }
};

int main() {
    LE3Application app(std::make_unique<Demo01_HelloOpenGL>());
    app.run();
    return 0;
}