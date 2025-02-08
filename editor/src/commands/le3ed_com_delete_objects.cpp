#include "commands/le3ed_com_delete_objects.h"
using namespace le3;

LE3EditorComDeleteObjects::LE3EditorComDeleteObjects(std::vector<std::string> names) : m_names(names) {
}

void LE3EditorComDeleteObjects::execute() {
    m_tickets.clear();
    LE3GetEditorManager().getSelection().reset();
    for (std::string name : m_names) {
        LE3GetScriptSystem().getGlobal("delete_object");
        LE3GetScriptSystem().pushUserType<LE3Scene>(LE3GetActiveScene().get());
        LE3GetScriptSystem().pushString(name);
        LE3GetScriptSystem().callFunction(2, 1);
        m_tickets.push_back(LE3GetScriptSystem().getNumber(-1));
    }
}
void LE3EditorComDeleteObjects::undo() {
    for (double ticket : m_tickets) {
        LE3GetScriptSystem().getGlobal("restore_object");
        LE3GetScriptSystem().pushUserType<LE3Scene>(LE3GetActiveScene().get());
        LE3GetScriptSystem().pushNumber(ticket);
        LE3GetScriptSystem().callFunction(2, 0);
    }
}