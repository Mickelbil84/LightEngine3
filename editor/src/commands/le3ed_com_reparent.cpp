#include "commands/le3ed_com_reparent.h"
using namespace le3;

LE3EditorComReparent::LE3EditorComReparent(std::vector<std::string> names) :
    m_names(names) {
    for (auto name : names) {
        m_oldParents[name] = LE3GetActiveScene()->getObject(name)->getParent()->getName();
    }
}

void LE3EditorComReparent::execute() {
    std::string parentName = m_names[m_names.size() - 1];
    for (int idx = 0; idx < m_names.size() - 1; idx++) {
        LE3GetActiveScene()->getObject(m_names[idx])->reparent(
            LE3GetActiveScene()->getObject(parentName)
        );
    }
}
void LE3EditorComReparent::undo() {
    for (auto [objName, oldParentName] : m_oldParents) {
        LE3GetActiveScene()->getObject(objName)->reparent(
            LE3GetActiveScene()->getObject(oldParentName)
        );
    }
}