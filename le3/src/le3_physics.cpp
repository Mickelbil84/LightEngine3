#include "le3_physics.h"
#include "le3_physics_manager.h"
#include "le3_engine_systems.h"
using namespace le3;

void LE3PhysicsComponent::enable() {
    if (!m_collider) return;
    m_bEnabled = true;
    LE3GetPhysicsManager().registerComponent(*this);
}

void LE3PhysicsComponent::addBoxCollider(glm::vec3 size) {
    m_collider = std::make_shared<btBoxShape>(btVector3(size.x, size.y, size.z));
}