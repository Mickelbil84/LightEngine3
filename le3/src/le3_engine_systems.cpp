#include "le3_engine_systems.h"
using namespace le3;

LE3EngineSystems& LE3EngineSystems::instance() {
    static LE3EngineSystems* instance_ = new LE3EngineSystems();
    return *instance_;
}

void LE3EngineSystems::reset() {
    // g_datFilesystem = LE3DatFileSystem();
    g_scriptSystem = LE3ScriptSystem();
    g_imGuiUtils = LE3ImGuiUtils();
    g_assetManager = LE3AssetManager();
    g_visualDebug = LE3VisualDebug();
    g_sceneManager = LE3SceneManager();
    g_editorManager = LE3EditorManager();
    g_eventManager = LE3EventManager();
}