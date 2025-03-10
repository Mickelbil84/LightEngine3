#pragma once

#include <string>
#include <vector>
#include <algorithm>
#include <filesystem>

namespace le3 {
    // For simplicity, this class only has static methods, as its API is only one method anyway, without state
    class LE3ToolPkg {
    public:
        static void run(std::string rootDir, std::string outDir, bool verbose = true);
    private:
        static void recurseDirectory(std::filesystem::directory_entry entry, std::vector<std::string>& res);
        static void fixPath(std::string& path);
    };
}