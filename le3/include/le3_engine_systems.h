#pragma once

#include <memory>

#include "le3_dat_filesystem.h"
#include "le3_script_system.h"
#include "le3_primitives.h"

namespace le3 {
    // Singleton for various (global) engine systems, which are not specific to any scene
    class LE3EngineSystems {
    public:
        static LE3EngineSystems& instance() {
            static LE3EngineSystems* instance_ = new LE3EngineSystems();
            return *instance_;
        }

        inline LE3DatFileSystem& getDatFileSystem() { return g_datFilesystem; }
        inline LE3ScriptSystem& getScriptSystem() { return g_scriptSystem; }
        inline LE3ScreenRectPtr getScreenRect() { return g_screenRect; }

    private:
        LE3EngineSystems() {
            // Load engine data and scripts
            g_datFilesystem.addArchive("engine", "engine.dat");
            for (auto filename : g_datFilesystem.getFilesFromDir("/engine/scripts")) {
                std::string content = g_datFilesystem.getFileContent(filename).toString();
                g_scriptSystem.doString(content);
            }

            // Create a new screen rect
            g_screenRect = createScreenRect();
        }

        LE3DatFileSystem g_datFilesystem;
        LE3ScriptSystem g_scriptSystem;
        LE3ScreenRectPtr g_screenRect;
    };

    #define LE3GetDatFileSystem LE3EngineSystems::instance().getDatFileSystem
    #define LE3GetScriptSystem LE3EngineSystems::instance().getScriptSystem
}