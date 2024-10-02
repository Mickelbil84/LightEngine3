#include <le3.h>

namespace le3 {
    class LE3EditorLogic  : public LE3GameLogic {
    public:
        void init();
        void update(float deltaTime);
        void render();
        void renderDebug();
        void handleInput(LE3Input input);
    };
}