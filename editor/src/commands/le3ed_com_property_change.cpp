#include "commands/le3ed_com_property_change.h"
using namespace le3;

#include <fmt/core.h>

void LE3EditorComPropertyChange::execute() {
    LE3GetScriptSystem().getGlobal("property_change_execute_ticket");
    LE3GetScriptSystem().pushNumber(m_ticket);
    LE3GetScriptSystem().callFunction(1, 0);
}
void LE3EditorComPropertyChange::undo() {
    LE3GetScriptSystem().getGlobal("property_change_undo_ticket");
    LE3GetScriptSystem().pushNumber(m_ticket);
    LE3GetScriptSystem().callFunction(1, 0);
}

void LE3EditorComPropertyChange::registerLua() {
    lua_State* L = LE3GetScriptSystem().getLuaState();
    REGISTER(LE3EditorComPropertyChange);
}

// ----------------------------------------

FBIND(LE3EditorComPropertyChange, foo)
    fmt::print("Hello World!\n");
FEND()

FBIND(LE3EditorComPropertyChange, addNew)
    GET_NUMBER(ticket)
    LE3GetEditorManager().getCommandStack().execute(
        std::make_unique<LE3EditorComPropertyChange>(ticket)
    );
FEND()

LIB(LE3EditorComPropertyChange, 
    foo, addNew)