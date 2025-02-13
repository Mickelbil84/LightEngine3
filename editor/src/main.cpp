#include <le3.h>
#include "le3ed_logic.h"
#include "le3ed_project_browser.h"
using namespace le3;

int main(int argc, char** argv) {
    do {        
        // Run the project browser
        if (LE3EngineSystems::instance().isRequestingReset()) LE3EngineSystems::instance().reset();
        LE3Application browser(std::make_unique<LE3EditorProjectBrowser>());
        browser.getSettings().bImGuiDocking = false;
        browser.run();

        // Run the project browser
        LE3EngineSystems::instance().reset();
        LE3Application app(std::make_unique<LE3EditorLogic>());
        app.run();
    } while(LE3EngineSystems::instance().isRequestingReset());
    return 0;
}