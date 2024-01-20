#pragma once

#include "le3_object.h"

namespace le3 {
    class LE3Camera : public LE3Object {
    public:
        LE3Camera();

        virtual void update(float deltaTime);

        glm::mat4 getViewMatrix();
        glm::mat4 getProjectionMatrix(float aspectRatio=-1.f);

        float getAspectRatio() const { return m_aspectRatio; }
        void setAspectRatio(float aspectRatio) { m_aspectRatio = aspectRatio; }
        void setFov(float fov) { m_fov = fov; }

        void addPitchYaw(float pitch, float yaw) { m_pitch += pitch; m_yaw += yaw; }

    protected:
        float m_aspectRatio, m_fov;
        float m_pitch, m_yaw;
    };
}