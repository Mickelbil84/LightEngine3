#pragma once

#include <memory>

#include <glm/glm.hpp>

#include "le3_collider_info.h"
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
        LE3PhysicsComponent(LE3Transform& transform, bool isRigidBody = false);
        
        void disable();
        void enable();
        bool isEnabled() const { return m_bEnabled; }

        bool update();

        void setIsTrigger(bool isTrigger) { m_bIsTrigger = isTrigger; }
        bool isTrigger() const { return m_bIsTrigger; }
        inline bool isRigidBody() const { return m_bRigidBody; }
        inline void setIsRigidBody(bool isRigidBody) { if (!isRigidBody) disable(); m_bRigidBody = isRigidBody; }
        
        void setMass(float mass);
        float getMass();
        
        std::weak_ptr<LE3PhysicsCollider> getCollider() { return m_collider; }
        void setupRigidBody(LE3ColliderInfo colliderInfo);
        LE3ColliderInfo getColliderInfo() const { return m_colliderInfo; }
        
        void* getRigidBody();
        
        void warp(glm::vec3 position, glm::quat rotation);

        
        
    private:
        void addBoxCollider(glm::vec3 size);
        void addSphereCollider(float radius, glm::vec3 scaling);
        void addConvexHullCollider(std::vector<glm::vec3> vertices, glm::vec3 centroid, glm::vec3 scaling);

        LE3Transform& m_transform;
        std::shared_ptr<LE3PhysicsCollider> m_collider;
        std::shared_ptr<LE3PhysicsRigidBody> m_rigidBody;
        LE3ColliderInfo m_colliderInfo;
        bool m_bEnabled, m_bIsTrigger; // Enabled == do not override! this means whether the physics is active (it may become true at some point)
        bool m_bRigidBody; // The most important variable: if false - then this entire component is disabled (stronger then m_bEnabled)

        std::string m_componentName; // This would be some random unique id, but not the object name so we don't have to track changes
    };
}

