#include "le3_physics.h"
#include <iostream>

LE3BoxCollision::LE3BoxCollision(glm::vec3 lowerBound, glm::vec3 upperBound)
{
    this->lowerBound = lowerBound;
    this->upperBound = upperBound;
}

btCollisionShape* LE3BoxCollision::ToBullet()
{
    btBoxShape* pBoxShape = new btBoxShape(btVector3(
        0.5f * (upperBound.x - lowerBound.x),
        0.5f * (upperBound.y - lowerBound.y),
        0.5f * (upperBound.z - lowerBound.z)
    ));
    btCompoundShape* pOffsetBoxShape = new btCompoundShape();
    btTransform localCoords;
    localCoords.setIdentity();
    localCoords.setOrigin(btVector3(
        upperBound.x - 0.5f * (upperBound.x - lowerBound.x),
        upperBound.y - 0.5f * (upperBound.y - lowerBound.y),
        upperBound.z - 0.5f * (upperBound.z - lowerBound.z)
    ));
    pOffsetBoxShape->addChildShape(localCoords, pBoxShape);
    return (btCollisionShape*)pOffsetBoxShape;
}

void LE3PhysicsComponent::Init()
{
    m_pBroadphase = new btDbvtBroadphase();
    m_pCollisionConfiguration = new btDefaultCollisionConfiguration();
    m_pCollisionDispatcher = new btCollisionDispatcher(m_pCollisionConfiguration);

    m_pConstraintSolver = new btSequentialImpulseConstraintSolver;
    m_pWorld = new btDiscreteDynamicsWorld(m_pCollisionDispatcher, m_pBroadphase, m_pConstraintSolver, m_pCollisionConfiguration);
    m_pWorld->setGravity(btVector3(0, -9.81f, 0));
    std::cout << "Initiallized Bullet!" << std::endl;
}

btDiscreteDynamicsWorld* LE3PhysicsComponent::GetWorld() const
{
    return m_pWorld;
}