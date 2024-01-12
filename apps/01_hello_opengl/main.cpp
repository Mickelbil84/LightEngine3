#include <le3_application.h>
using namespace le3;

int main() {

    LE3Application app(std::make_unique<LE3GameLogic>());
    app.run();
    return 0;
}