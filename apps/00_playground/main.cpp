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
    LE3DatArchive engineDat("engine.dat");
    print("Data size: {}\n", engineDat.getDataSize());

    // Create demo file
    // LE3DatBuffer file1 = LE3DatBuffer::loadFromSystem("./resources/shaders/blinn_phong/blinn_phong.vs");
    // LE3DatBuffer file2 = LE3DatBuffer::loadFromSystem("./resources/shaders/blinn_phong/blinn_phong.fs");
    // engineDat.appendFile("engine/shaders/blinn_phong/blinn_phong.vs", file1, false);
    // engineDat.appendFile("engine/shaders/blinn_phong/blinn_phong.fs", file2, false);

    for (auto kv : engineDat.getFileInfos()) {
        print("\t{}\n", kv.second.str());
    }
    
    print("\n\n{}\n--------------\n", engineDat.getFileContent("engine/shaders/blinn_phong/blinn_phong.vs", false).toString());

    LE3DatBuffer file1_mod; file1_mod.fromString("Oops I broke everything :(");
    // engineDat.appendFile("engine/shaders/blinn_phong/blinn_phong.vs", file1_mod, false);

    engineDat.defragmentArchive();

    for (auto kv : engineDat.getFileInfos()) {
        print("\t{}\n", kv.second.str());
    }
    
    print("\n\n{}\n--------------\n", engineDat.getFileContent("engine/shaders/blinn_phong/blinn_phong.vs", false).toString());



    return 0;
}