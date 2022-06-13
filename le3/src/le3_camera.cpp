#include "le3_camera.h"

LE3Camera::LE3Camera() : 
    LE3Object("Camera"),
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

glm::mat4 LE3Camera::GetProjectionMatrix(float aspectRatio) const
{
    return glm::perspective(glm::radians(45.f), aspectRatio, 0.1f, 100.f);
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

LE3FPSCamera::LE3FPSCamera(float walkSpeed, float lookSensitivity) : 
    LE3Camera(),
    m_walkSpeed(walkSpeed),
    m_lookSensitivity(lookSensitivity),
    m_moveVelocity(glm::vec2(0.f)),
    m_lookVelocity(glm::vec2(0.f))
{
}

void LE3FPSCamera::Update(double deltaTime)
{
    glm::vec3 floorForward = m_forward;
    floorForward.y = 0.f;
    floorForward = glm::normalize(floorForward);
    m_position += (float)deltaTime * m_walkSpeed * m_moveVelocity.y * floorForward;
    m_position += (float)deltaTime * m_walkSpeed * m_moveVelocity.x * m_right;
    AddRotationY(m_lookSensitivity * m_lookVelocity.x);
    AddRotationX(m_lookSensitivity * m_lookVelocity.y);

    LE3Camera::Update(deltaTime);
}

void LE3FPSCamera::SetMoveVelocityX(float x)
{
    m_moveVelocity.x = x;
}
void LE3FPSCamera::SetMoveVelocityY(float y)
{
    m_moveVelocity.y = y;
}
void LE3FPSCamera::SetLookVelocityX(float x)
{
    m_lookVelocity.x = x;
}
void LE3FPSCamera::SetLookVelocityY(float y)
{
    m_lookVelocity.y = y;
}

LE3FreeCamera::LE3FreeCamera(float walkSpeed, float lookSensitivity) : 
    LE3Camera(),
    m_walkSpeed(walkSpeed),
    m_lookSensitivity(lookSensitivity),
    m_moveVelocity(glm::vec3(0.f)),
    m_lookVelocity(glm::vec2(0.f))
{
}

void LE3FreeCamera::Update(double deltaTime)
{
    m_position += (float)deltaTime * m_walkSpeed * m_moveVelocity.y * m_forward;
    m_position += (float)deltaTime * m_walkSpeed * m_moveVelocity.x * m_right;
    m_position += (float)deltaTime * m_walkSpeed * m_moveVelocity.z * m_up;
    AddRotationY(m_lookSensitivity * m_lookVelocity.x);
    AddRotationX(m_lookSensitivity * m_lookVelocity.y);

    LE3Camera::Update(deltaTime);
}

void LE3FreeCamera::SetMoveVelocityX(float x)
{
    m_moveVelocity.x = x;
}
void LE3FreeCamera::SetMoveVelocityY(float y)
{
    m_moveVelocity.y = y;
}
void LE3FreeCamera::SetMoveVelocityZ(float z)
{
    m_moveVelocity.z = z;
}
void LE3FreeCamera::SetLookVelocityX(float x)
{
    m_lookVelocity.x = x;
}
void LE3FreeCamera::SetLookVelocityY(float y)
{
    m_lookVelocity.y = y;
}