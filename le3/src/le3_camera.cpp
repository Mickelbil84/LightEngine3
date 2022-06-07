#include "le3_camera.h"

LE3Camera::LE3Camera() : 
    m_forward(glm::vec3(0.f, 0.f, -1.f)),
    m_up(glm::vec3(0.f, 1.f, 0.f)),
    m_right(glm::vec3(1.f, 0.f, 0.f))
{
    // Look forward by default
    m_rotation.y = glm::radians(-90.f);
}

void LE3Camera::Update(double deltaTime)
{
    LE3Object::Update(deltaTime);

    // Clamp pitch value
    if (m_rotation.x > glm::radians(89.f))
        m_rotation.x = glm::radians(89.f);
    if (m_rotation.x < glm::radians(-89.f))
        m_rotation.x = glm::radians(-89.f);

    // Update forward vector
    m_forward.x = cos(m_rotation.y) * cos(m_rotation.x);
    m_forward.y = sin(m_rotation.x);
    m_forward.z = sin(m_rotation.y) * cos(m_rotation.x);
    m_forward = glm::normalize(m_forward);

    // Update right vector, which forward x world up
    m_right = glm::cross(m_forward, glm::vec3(0.f, 1.f, 0.f));
    m_right = glm::normalize(m_right);

    // Finally update the camera up vector
    m_up = glm::cross(m_right, m_forward);
}

glm::mat4 LE3Camera::GetViewMatrix() const
{
    return glm::lookAt(m_position, m_position + m_forward, m_up);
}

glm::vec3 LE3Camera::GetForward() const
{
    return m_forward;
}

glm::vec3 LE3Camera::GetRight() const
{
    return m_right;
}

glm::vec3 LE3Camera::GetUp() const
{
    return m_up;
}