#include "core/le3_game_base.h"
using namespace le3;

#include <filesystem>

#include <fmt/core.h>
#include <fmt/format.h>

#include "core/le3_config.h"
#include "core/le3_dat_filesystem.h"
#include "core/le3_engine_systems.h"
#include "core/le3_scene.h"

void LE3GameBase::init() {
    loadBootstrapConfig();
    registerBindings();
    loadProjectArchives();
    loadInitialScene();
    if (m_bDisplayFPS) initFPSDisplay();
}

void LE3GameBase::update(float deltaTime) {
    LE3GetSceneManager().updateScenes(deltaTime);
    updateFPSDisplay(deltaTime);
}

void LE3GameBase::render() {
    LE3GetActiveScene()->draw();
}

// Run the game bootstrap config file (which is in *.lua format); throws if the file cannot be read
void LE3GameBase::loadBootstrapConfig() {
    std::string bootstrapContent = LE3DatBuffer::loadFromSystem(LE3GetDataFilePath(m_bootstrapFile)).toString();
    LE3GetScriptSystem().doString(bootstrapContent);
}

// Mount the project archive, the extra data archives and all other *.dat files in the project root,
// then run all project scripts (load all class types)
void LE3GameBase::loadProjectArchives() {
    std::string projectPath = LE3GetConfig<std::string>("LE3GameConfig.ProjectPath");

    const std::string projectFilename = "le3proj.dat";
    LE3GetDatFileSystem().addArchive("le3proj", fmt::format("{}/{}", projectPath, projectFilename));
    for (const auto& [name, filename] : m_dataArchives)
        LE3GetDatFileSystem().addArchive(name, LE3GetDataFilePath(filename));

    for (const auto& entry : std::filesystem::directory_iterator(projectPath)) {
        if (entry.path().extension() == ".dat" && entry.path().filename().string() != projectFilename)
            LE3GetDatFileSystem().addArchive(entry.path().stem().string(), fmt::format("{}/{}", projectPath, entry.path().filename().string()));
    }

    if (LE3GetDatFileSystem().archiveExists("scripts")) {
        for (std::string script : LE3GetDatFileSystem().getFilesFromDir("/scripts")) {
            if (!script.ends_with(".lua")) continue;
            fmt::print("\tSCRIPT:{}\n", script);
            LE3GetScriptSystem().doFile(script);
        }
    }

    LE3GetAssetManager().reloadAssets();
}

// Load the initial scene on top of the shared scene, and make sure it has a player start
void LE3GameBase::loadInitialScene() {
    std::string initialSceneName = LE3GetConfig<std::string>("LE3GameConfig.InitialScene");
    LE3GetPhysicsManager().reset();
    LE3GetSceneManager().createScene("__main__", m_engineState, "");
    LE3GetSceneManager().getScene("__main__")->load("/le3proj/scenes/__shared__.lua");
    LE3GetSceneManager().getScene("__main__")->load(fmt::format("/le3proj/scenes/{}", initialSceneName));

    if (!LE3GetActiveScene()->getObject(LE3_PLAYERSTART_OBJECT_NAME)) {
        LE3GetScriptSystem().pushUserType<LE3Scene>(LE3GetActiveScene().get());
        LE3GetScriptSystem().setGlobal("_activeScene");
        LE3GetScriptSystem().doString(
            fmt::format("LE3PlayerStart.load(_activeScene, {{Name = \"{}\", Classname = \"{}\"}})",
                LE3_PLAYERSTART_OBJECT_NAME,
                LE3_PLAYERSTART_DEFAULT_CLASS
            ));
    }
}

void LE3GameBase::initFPSDisplay() {
    LE3GetAssetManager().addFont("F_default", "/engine/fonts/Tahoma.ttf", 32.0f);
    LE3GetActiveScene()->addUITextObject("fpsText", "F_default");
    m_fpsTextObject = LE3GetActiveScene()->getObject<LE3UITextObject>("fpsText");
    m_fpsTextObject->getTransform().setPosition(glm::vec3(-0.98f, 0.92f, 0.f));
    m_fpsTextObject->getTransform().setScale(glm::vec3(0.06f, 0.06f, 1.f));
    m_fpsTextObject->setText("FPS: 0");
    m_fpsTextObject->setTextColor(glm::vec4(0.f, 0.9f, 0.1f, 1.f));
}

void LE3GameBase::updateFPSDisplay(float deltaTime) {
    if (!m_fpsTextObject) return;
    m_fpsPrintTimer += deltaTime;
    if (m_fpsPrintTimer >= 0.25f) {
        m_fpsPrintTimer = 0.f;
        m_fpsTextObject->setText(fmt::format("FPS: {:.0f}", m_engineState.getFPS()));
    }
}
