#include "le3_physics.h"
#include "le3_physics_manager.h"
#include "le3_engine_systems.h"
using namespace le3;

#include <bullet/btBulletDynamicsCommon.h>

struct le3::LE3PhysicsCollider {
    std::shared_ptr<btCollisionShape> m_collisionShape;
};
struct le3::LE3PhysicsRigidBody {
    btTransform m_transform;
    btScalar m_mass;

    std::shared_ptr<btDefaultMotionState> m_motionState;
    std::shared_ptr<btRigidBody> m_rigidBody;

};

LE3PhysicsComponent::LE3PhysicsComponent(LE3Transform& transform) : m_transform(transform), m_bEnabled(false), m_bIsTrigger(false) 
{
}

void LE3PhysicsComponent::enable() {
    if (!m_collider) return;
    if (!m_rigidBody) return;
    m_bEnabled = true;
    LE3GetPhysicsManager().registerComponent(*this);
}

void LE3PhysicsComponent::addBoxCollider(glm::vec3 size) {
    m_collider = std::make_shared<LE3PhysicsCollider>();
    m_collider->m_collisionShape = std::make_shared<btBoxShape>(btVector3(size.x, size.y, size.z));
}
void LE3PhysicsComponent::addSphereCollider(float radius) {
    m_collider = std::make_shared<LE3PhysicsCollider>();
    m_collider->m_collisionShape = std::make_shared<btSphereShape>(radius);
}

void LE3PhysicsComponent::setupRigidBody(float mass) {
    m_rigidBody = std::make_shared<LE3PhysicsRigidBody>();
    m_rigidBody->m_mass = mass;
    m_rigidBody->m_transform = btTransform(
        btQuaternion(m_transform.getRotation().x, m_transform.getRotation().y, m_transform.getRotation().z, m_transform.getRotation().w),
        btVector3(m_transform.getPosition().x, m_transform.getPosition().y, m_transform.getPosition().z)
    );

    m_rigidBody->m_motionState = std::make_shared<btDefaultMotionState>(m_rigidBody->m_transform);
    btRigidBody::btRigidBodyConstructionInfo rbInfo = btRigidBody::btRigidBodyConstructionInfo(mass, m_rigidBody->m_motionState.get(), m_collider->m_collisionShape.get());
    m_rigidBody->m_rigidBody = std::make_shared<btRigidBody>(rbInfo);
}

void* LE3PhysicsComponent::getRigidBody() {
    return m_rigidBody->m_rigidBody.get();
}

bool LE3PhysicsComponent::update() {
    if (!m_bEnabled) return false;
    if (!m_rigidBody) return false;
    if (m_rigidBody->m_mass <= 0) return false;

    btTransform trans;
    m_rigidBody->m_rigidBody->getMotionState()->getWorldTransform(trans);
    glm::quat rot = glm::quat(trans.getRotation().getX(), trans.getRotation().getY(), trans.getRotation().getZ(), trans.getRotation().getW());
    glm::vec3 pos = glm::vec3(float(trans.getOrigin().getX()), float(trans.getOrigin().getY()), float(trans.getOrigin().getZ()));
    m_transform.setRotation(rot);
    m_transform.setPosition(pos);

    return true;
}