#pragma once

#ifndef GLM_ENABLE_EXPERIMENTAL
#define GLM_ENABLE_EXPERIMENTAL
#endif

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

namespace le3 {
    struct LE3Transform {
    public:
        LE3Transform();

        glm::mat4 getTransformMatrix() const;
        void fromTransformMatrix(glm::mat4 transformMatrix);

        glm::vec3 getPosition() const;
        glm::quat getRotation() const;
        glm::vec3 getScale() const;

        void setPosition(glm::vec3 position);
        void addPosition(glm::vec3 position);
        void addPositionX(float amount);
        void addPositionY(float amount);
        void addPositionZ(float amount);

        void setRotation(glm::quat rotation);
        void setRotationRPY(float roll, float pitch, float yaw);
        void addRotationX(float amount);
        void addRotationY(float amount);
        void addRotationZ(float amount);
        void addRotation(float amount, glm::vec3 axis);

        void setScale(glm::vec3 scale);
        void setScale(float scale);
        
        void setOrbit(float roll, float pitch, float yaw, glm::vec3 origin, float offset);

        void lookAt(glm::vec3 target);

        void disableZ();

    private:
        glm::vec3 m_position;
        glm::quat m_rotation;
        glm::vec3 m_scale;

        glm::quat rotationBetweenVectors(glm::vec3 start, glm::vec3 dest);
    };
};