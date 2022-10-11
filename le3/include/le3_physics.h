#pragma once
#include <glm/glm.hpp>
#include "btBulletDynamicsCommon.h"

struct LE3BoxCollision
{
    LE3BoxCollision(glm::vec3 lowerBound=glm::vec3(), glm::vec3 upperBound=glm::vec3());
    glm::vec3 lowerBound, upperBound;

    btCollisionShape* ToBullet();
};

class LE3PhysicsComponent
{
public:
    void Init();

    btDiscreteDynamicsWorld* GetWorld() const;

private:
    btBroadphaseInterface* m_pBroadphase;
    btDefaultCollisionConfiguration* m_pCollisionConfiguration;
    btCollisionDispatcher* m_pCollisionDispatcher;
    btSequentialImpulseConstraintSolver* m_pConstraintSolver;
    btDiscreteDynamicsWorld* m_pWorld;
};