#include "le3_camera.h"
using namespace le3;

LE3Camera::LE3Camera() : 
    m_fov(glm::radians(45.f)), m_aspectRatio(1.f),
    m_pitch(0.f), m_yaw(0.f) {
    // By default, make the camera facing forward
    // m_transform.addRotationY(glm::radians(-90.f));
}

void LE3Camera::update(float deltaTime) {
    updateCameraDirections();
    LE3Object::update(deltaTime);
}

glm::mat4 LE3Camera::getViewMatrix() {
    return glm::inverse(getWorldMatrix());
}
glm::mat4 LE3Camera::getProjectionMatrix(float aspectRatio) {
    if (aspectRatio < 0) aspectRatio = m_aspectRatio;
    return glm::perspective(m_fov, aspectRatio, .1f, 100.f);
}

LE3OrbitCamera::LE3OrbitCamera() : LE3Camera(), m_origin(glm::vec3(0.f)), m_offset(0.f) {
}

void LE3OrbitCamera::update(float deltaTime) {
    m_transform.setOrbit(0.f, m_pitch, m_yaw, m_origin, m_offset);
    LE3Camera::update(deltaTime);
}

void LE3OrbitCamera::updateCameraDirections() {
    m_forwawrd = m_origin - m_offset; //- glm::vec3(getWorldMatrix()[3]);
    m_right = glm::cross(m_forwawrd, glm::vec3(0.f, 1.f, 0.f));
    m_up = glm::cross(m_right, m_forwawrd);
}

LE3FreeCamera::LE3FreeCamera() : LE3Camera() {
}

void LE3FreeCamera::update(float deltaTime) {
    m_transform.setRotationRPY(0.f, m_pitch, m_yaw);
    LE3Camera::update(deltaTime);
}

void LE3FreeCamera::updateCameraDirections() {
    glm::quat rotation = m_transform.getRotation();
    m_forwawrd = rotation * glm::vec3(0.f, 0.f, -1.f);
    m_right = rotation * glm::vec3(1.f, 0.f, 0.f);
    m_up = rotation * glm::vec3(0.f, 1.f, 0.f);
}