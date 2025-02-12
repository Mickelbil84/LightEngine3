#include <le3.h>
#include "le3ed_logic.h"
using namespace le3;

int main() {
    do {
        if (LE3EngineSystems::instance().isRequestingReset()) LE3EngineSystems::instance().reset();
        LE3Application app(std::make_unique<LE3EditorLogic>());
        app.run();
        fmt::print("Request reset: {}\n", LE3EngineSystems::instance().isRequestingReset());
    } while(LE3EngineSystems::instance().isRequestingReset());
    return 0;
}