#include <le3.h>
#include "le3ed_logic.h"
#include "le3ed_project_browser.h"
using namespace le3;

int main(int argc, char** argv) {
    do {
        if (LE3EngineSystems::instance().isRequestingReset()) LE3EngineSystems::instance().reset();
        LE3Application app(std::make_unique<LE3EditorLogic>());
        app.run();
        fmt::print("Request reset: {}\n", LE3EngineSystems::instance().isRequestingReset());
    } while(LE3EngineSystems::instance().isRequestingReset());
    return 0;
}