#include "commands/le3ed_com_reparent.h"
using namespace le3;

LE3EditorComReparent::LE3EditorComReparent(std::string objName, std::string newParentName) :
    m_objName(objName), m_newParentName(newParentName) {
    m_oldParentName = LE3GetActiveScene()->getObject(m_objName)->getName();
}

void LE3EditorComReparent::execute() {
    LE3GetActiveScene()->getObject(m_objName)->reparent(
        LE3GetActiveScene()->getObject(m_newParentName)
    );
}
void LE3EditorComReparent::undo() {
    LE3GetActiveScene()->getObject(m_objName)->reparent(
        LE3GetActiveScene()->getObject(m_oldParentName)
    );
}