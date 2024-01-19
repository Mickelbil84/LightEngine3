#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

namespace le3 {
    struct LE3Transform {
    public:
        LE3Transform();

        inline glm::mat4 getTransformMatrix() const { return m_transform; }

        glm::vec3 getPosition() const;
        glm::quat getRotation() const;
        glm::vec3 getScale() const;

        glm::vec3 getForward() const;
        glm::vec3 getRight() const;
        glm::vec3 getUp() const;

        void setPosition(glm::vec3 position);
        void addPositionX(float amount);
        void addPositionY(float amount);
        void addPositionZ(float amount);

        void addRotationX(float amount);
        void addRotationY(float amount);
        void addRotationZ(float amount);

    private:
        glm::mat4 m_transform;

        // Cache
        glm::vec3 m_position, m_scale;
        glm::quat m_rotation;
        void updateCache();

    };
};