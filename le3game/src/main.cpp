#include <le3.h>
using namespace le3;

#include <filesystem>

#include <fmt/core.h>
#include <NMB/NMB.h>

#include "le3game_constants.h"

class LE3Game : public LE3GameLogic {
public:
    void init() {
        loadBoostrapConfig();
        loadProjectArchives();
        loadInitialScene();
    }
    void update(float deltaTime) {
        LE3GetSceneManager().updateScenes(deltaTime);
    }

    void render() {
        LE3GetActiveScene()->draw();
    }

    void renderDebug() {
    }

    void handleInput(LE3Input input) {
    }

private:
    // Load the game bootstrap config file (which is in *.lua format)
    void loadBoostrapConfig() {
        std::string bootstrapContent;
        try {
            bootstrapContent = LE3DatBuffer::loadFromSystem(LE3_GAME_BOOTSTRAP_FILE).toString(); // The bootstrap file #define is defined in CMake!
        } catch (std::runtime_error e) {
            NMB::show("ERROR", "Could not read boostrap file! Closing...", NMB::Icon::ICON_ERROR);
            exit(-1);
        }
        LE3GetScriptSystem().doString(bootstrapContent);
        
    }

    // Load all *.dat files that are in the project root
    void loadProjectArchives() {    
        std::string projectPath = LE3GetConfig<std::string>("LE3GameConfig.ProjectPath");

        // Preload also project & demos archives
        std::string projectFilename = "le3proj.dat";
        LE3GetDatFileSystem().addArchive("le3proj", fmt::format("{}/{}", projectPath, projectFilename));
        LE3GetDatFileSystem().addArchive("demos", "demos.dat");

        // Add the rest archives available
        for (const auto& entry : std::filesystem::directory_iterator(projectPath)) {
            if (entry.path().extension() == ".dat") {
                if (entry.path().filename().string() != projectFilename)
                    LE3GetDatFileSystem().addArchive(entry.path().stem().string(), fmt::format("{}/{}", projectPath, entry.path().filename().string()));
            }
        }

        // Run all game scripts (load all class types)
        if (LE3GetDatFileSystem().archiveExists("scripts")) {
            for (std::string script : LE3GetDatFileSystem().getFilesFromDir("/scripts")) {
                if (!script.ends_with(".lua")) continue;
                LE3GetScriptSystem().doFile(script);
            }
        }

        LE3GetAssetManager().reloadAssets();
    }

    // Load initial scene
    void loadInitialScene() {
        std::string initialSceneName = LE3GetConfig<std::string>("LE3GameConfig.InitialScene");
        LE3GetPhysicsManager().reset();
        LE3GetSceneManager().createScene("__main__", m_engineState, "");
        LE3GetSceneManager().getScene("__main__")->load("/le3proj/scenes/__shared__.lua");
        LE3GetSceneManager().getScene("__main__")->load(fmt::format("/le3proj/scenes/{}", initialSceneName));

        // LE3GetActiveScene()->addFreeCamera("camera");
        if (!LE3GetActiveScene()->getObject(LE3_PLAYERSTART_OBJECT_NAME)) {
            LE3GetScriptSystem().pushUserType<LE3Scene>(LE3GetActiveScene().get());
            LE3GetScriptSystem().setGlobal("_activeScene");
            LE3GetScriptSystem().doString(
                fmt::format("LE3PlayerStart.load(_activeScene, {{Name = \"{}\", Classname = \"{}\"}})",
                    LE3_PLAYERSTART_OBJECT_NAME,
                    "TPSCamPlayer" // LE3_PLAYERSTART_DEFAULT_CLASS
                ));
        }
    }
};

int main() {
    LE3Application app(std::make_unique<LE3Game>());
    app.run();
    return 0;
}