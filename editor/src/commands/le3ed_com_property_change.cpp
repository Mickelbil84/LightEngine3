#include "commands/le3ed_com_property_change.h"
using namespace le3;

#include <fmt/core.h>

void LE3EditorComPropertyChange::execute() {

}
void LE3EditorComPropertyChange::undo() {

}

void LE3EditorComPropertyChange::registerLua() {
    lua_State* L = LE3GetScriptSystem().getLuaState();
    REGISTER(LE3EditorComPropertyChange);
}

// ----------------------------------------

FBIND(LE3EditorComPropertyChange, foo)
    fmt::print("Hello World!\n");
FEND()
LIB(LE3EditorComPropertyChange, 
    foo)