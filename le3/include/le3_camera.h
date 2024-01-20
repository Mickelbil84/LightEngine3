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

    class LE3OrbitCamera : public LE3Camera {
    public:     
        LE3OrbitCamera();

        virtual void update(float deltaTime);

        glm::vec3 getOffset() const { return m_offset; }
        void setOffset(glm::vec3 offset) { m_offset = offset; }
        glm::vec3 getOrigin() const { return m_origin; }
        void setOrigin(glm::vec3 origin) { m_origin = origin; }

    protected:
        glm::vec3 m_offset, m_origin;
    };

    class LE3FreeCamera : public LE3Camera {
    public:     
        LE3FreeCamera();

        virtual void update(float deltaTime);
    protected:
    };
}