#pragma once

#include <memory>

#include <glm/glm.hpp>

#include "core/le3_transform.h"

namespace le3 {

    ///////////////////////////
    // Forward declarations
    ///////////////////////////
    struct LE3PhysicsCollider;
    struct LE3PhysicsRigidBody;
    ///////////////////////////

    class LE3PhysicsComponent {
    public:
        LE3PhysicsComponent(LE3Transform& transform);
        
        void enable();
        bool isEnabled() const { return m_bEnabled; }

        bool update();

        void setIsTrigger(bool isTrigger) { m_bIsTrigger = isTrigger; }
        bool isTrigger() const { return m_bIsTrigger; }

        void addBoxCollider(glm::vec3 size);
        void addSphereCollider(float radius);

        std::weak_ptr<LE3PhysicsCollider> getCollider() { return m_collider; }
        void setupRigidBody(float mass);

        void* getRigidBody();

        void warp(glm::vec3 position, glm::quat rotation);


    private:
        LE3Transform& m_transform;
        std::shared_ptr<LE3PhysicsCollider> m_collider;
        std::shared_ptr<LE3PhysicsRigidBody> m_rigidBody;
        bool m_bEnabled, m_bIsTrigger;
    };
}

