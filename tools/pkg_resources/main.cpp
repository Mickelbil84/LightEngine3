#include <string>
#include <vector>
#include <filesystem>

#include <fmt/core.h>
using fmt::format, fmt::print;

#include <le3.h>
using namespace le3;

void recurseDirectory(std::filesystem::directory_entry entry, std::vector<std::string>& res) {
    if (!entry.is_directory()) {
        if (!entry.path().filename().string().starts_with('.')) res.push_back(entry.path().string());
        return;
    }
    for (const auto& childEntry : std::filesystem::directory_iterator(entry.path())) 
        recurseDirectory(childEntry, res);
}

int main(int argc, char** argv) {
    LE3DatFileSystem datFilesystem;

    const std::string rootDir = std::string(argv[1]);
    const std::string outDir = std::string(argv[2]);

    for (const auto& entry : std::filesystem::directory_iterator(rootDir)) {
        if (!entry.is_directory() || entry.path().filename().string().starts_with('.')) continue;
        
        std::vector<std::string> files;
        recurseDirectory(entry, files);

        std::string archiveName = entry.path().filename().string();
        std::string archivePath = outDir + "/" + archiveName + ".dat";
        datFilesystem.addArchive(archiveName, archivePath);
        print("Archive {} @ {}\n", archiveName, archivePath);

        for (auto file : files) {
            // print("{}| {} --> {}\n", archiveName, file, file.substr(rootDir.size()));
            datFilesystem.appendFile(archiveName, file.substr(rootDir.size()), file, true);
        }
    }


    return 0;
}