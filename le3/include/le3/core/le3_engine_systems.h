#pragma once

#include <memory>

#include "core/le3_input.h"
#include "core/le3_dat_filesystem.h"
#include "core/le3_scene_manager.h"
#include "core/le3_editor_manager.h"
#include "core/le3_event_manager.h"
#include "core/le3_asset_manager.h"

#include "graphics/le3_visual_debug.h"
#include "graphics/le3_primitives.h"

#include "scripting/le3_script_system.h"
#include "ui/le3_imgui_utils.h"
#include "physics/le3_physics_manager.h"

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
            std::vector<std::string> gameplayScripts;
            for (int i = 0; i < sizeof(dirs) / sizeof(std::string); i++) {
                for (auto filename : g_datFilesystem.getFilesFromDir(dirs[i])) {
                    if (filename.find("/gameplay/") != std::string::npos) {
                        gameplayScripts.push_back(filename);
                        continue;
                    }
                    std::string content = g_datFilesystem.getFileContent(filename).toString();
                    g_scriptSystem.doString(content);
                }
            }
            // Special case: the gameplay scripts should always run last
            for (auto filename : gameplayScripts)
                g_scriptSystem.doString(g_datFilesystem.getFileContent(filename).toString());

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
        void reset(); // Reset all editor systems

        inline LE3DatFileSystem& getDatFileSystem() { return g_datFilesystem; }
        inline LE3ScriptSystem& getScriptSystem() { return g_scriptSystem; }
        inline LE3AssetManager& getAssetManager() { return g_assetManager; }
        inline LE3VisualDebug& getVisualDebug() { return g_visualDebug; }
        inline LE3ImGuiUtils& getImGuiUtils() { return g_imGuiUtils; }
        inline LE3SceneManager& getSceneManager() { return g_sceneManager; }
        inline LE3EditorManager& getEditorManager() { return g_editorManager; }
        inline LE3EventManager& getEventManager() { return g_eventManager; }
        inline LE3PhysicsManager& getPhysicsManager() { return g_physicsManager; }
        inline LE3EngineDebug& getEngineDebug() { return g_engineDebug; }
        inline bool isHeadless() { return g_headlessEngine; }

        inline bool isRequestingReset() const { return g_requestReset; }
        inline void requestReset() { g_requestReset = true; }

        inline bool isEditModeEngine() const { return g_editModeEngine; }
        inline void setEditModeEngine(bool editMode) { g_editModeEngine = editMode; }

        inline LE3Input getRecentInput() const { return g_input; }
        inline void setRecentInput(LE3Input input) { g_input = input; }

        inline LE3EngineState* getEngineState() { return g_engineState; }
        inline void setEngineState(LE3EngineState* engineState) { g_engineState = engineState; }
        
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
        LE3EventManager g_eventManager;
        LE3PhysicsManager g_physicsManager;
        LE3EngineDebug g_engineDebug;

        bool g_headlessEngine;
        bool g_editModeEngine = false; // If true, then no scripts or physics run
        bool g_requestReset = false;
        LE3Input g_input; // Store the most recent input, mostly for script bindings
        LE3EngineState* g_engineState = nullptr;
    };

    #define LE3GetDatFileSystem LE3EngineSystems::instance().getDatFileSystem
    #define LE3GetScriptSystem LE3EngineSystems::instance().getScriptSystem
    #define LE3GetAssetManager LE3EngineSystems::instance().getAssetManager
    #define LE3GetVisualDebug LE3EngineSystems::instance().getVisualDebug
    #define LE3GetImGuiUtils LE3EngineSystems::instance().getImGuiUtils
    #define LE3GetSceneManager LE3EngineSystems::instance().getSceneManager
    #define LE3GetEditorManager LE3EngineSystems::instance().getEditorManager
    #define LE3GetEventManager LE3EngineSystems::instance().getEventManager
    #define LE3GetPhysicsManager LE3EngineSystems::instance().getPhysicsManager
    #define LE3GetEngineDebug LE3EngineSystems::instance().getEngineDebug

    #define LE3GetActiveScene LE3GetSceneManager().getActiveScene
    #define LE3GetInput LE3EngineSystems::instance().getRecentInput
    #define LE3GetEngineState LE3EngineSystems::instance().getEngineState
}