#pragma once

#include <memory>

#include <glm/glm.hpp>
#include <bullet/btBulletDynamicsCommon.h>

namespace le3 {
    class LE3PhysicsComponent {
    public:
        void enable();
        bool isEnabled() const { return m_bEnabled; }

        void setIsRigidBody(bool isRigidBody) { m_bIsRigidBody = isRigidBody; }
        bool isRigidBody() const { return m_bIsRigidBody; }

        void setIsTrigger(bool isTrigger) { m_bIsTrigger = isTrigger; }
        bool isTrigger() const { return m_bIsTrigger; }

        void addBoxCollider(glm::vec3 size);

        std::weak_ptr<btCollisionShape> getCollider() { return m_collider; }


    private:
        std::shared_ptr<btCollisionShape> m_collider;
        bool m_bEnabled, m_bIsRigidBody, m_bIsTrigger;
    };
}

