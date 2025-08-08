#include <le3.h>
using namespace le3;

class LuaFlappy : public LE3GameLogic {
public:
    void init() override {
        // Create an empty scene and expose it to Lua
        LE3GetSceneManager().createScene("flappy", m_engineState, "");
        auto scene = LE3GetActiveScene();

        LE3GetScriptSystem().pushUserType<LE3Scene>(scene.get());
        LE3GetScriptSystem().setGlobal("_scene");

        // Load the Lua game logic and run its init routine
        LE3GetScriptSystem().doFile("/engine/scripts/flappy/flappy.lua");
        LE3GetScriptSystem().callFunction("init_flappy");
    }

    void update(float deltaTime) override {
        LE3GetScriptSystem().getGlobal("update_flappy");
        LE3GetScriptSystem().pushNumber(deltaTime);
        LE3GetScriptSystem().callFunction(1, 0);

        LE3GetSceneManager().updateScenes(deltaTime);
    }

    void render() override {
        LE3GetActiveScene()->draw();
    }
};

int main() {
    LE3Application app(std::make_unique<LuaFlappy>());
    app.run();
    return 0;
}
