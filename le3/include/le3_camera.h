#pragma once

#include "le3_object.h"

#include <gl/glew.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

// Abstract class describing a virtual camera
class LE3Camera : public LE3Object
{
public:
    LE3Camera();

    // Update method, called once every frame
    virtual void Update(double deltaTime);

    // Returns the view matrix for the given camera
    glm::mat4 GetViewMatrix() const;
    // Returns the projection matrix for the given camera
    glm::mat4 GetProjectionMatrix(float aspectRatio=-1.f) const;
    // Returns camera's forward vector
    glm::vec3 GetForward() const;
    // Returns camera's right vector
    glm::vec3 GetRight() const;
    // Returns camera's up vector
    glm::vec3 GetUp() const;

    float GetAspectRatio() const;
    void SetAspectRatio(float aspectRatio);

protected:
    glm::vec3 m_forward, m_up, m_right;
    float m_aspectRatio;
};

class LE3FPSCamera : public LE3Camera
{
public:
    LE3FPSCamera(float walkSpeed = 2.2f, float lookSensitivity = 0.005f);

    // Update method, called once every frame
    virtual void Update(double deltaTime);

    void SetMoveVelocityX(float x);
    void SetMoveVelocityY(float y);
    void SetLookVelocityX(float x);
    void SetLookVelocityY(float y);


protected:
    float m_walkSpeed, m_lookSensitivity;
    glm::vec2 m_moveVelocity, m_lookVelocity;
};

class LE3FreeCamera : public LE3Camera
{
public:
    LE3FreeCamera(float walkSpeed = 2.2f, float lookSensitivity = 0.005f);

    // Update method, called once every frame
    virtual void Update(double deltaTime);

    void SetMoveVelocityX(float x);
    void SetMoveVelocityY(float y);
    void SetMoveVelocityZ(float z);
    void SetLookVelocityX(float x);
    void SetLookVelocityY(float y);


protected:
    float m_walkSpeed, m_lookSensitivity;
    glm::vec3 m_moveVelocity;
    glm::vec2 m_lookVelocity;
};

CEREAL_REGISTER_TYPE(LE3Camera);
CEREAL_REGISTER_TYPE(LE3FreeCamera);
CEREAL_REGISTER_POLYMORPHIC_RELATION(LE3Object, LE3Camera);
CEREAL_REGISTER_POLYMORPHIC_RELATION(LE3Camera, LE3FreeCamera);