#include "tools/le3_tool_pkg.h"
#include "le3_dat_filesystem.h"
using namespace le3;

#include <fmt/core.h>

void LE3ToolPkg::recurseDirectory(std::filesystem::directory_entry entry, std::vector<std::string>& res) {
    if (!entry.is_directory()) {
        if (!entry.path().filename().string().starts_with('.')) res.push_back(entry.path().string());
        return;
    }
    for (const auto& childEntry : std::filesystem::directory_iterator(entry.path())) 
        recurseDirectory(childEntry, res);
}

void LE3ToolPkg::fixPath(std::string& path) {
    std::replace(path.begin(), path.end(), '\\', '/');
}

void LE3ToolPkg::run(std::string rootDir, std::string outDir, bool verbose) {
    LE3DatFileSystem datFilesystem;

    fixPath(rootDir);
    fixPath(outDir);

    for (const auto& entry : std::filesystem::directory_iterator(rootDir)) {
        if (!entry.is_directory() || entry.path().filename().string().starts_with('.')) continue;
        
        std::vector<std::string> files;
        recurseDirectory(entry, files);

        std::string archiveName = entry.path().filename().string();
        std::string archivePath = outDir + "/" + archiveName + ".dat";
        try {
            std::filesystem::remove(archivePath);
        } catch (...) {
            if (verbose) fmt::print("Failed to remove archive {}\n", archivePath);
        }
        datFilesystem.addArchive(archiveName, archivePath);
        if (verbose) fmt::print("Archive {} @ {}\n", archiveName, archivePath);

        for (auto file : files) {
            fixPath(file);
            datFilesystem.appendFile(archiveName, file.substr(rootDir.size()), file, true);
        }
    }
}

