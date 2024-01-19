#include "le3_transform.h"
using namespace le3;

LE3Transform::LE3Transform() : m_transform(glm::mat4(1.f)) {}

void LE3Transform::updateCache() {
    m_position = m_transform[3];
    
    m_scale = glm::vec3(
        glm::length(glm::vec3(m_transform[0])), 
        glm::length(glm::vec3(m_transform[1])), 
        glm::length(glm::vec3(m_transform[2]))
    );

    const glm::mat3 rotationMatrix(
        glm::vec3(m_transform[0]) / m_scale[0],
        glm::vec3(m_transform[1]) / m_scale[1],
        glm::vec3(m_transform[2]) / m_scale[2]
    );
    m_rotation = glm::quat_cast(rotationMatrix);
}

glm::vec3 LE3Transform::getPosition() const  {
    return m_position;
}
glm::quat LE3Transform::getRotation() const  {
    return m_rotation;
    
}
glm::vec3 LE3Transform::getScale() const  {
    return m_scale;
}

glm::vec3 LE3Transform::getForward() const  {
    return m_rotation * glm::vec3(-1.f, 0.f, 0.f);
}
glm::vec3 LE3Transform::getRight() const  {
    return m_rotation * glm::vec3(0.f, 0.f, 1.f);
}
glm::vec3 LE3Transform::getUp() const  {
    return m_rotation * glm::vec3(0.f, 1.f, 0.f);
}

void LE3Transform::setPosition(glm::vec3 position) {
    m_transform[3] = glm::vec4(position, 1.f);
    updateCache();
}
void LE3Transform::addPositionX(float amount) {
    m_transform[3][0] += amount;
    updateCache();
}
void LE3Transform::addPositionY(float amount) {
    m_transform[3][1] += amount;
    updateCache();
}
void LE3Transform::addPositionZ(float amount) {
    m_transform[3][2] += amount;
    updateCache();
}

void LE3Transform::addRotationX(float amount) {
    m_transform = glm::rotate(m_transform, amount, glm::vec3(1.f, 0.f, 0.f));
    updateCache();
}
void LE3Transform::addRotationY(float amount) {
    m_transform = glm::rotate(m_transform, amount, glm::vec3(0.f, 1.f, 0.f));
    updateCache();
}
void LE3Transform::addRotationZ(float amount) {
    m_transform = glm::rotate(m_transform, amount, glm::vec3(0.f, 0.f, 1.f));
    updateCache();
}