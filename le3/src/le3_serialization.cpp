#include "le3_serialization.h"
#include "le3_engine_systems.h"
using namespace le3;

void LE3Serialization::dump(std::string table, std::string filename) {
    LE3GetScriptSystem().getGlobal("serialize");
    LE3GetScriptSystem().getGlobal(table);
    LE3GetScriptSystem().callFunction(1, 1);
    std::string content = table + " = " + LE3GetScriptSystem().getString(-1);
    LE3GetScriptSystem().pop(1);

    LE3DatBuffer buffer;
    buffer.fromString(content);
    LE3GetDatFileSystem().appendFile("editor", filename, buffer, true);
}