#include "le3_engine_systems.h"
using namespace le3;

LE3EngineSystems& LE3EngineSystems::instance() {
    static LE3EngineSystems* instance_ = new LE3EngineSystems();
    return *instance_;
}

void LE3EngineSystems::reset() {
    g_datFilesystem.reset();
    g_scriptSystem.reset();
    g_imGuiUtils.reset();
    g_assetManager.reset();
    g_visualDebug.reset();
    g_sceneManager.reset();
    g_editorManager.reset();
    g_eventManager.reset();
    
    // preload(g_headlessEngine);
    // init();

    g_requestReset = false;
}