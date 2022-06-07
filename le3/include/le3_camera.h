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

    // Update method, caleld once every frame
    virtual void Update(double deltaTime);

    // Returns the view matrix for the given camera
    glm::mat4 GetViewMatrix() const;
    // Returns camera's forward vector
    glm::vec3 GetForward() const;
    // Returns camera's right vector
    glm::vec3 GetRight() const;
    // Returns camera's up vector
    glm::vec3 GetUp() const;

protected:
    glm::vec3 m_forward, m_up, m_right;
    
};