#include "commands/le3ed_com_duplicate.h"
using namespace le3;

LE3EditorComDuplicate::LE3EditorComDuplicate(std::vector<std::string> names) : m_names(names) {
}

void LE3EditorComDuplicate::execute() {
    for (std::string name : m_names) {
        LE3ObjectPtr pObject = LE3GetActiveScene()->getObject(name);
        LE3GetScriptSystem().getGlobal("duplicate_object");
        LE3GetScriptSystem().pushUserType<LE3Scene>(LE3GetActiveScene().get());
        LE3GetScriptSystem().pushString(pObject->getObjectType());
        LE3GetScriptSystem().pushString(pObject->getName());
        LE3GetScriptSystem().callFunction(3, 1);
        std::string newName = LE3GetScriptSystem().getString(-1);
        LE3GetEditorManager().getSelection().selectObject(
            LE3GetActiveScene()->getObject(newName));
        m_newNames.push_back(newName);
    }
}
void LE3EditorComDuplicate::undo() {
    LE3GetEditorManager().getSelection().reset();
    for (std::string name : m_newNames) {
        LE3GetActiveScene()->deleteObject(name);
    }
}