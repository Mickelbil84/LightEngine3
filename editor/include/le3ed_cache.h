#pragma once

#include <le3.h>

namespace le3 {
    class LE3EditorCache {
    public:
        static void load();

        static void setMostRecentProject(std::string path); // This also adds to recent projects list
        static std::string getMostRecentProject();
        static std::vector<std::string> getRecentProjects();

    private:
    };
}