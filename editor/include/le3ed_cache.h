#pragma once

#include <le3.h>

namespace le3 {
    class LE3EditorCache {
    public:
        static void load() {
            LE3GetDatFileSystem().addArchive("le3edcache", "le3edcache.dat");
            if (!LE3GetDatFileSystem().fileExists("/le3edcache/exists")) {
                LE3GetDatFileSystem().appendFile("le3edcache", "/exists", LE3DatBuffer(), false);
                return;
            }
            for (auto filename : LE3GetDatFileSystem().getFilesFromDir("/le3edcache")) {
                if (!filename.ends_with(".lua")) continue;
                std::string content = LE3GetDatFileSystem().getFileContent(filename).toString();
                LE3GetScriptSystem().doString(content);
            }
        }
    };
}