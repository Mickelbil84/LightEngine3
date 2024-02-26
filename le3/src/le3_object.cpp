#include "le3_object.h"
using namespace le3;

void LE3Object::update(float deltaTime) {
    glm::mat4 parentWorld = glm::mat4(1.f);
    if (m_pParent) parentWorld = m_pParent->getWorldMatrix();
    m_worldMatrix = parentWorld * m_transform.getTransformMatrix();
}

void LE3Object::reparent(std::shared_ptr<LE3Object> newParent) {
    if (m_pParent) {
        m_pParent->m_pChildren.erase(
            std::remove(m_pParent->m_pChildren.begin(), m_pParent->m_pChildren.end(), shared_from_this()), 
            m_pParent->m_pChildren.end());
    }
    m_pParent = newParent;
    m_pParent->m_pChildren.push_back(shared_from_this());
}
void LE3Object::appendChild(std::shared_ptr<LE3Object> pChild) {
    pChild->reparent(shared_from_this());
}