#pragma once

#include <string>
#include <vector>

namespace le3 {

    const std::string LE3ED_PROJECT_FILENAME = "le3proj.dat";
    const std::string LE3ED_PROJECT_ARCHIVE = "le3proj";
    const std::string LE3ED_PROJECT_CONFIG = "/" + LE3ED_PROJECT_ARCHIVE + "/project_config.lua";
    const std::string LE3ED_PROJECT_ASSETS = "/" + LE3ED_PROJECT_ARCHIVE + "/assets.lua";
    const std::string LE3ED_PROJECT_SCENES_ROOT = "/" + LE3ED_PROJECT_ARCHIVE + "/scenes/";

    class LE3EditorProject {
    public:
        static std::vector<std::pair<std::string, std::string>> getProjectDatArchives();
        static bool isProjectDatArchive(std::string archiveName);
        static void reloadAssets();
    };
}