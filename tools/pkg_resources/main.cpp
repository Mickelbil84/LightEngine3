#include <tools/le3_tool_pkg.h>

int main(int argc, char** argv) {
    // std::string rootDir = std::string(argv[1]);
    // std::string outDir = std::string(argv[2]);

    std::string rootDir = "C:\\Users\\micke\\Documents\\LightEngine3\\resources";
    std::string outDir = "C:\\Users\\micke\\Documents\\LightEngine3\\bin";

    le3::LE3ToolPkg::run(rootDir, outDir);
    return 0;
}