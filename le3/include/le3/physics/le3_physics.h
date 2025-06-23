#pragma once

#include <memory>

#include <glm/glm.hpp>

#include "le3_collider_info.h"
#include "core/le3_transform.h"
#include "graphics/le3_geometry.h"

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

        void setLinearVelocity(glm::vec3 velocity);
        void setAngularVelocity(glm::vec3 velocity);
        void setAngularFactor(glm::vec3 factor);
        
        std::weak_ptr<LE3PhysicsCollider> getCollider() { return m_collider; }
        void setupRigidBody(LE3ColliderInfo colliderInfo);
        LE3ColliderInfo getColliderInfo() const { return m_colliderInfo; }
        
        void* getRigidBody();
        
        void warp(glm::vec3 position, glm::quat rotation);
        void setRotation(glm::quat rotation); // Set rotation will always apply the given rotation on top of the initial rotation

        std::weak_ptr<LE3DebugMesh> getHullDebugMesh() { return m_hullMesh; }

        void setManualColliderOverride(bool colliderOverride) { m_bColliderOverride = colliderOverride; }
        bool isManualColliderOverride() const { return m_bColliderOverride; }
        
        void setManualColliderType(LE3ColliderType colliderType) { m_colliderOverride.colliderType = colliderType;}
        LE3ColliderType getManualColliderType() const { return m_colliderOverride.colliderType; }
        LE3ColliderInfo getOverrideColliderInfo() const { return m_colliderOverride; }
        
        void setManualCentroid(glm::vec3 centroid) { m_colliderOverride.centroid = centroid; }
        glm::vec3 getManualCentroid() const { return m_colliderOverride.centroid; }
        void setManualExtent(glm::vec3 extent) { m_colliderOverride.extent = extent; }
        glm::vec3 getManualExtent() const { return m_colliderOverride.extent; }
        void setManualRadius(float radius) { m_colliderOverride.radius = radius; }
        float getManualRadius() const { return m_colliderOverride.radius; }

        
        
    private:
        void addBoxCollider(glm::vec3 size);
        void addSphereCollider(float radius, glm::vec3 scaling);
        void addConeCollider(glm::vec3 size);
        void addCylinderCollider(glm::vec3 size);
        void addCapsuleCollider(glm::vec3 size);
        void addConvexHullCollider(std::vector<glm::vec3> vertices, glm::vec3 centroid, glm::vec3 scaling);

        LE3Transform& m_transform;
        std::shared_ptr<LE3PhysicsCollider> m_collider;
        std::shared_ptr<LE3PhysicsRigidBody> m_rigidBody;
        LE3ColliderInfo m_colliderInfo, m_colliderOverride;
        bool m_bEnabled, m_bIsTrigger; // Enabled == do not override! this means whether the physics is active (it may become true at some point)
        bool m_bRigidBody; // The most important variable: if false - then this entire component is disabled (stronger then m_bEnabled)
        bool m_bColliderOverride = false;
        
        std::shared_ptr<LE3DebugMesh> m_hullMesh = nullptr; // For convex hull - store the hull mesh

        // For local offsets/warping/setting rotation trickery
        glm::quat m_initialRotation = glm::quat(1.f, 0.f, 0.f, 0.f);

        std::string m_componentName; // This would be some random unique id, but not the object name so we don't have to track changes
    };
}

