#pragma once

#include <memory>

#include "le3_dat_filesystem.h"
#include "le3_script_system.h"
#include "le3_primitives.h"
#include "le3_imgui_utils.h"
#include "le3_asset_manager.h"
#include "le3_visual_debug.h"
#include "le3_scene_manager.h"
#include "le3_editor_manager.h"

namespace le3 {
    // Singleton for various (global) engine systems, which are not specific to any scene
    class LE3EngineSystems {
    public:
        static LE3EngineSystems& instance();

        // Called before initializing any other system (so that we can call bare-bones code)
        void preload(bool headless = false) {
            // Load engine data, config and scripts
            g_datFilesystem.addArchive("engine", "engine.dat");
            std::string dirs[] = {
                "/engine/config", "/engine/scripts"
            };
            for (int i = 0; i < sizeof(dirs) / sizeof(std::string); i++) {
                for (auto filename : g_datFilesystem.getFilesFromDir(dirs[i])) {
                    std::string content = g_datFilesystem.getFileContent(filename).toString();
                    g_scriptSystem.doString(content);
                }
            }

            g_headlessEngine = headless;
        }

        void init() {
            // Init the asset manager
            g_assetManager.init();

            // Once everyhing is loaded, we can apply our configs
            // (on everything that is done from the Lua script engine)
            g_scriptSystem.getGlobal("apply_all_configs");
            g_scriptSystem.callFunction(0, 0);
        }

        inline LE3DatFileSystem& getDatFileSystem() { return g_datFilesystem; }
        inline LE3ScriptSystem& getScriptSystem() { return g_scriptSystem; }
        inline LE3AssetManager& getAssetManager() { return g_assetManager; }
        inline LE3VisualDebug& getVisualDebug() { return g_visualDebug; }
        inline LE3ImGuiUtils& getImGuiUtils() { return g_imGuiUtils; }
        inline LE3SceneManager& getSceneManager() { return g_sceneManager; }
        inline LE3EditorManager& getEditorManager() { return g_editorManager; }
        inline bool isHeadless() { return g_headlessEngine; }
        
    private:
        LE3EngineSystems() {
        }

        LE3DatFileSystem g_datFilesystem;
        LE3ScriptSystem g_scriptSystem;
        LE3ImGuiUtils g_imGuiUtils;
        LE3AssetManager g_assetManager;
        LE3VisualDebug g_visualDebug;
        LE3SceneManager g_sceneManager;
        LE3EditorManager g_editorManager;

        bool g_headlessEngine;
    };

    #define LE3GetDatFileSystem LE3EngineSystems::instance().getDatFileSystem
    #define LE3GetScriptSystem LE3EngineSystems::instance().getScriptSystem
    #define LE3GetAssetManager LE3EngineSystems::instance().getAssetManager
    #define LE3GetVisualDebug LE3EngineSystems::instance().getVisualDebug
    #define LE3GetImGuiUtils LE3EngineSystems::instance().getImGuiUtils
    #define LE3GetSceneManager LE3EngineSystems::instance().getSceneManager
    #define LE3GetEditorManager LE3EngineSystems::instance().getEditorManager

    #define LE3GetActiveScene LE3GetSceneManager().getActiveScene
}