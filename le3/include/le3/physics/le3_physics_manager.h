#pragma once

#include <memory>
#include <vector>
#include <string>

#include "physics/le3_physics.h"

namespace le3 {
    class LE3PhysicsManager {
    public:
        LE3PhysicsManager();
        void reset();
        void update(float deltaTime);

        inline void setPhysicsEnabled(bool enabled) { m_bPhysicsEnabled = enabled; }
        inline bool isPhysicsEnabled() const { return m_bPhysicsEnabled; }

        void registerComponent(LE3PhysicsComponent& component);

    private:
        struct _LE3PhysicsManager_Internal;
        std::shared_ptr<_LE3PhysicsManager_Internal> m_pInternal;

        bool m_bPhysicsEnabled = true;
    };
}

