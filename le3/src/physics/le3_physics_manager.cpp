#include "physics/le3_physics_manager.h"
using namespace le3;

#include <bullet/btBulletDynamicsCommon.h>

struct LE3PhysicsManager::_LE3PhysicsManager_Internal {
    _LE3PhysicsManager_Internal() {}
    std::unique_ptr<btDefaultCollisionConfiguration> m_collisionConfiguration;
    std::unique_ptr<btCollisionDispatcher> m_dispatcher;
    std::unique_ptr<btBroadphaseInterface> m_overlappingPairCache;
    std::unique_ptr<btSequentialImpulseConstraintSolver> m_solver;
    std::unique_ptr<btDiscreteDynamicsWorld> m_dynamicsWorld;

    std::map<std::string, btRigidBody*> m_rigidBodies;  // Each object/component should only have one rigid body
};

LE3PhysicsManager::LE3PhysicsManager() : m_pInternal(std::make_shared<_LE3PhysicsManager_Internal>()) {
    reset();
}

void LE3PhysicsManager::reset() {
    // Delete previous references in a safe order
    m_pInternal->m_dynamicsWorld = nullptr;
    m_pInternal->m_dispatcher = nullptr;
    m_pInternal->m_collisionConfiguration = nullptr;
    m_pInternal->m_overlappingPairCache = nullptr;
    m_pInternal->m_solver = nullptr;

    m_pInternal->m_collisionConfiguration = std::make_unique<btDefaultCollisionConfiguration>();
    m_pInternal->m_dispatcher = std::make_unique<btCollisionDispatcher>(m_pInternal->m_collisionConfiguration.get());
    m_pInternal->m_overlappingPairCache = std::make_unique<btDbvtBroadphase>();
    m_pInternal->m_solver = std::make_unique<btSequentialImpulseConstraintSolver>();
    
    m_pInternal->m_dynamicsWorld = std::make_unique<btDiscreteDynamicsWorld>(
        m_pInternal->m_dispatcher.get(), m_pInternal->m_overlappingPairCache.get(), m_pInternal->m_solver.get(), m_pInternal->m_collisionConfiguration.get());
    m_pInternal->m_dynamicsWorld->setGravity(btVector3(0, -10, 0));
}

void LE3PhysicsManager::update(float deltaTime) {
    if (!m_bPhysicsEnabled) return;
    m_pInternal->m_dynamicsWorld->stepSimulation(deltaTime);
}

void LE3PhysicsManager::registerComponent(std::string name, LE3PhysicsComponent& component) {
    clearComponent(name);
    btRigidBody* rb = (btRigidBody*)component.getRigidBody();
    m_pInternal->m_dynamicsWorld->addRigidBody(rb);
    m_pInternal->m_rigidBodies[name] = rb;
}

void LE3PhysicsManager::clearComponent(std::string name) {
    if (m_pInternal->m_rigidBodies.find(name) != m_pInternal->m_rigidBodies.end()) {
        m_pInternal->m_dynamicsWorld->removeRigidBody(m_pInternal->m_rigidBodies[name]);
        m_pInternal->m_rigidBodies.erase(name);
    }
}

bool LE3PhysicsManager::rayTest(glm::vec3 from, glm::vec3 to) {
    if (!m_bPhysicsEnabled) return false;

    btVector3 btFrom(from.x, from.y, from.z);
    btVector3 btTo(to.x, to.y, to.z);
    btCollisionWorld::ClosestRayResultCallback rayCallback(btFrom, btTo);
    m_pInternal->m_dynamicsWorld->rayTest(btFrom, btTo, rayCallback);

    return rayCallback.hasHit();
}