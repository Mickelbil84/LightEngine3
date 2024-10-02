#include <le3.h>
#include "le3ed_logic.h"
using namespace le3;

int main() {
    LE3Application app(std::make_unique<LE3EditorLogic>());
    app.run();
    return 0;
}