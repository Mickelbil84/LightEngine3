#include <le3.h>
#include <ui/_NMB.h>
using namespace le3;

#include "le3game_constants.h"

class LE3Game : public LE3GameBase {
public:
    LE3Game() {
        setBootstrapFile(LE3_GAME_BOOTSTRAP_FILE); // The bootstrap file #define is defined in CMake!
        addDataArchive("demos", "demos.dat");
        setDisplayFPS(true);
    }

    void init() override {
        try {
            LE3GameBase::init();
        } catch (std::runtime_error& e) {
            NMB::show("ERROR", e.what(), NMB::Icon::ICON_ERROR);
            exit(-1);
        }
    }
};

int main() {
    LE3Application app(std::make_unique<LE3Game>());
    app.run();
    return 0;
}
