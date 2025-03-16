#include "le3ed_project.h"
#include "le3_engine_systems.h"
#include "le3ed_cache.h"
#include "tools/le3_tool_pkg.h"
using namespace le3;
#include <filesystem>

std::vector<std::pair<std::string, std::string>> LE3EditorProject::getProjectDatArchives() {
    std::string projectPath = LE3EditorCache::getMostRecentProject();
    std::vector<std::pair<std::string, std::string>> archives;
    for (const auto& entry : std::filesystem::directory_iterator(projectPath)) {
        if (entry.path().extension() == ".dat") {
            if (entry.path().filename().string() != LE3ED_PROJECT_FILENAME)
                archives.push_back(
                    std::make_pair(entry.path().stem().string(), projectPath + "/" + entry.path().filename().string())
                );
        }
    }
    return archives;
}

bool LE3EditorProject::isProjectDatArchive(std::string archiveName) {
    if (archiveName == "engine") return false;
    if (archiveName == "editor") return false;
    if (archiveName == "demos") return false;
    if (archiveName == "le3proj") return false;
    if (archiveName == "le3edcache") return false;
    return true;
}

void LE3EditorProject::reloadAssets() {
    std::string projectPath = LE3EditorCache::getMostRecentProject();
    LE3ToolPkg::run(projectPath, projectPath);
    LE3GetEditorManager().setSelectedFile("");
    LE3GetDatFileSystem().closeArchives(LE3EditorProject::isProjectDatArchive);
    for (auto [archiveName, archivePath] : LE3EditorProject::getProjectDatArchives()) {
        LE3GetDatFileSystem().addArchive(archiveName, archivePath);
    }
    LE3GetAssetManager().reloadAssets();
}