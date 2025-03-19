#pragma once

#include <memory>
#include <vector>
#include <string>

#include <bullet/btBulletDynamicsCommon.h>

#include "le3_physics.h"

namespace le3 {
    class LE3PhysicsManager {
    public:
        void reset();
        void update(float deltaTime);

        inline void setPhysicsEnabled(bool enabled) { m_bPhysicsEnabled = enabled; }
        inline bool isPhysicsEnabled() const { return m_bPhysicsEnabled; }

        void registerComponent(LE3PhysicsComponent& component);

    private:
        std::unique_ptr<btDefaultCollisionConfiguration> m_collisionConfiguration;
        std::unique_ptr<btCollisionDispatcher> m_dispatcher;
        std::unique_ptr<btBroadphaseInterface> m_overlappingPairCache;
        std::unique_ptr<btSequentialImpulseConstraintSolver> m_solver;
        std::unique_ptr<btDiscreteDynamicsWorld> m_dynamicsWorld;

        bool m_bPhysicsEnabled = true;
    };
}

