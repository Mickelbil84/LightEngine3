#include "le3ed_cache.h"
using namespace le3;

void LE3EditorCache::load() {
    LE3GetDatFileSystem().addArchive("le3edcache", "le3edcache.dat");
    if (!LE3GetDatFileSystem().fileExists("/le3edcache/exists")) {
        LE3GetDatFileSystem().appendFile("le3edcache", "/le3edcache/exists", LE3DatBuffer(), false);
    }
    for (auto filename : LE3GetDatFileSystem().getFilesFromDir("/le3edcache")) {
        if (!filename.ends_with(".lua")) continue;
        std::string content = LE3GetDatFileSystem().getFileContent(filename).toString();
        LE3GetScriptSystem().doString(content);
    }

    // Load cache (found in `editor` archive)
    LE3GetScriptSystem().doString(LE3GetDatFileSystem().getFileContent("/editor/scripts/editor_cache.lua").toString());
    fmt::print("{}\n", LE3GetDatFileSystem().getFileContent("/editor/scripts/editor_cache.lua").toString());
    LE3GetScriptSystem().callFunction("init_editor_cache"); // If there is not editor cache
}

void LE3EditorCache::setMostRecentProject(std::string path) {

}
std::string LE3EditorCache::getMostRecentProject() {

}
std::vector<std::string> LE3EditorCache::getRecentProjects() {

}