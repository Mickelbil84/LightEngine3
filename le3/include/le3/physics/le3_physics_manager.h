#pragma once

#include <map>
#include <memory>
#include <vector>
#include <string>

#include <glm/gtc/quaternion.hpp>

#include "physics/le3_physics.h"

namespace le3 {
    class LE3PhysicsManager {
    public:
        LE3PhysicsManager();
        void reset();
        void update(float deltaTime);

        inline void setPhysicsEnabled(bool enabled) { m_bPhysicsEnabled = enabled; }
        inline bool isPhysicsEnabled() const { return m_bPhysicsEnabled; }

        void registerComponent(std::string name, LE3PhysicsComponent& component);
        void clearComponent(std::string name);

        bool rayTest(glm::vec3 from, glm::vec3 to);

        // Exact triangle-mesh contacts (FCL), separate from the Bullet world and cleared by reset().
        // Two meshes collide iff their surfaces touch or overlap: no hulls, no margins.
        void addCollisionMesh(std::string name, const std::vector<glm::vec3>& triangles); // Appends; 3 vertices per triangle
        void setCollisionMeshPose(std::string name, glm::dvec3 position, glm::dquat rotation);
        void ignoreCollisionMeshPair(std::string nameA, std::string nameB);
        std::vector<std::string> getCollidingMeshPairs(); // Flat: a1, b1, a2, b2, ...; recomputed only after a change

    private:
        void checkCollisions();
        struct _LE3PhysicsManager_Internal;
        std::shared_ptr<_LE3PhysicsManager_Internal> m_pInternal;
        bool m_bPhysicsEnabled = true;
    };
}

