#include "le3_camera.h"
using namespace le3;

LE3Camera::LE3Camera() : m_fov(glm::radians(45.f)), m_aspectRatio(1.f) {
    // By default, make the camera facing forward
    m_transform.addRotationY(glm::radians(-90.f));
}

void LE3Camera::update(float deltaTime) {
    LE3Object::update(deltaTime);
}

glm::mat4 LE3Camera::getViewMatrix() {
    return glm::lookAt(
        m_transform.getPosition(), 
        m_transform.getPosition() + m_transform.getForward(),
        m_transform.getUp()
    );
}
glm::mat4 LE3Camera::getProjectionMatrix(float aspectRatio) {
    if (aspectRatio < 0) aspectRatio = m_aspectRatio;
    return glm::perspective(m_fov, aspectRatio, .1f, 100.f);
}