#include <memory>
#include <string>
#include <queue>
#include <iostream>

#include <fmt/core.h>
using fmt::format, fmt::print;

#include <lua.hpp>
#include <lauxlib.h>
#include <lualib.h>

#include <le3.h>
using namespace le3;


int main() {
    LE3DatFileSystem datFilesystem;
    datFilesystem.addArchive("engine", "engine.dat");

    // datFilesystem.appendFile("engine", 
    //     "/engine/shaders/blinn_phong/blinn_phong.vs.comp", 
    //     "./resources/shaders/blinn_phong/blinn_phong.vs", true);
    // datFilesystem.appendFile("engine", 
    //     "/engine/shaders/blinn_phong/blinn_phong.fs.comp", 
    //     "./resources/shaders/blinn_phong/blinn_phong.fs", true);

    for (auto path : datFilesystem.getFilesFromDir("/engine")) {
        print("{}\n", path);
        bool shouldDecompress = path.ends_with(".comp");
        print("{}\n----------------------------\n\n", datFilesystem.getFileContent(path, shouldDecompress).toString());
    }


    return 0;
}