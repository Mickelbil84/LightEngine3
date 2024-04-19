#pragma once

#include "le3_object.h"

namespace le3 {
    class LE3Camera : public LE3Object {
    public:
        LE3Camera();

        virtual void update(float deltaTime);

        glm::mat4 getViewMatrix();
        glm::mat4 getProjectionMatrix(float aspectRatio=-1.f);

        glm::vec3 getPosition() const { return glm::vec3(getWorldMatrix()[3]); }
        glm::vec3 getForward() const { return m_forwawrd; }
        glm::vec3 getRight() const { return m_right; }
        glm::vec3 getUp() const { return m_up; }

        void moveForward(float amount) { m_transform.addPosition(amount * m_forwawrd); }
        void moveRight(float amount) { m_transform.addPosition(amount * m_right); }
        void moveUp(float amount) { m_transform.addPosition(amount * m_up); }

        float getAspectRatio() const { return m_aspectRatio; }
        void setAspectRatio(float aspectRatio) { m_aspectRatio = aspectRatio; }
        
        float getFov() const { return m_fov; }
        void setFov(float fov) { m_fov = fov; }

        void addPitchYaw(float pitch, float yaw) { m_pitch += pitch; m_yaw += yaw; }
        void setPitchYaw(float pitch, float yaw) { m_pitch = pitch; m_yaw = yaw; }
        float getPitch() const { return m_pitch; }
        float getYaw() const { return m_yaw; }

    protected:
        float m_aspectRatio, m_fov;
        float m_pitch, m_yaw;
        glm::vec3 m_forwawrd, m_right, m_up;

        virtual void updateCameraDirections() = 0;
    };
    using LE3CameraPtr = std::shared_ptr<LE3Camera>;

    class LE3OrbitCamera : public LE3Camera {
    public:     
        LE3OrbitCamera();

        virtual void update(float deltaTime);

        float getOffset() const { return m_offset; }
        void setOffset(float offset) { m_offset = offset; }
        glm::vec3 getOrigin() const { return m_origin; }
        void setOrigin(glm::vec3 origin) { m_origin = origin; }

    protected:
        glm::vec3 m_origin;
        float m_offset;
        virtual void updateCameraDirections();
    };
    using LE3OrbitCameraPtr = std::shared_ptr<LE3OrbitCamera>;

    class LE3FreeCamera : public LE3Camera {
    public:     
        LE3FreeCamera();

        virtual void update(float deltaTime);
    protected:
        virtual void updateCameraDirections();
    };
    using LE3FreeCameraPtr = std::shared_ptr<LE3FreeCamera>;
}