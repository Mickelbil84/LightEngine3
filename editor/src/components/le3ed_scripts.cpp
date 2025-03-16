#include "components/le3ed_scripts.h"
#include "commands/le3ed_com_property_change.h"
#include <le3.h>
#include "le3ed_cache.h"
#include "le3ed_project.h"
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

    // Also load the project archive
    std::string projectPath = LE3EditorCache::getMostRecentProject();
    LE3GetDatFileSystem().addArchive(LE3ED_PROJECT_ARCHIVE, projectPath + "/" + LE3ED_PROJECT_FILENAME);
    if (!LE3GetDatFileSystem().fileExists(LE3ED_PROJECT_CONFIG)) {
        LE3DatBuffer buffer;
        // LE3GetDatFileSystem().appendFile(LE3ED_PROJECT_ARCHIVE, LE3ED_PROJECT_CONFIG, buffer, true);
        LE3GetScriptSystem().createEmptyTable("LE3ProjectConfig");
        LE3Serialization::dump("LE3ProjectConfig", LE3ED_PROJECT_CONFIG);
    }
    LE3GetScriptSystem().doFile(LE3ED_PROJECT_CONFIG);

    // Bind custom editor Lua "libraries"
    LE3EditorComPropertyChange::registerLua();
}
void LE3EditorScripts::update(float deltaTime) {
}