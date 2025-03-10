#include <tools/le3_tool_pkg.h>

int main(int argc, char** argv) {
    std::string rootDir = std::string(argv[1]);
    std::string outDir = std::string(argv[2]);

    le3::LE3ToolPkg::run(rootDir, outDir);
    return 0;
}