#include "commands/le3ed_com_reparent.h"
using namespace le3;

LE3EditorComReparent::LE3EditorComReparent(std::vector<std::string> names) :
    m_names(names) {
    for (auto name : names) {
        m_oldParents[name] = LE3GetActiveScene()->getObject(name)->getParent()->getName();
        m_oldTransforms[name] = LE3GetActiveScene()->getObject(name)->getTransform().getTransformMatrix();
    }
}

void LE3EditorComReparent::execute() {
    std::string parentName = m_names[m_names.size() - 1];
    LE3ObjectPtr parent = LE3GetActiveScene()->getObject(parentName);
    glm::mat4 invParentTransform = glm::inverse(parent->getTransform().getTransformMatrix());
    for (int idx = 0; idx < m_names.size() - 1; idx++) {
        LE3GetActiveScene()->getObject(m_names[idx])->reparent(parent);
        LE3GetActiveScene()->getObject(m_names[idx])->getTransform().fromTransformMatrix(
            invParentTransform * m_oldTransforms[m_names[idx]]
        );
    }
    LE3GetEditorManager().getSelection().selectObject(parent);
}
void LE3EditorComReparent::undo() {
    for (auto [objName, oldParentName] : m_oldParents) {
        LE3GetActiveScene()->getObject(objName)->reparent(
            LE3GetActiveScene()->getObject(oldParentName)
        );
        LE3GetActiveScene()->getObject(objName)->getTransform().fromTransformMatrix(
            m_oldTransforms[objName]
        );
    }
}