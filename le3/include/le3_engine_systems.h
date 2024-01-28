#pragma once

#include <memory>

#include "le3_dat_filesystem.h"

namespace le3 {
    // Singleton for various (global) engine systems, which are not specific to any scene
    class LE3EngineSystems {
    public:
        static LE3EngineSystems& instance() {
            static LE3EngineSystems* instance_ = new LE3EngineSystems();
            return *instance_;
        }

        inline LE3DatFileSystem& getDatFilesystem() { return g_datFilesystem; }

    private:
        LE3EngineSystems() {
            g_datFilesystem.addArchive("engine", "engine.dat");
        }

        LE3DatFileSystem g_datFilesystem;
    };
}