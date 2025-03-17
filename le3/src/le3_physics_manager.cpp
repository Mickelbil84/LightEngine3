#include "le3_physics_manager.h"
using namespace le3;

void LE3PhysicsManager::reset() {
    m_collisionConfiguration = std::make_unique<btDefaultCollisionConfiguration>();
    m_dispatcher = std::make_unique<btCollisionDispatcher>(m_collisionConfiguration.get());
    m_overlappingPairCache = std::make_unique<btDbvtBroadphase>();
    m_solver = std::make_unique<btSequentialImpulseConstraintSolver>();
    
    m_dynamicsWorld = std::make_unique<btDiscreteDynamicsWorld>(m_dispatcher.get(), m_overlappingPairCache.get(), m_solver.get(), m_collisionConfiguration.get());
    m_dynamicsWorld->setGravity(btVector3(0, -10, 0));
}

void LE3PhysicsManager::update(float deltaTime) {
    if (!m_bPhysicsEnabled) return;
    m_dynamicsWorld->stepSimulation(deltaTime);
}