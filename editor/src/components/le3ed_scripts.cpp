#include "components/le3ed_scripts.h"
#include "commands/le3ed_com_property_change.h"
#include <le3.h>
#include "le3ed_cache.h"
using namespace le3;

void LE3EditorScripts::init() {
    // Setup editor scripts
    LE3EditorCache::load();
    LE3GetScriptSystem().createEmptyTable("LE3EditorConfig");
    for (std::string script : LE3GetDatFileSystem().getFilesFromDir("/editor/scripts")) {
        if (!script.ends_with(".lua")) continue;
        LE3GetScriptSystem().doFile(script);
    }
    for (std::string script : LE3GetDatFileSystem().getFilesFromDir("/editor/config")) {
        if (!script.ends_with(".lua")) continue;
        LE3GetScriptSystem().doFile(script);
    }

    // Bind custom editor Lua "libraries"
    LE3EditorComPropertyChange::registerLua();
}
void LE3EditorScripts::update(float deltaTime) {
}