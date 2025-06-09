#include "physics/le3_physics.h"
#include "physics/le3_physics_manager.h"
#include "core/le3_engine_systems.h"
using namespace le3;

#include <bullet/btBulletDynamicsCommon.h>

#define UUID_SYSTEM_GENERATOR
#include <uuid.h>

struct le3::LE3PhysicsCollider {
    std::shared_ptr<btCollisionShape> m_collisionShape;
};
struct le3::LE3PhysicsRigidBody {
    btTransform m_transform;
    btScalar m_mass = 0;

    std::shared_ptr<btDefaultMotionState> m_motionState;
    std::shared_ptr<btRigidBody> m_rigidBody;

};

LE3PhysicsComponent::LE3PhysicsComponent(LE3Transform& transform, bool isRigidBody) : m_transform(transform), m_bEnabled(false), m_bIsTrigger(false) , m_bRigidBody(isRigidBody)
{
    m_componentName = uuids::to_string(uuids::uuid_system_generator{}());
    m_rigidBody = std::make_shared<LE3PhysicsRigidBody>();
}

void LE3PhysicsComponent::disable() {
    if (!m_bRigidBody) return;
    m_bEnabled = false;
    LE3GetPhysicsManager().clearComponent(m_componentName);
}

void LE3PhysicsComponent::enable() {
    if (!m_bRigidBody) return;
    if (!m_collider) return;
    if (!m_rigidBody->m_rigidBody) return;
    m_bEnabled = true;
    LE3GetPhysicsManager().registerComponent(m_componentName, *this);
}

void LE3PhysicsComponent::addBoxCollider(glm::vec3 size) {
    if (!m_bRigidBody) return;
    m_collider = std::make_shared<LE3PhysicsCollider>();
    m_collider->m_collisionShape = std::make_shared<btBoxShape>(btVector3(size.x, size.y, size.z));
}
void LE3PhysicsComponent::addSphereCollider(float radius) {
    if (!m_bRigidBody) return;
    m_collider = std::make_shared<LE3PhysicsCollider>();
    m_collider->m_collisionShape = std::make_shared<btSphereShape>(radius);
}

void LE3PhysicsComponent::setupRigidBody(LE3ColliderInfo colliderInfo) {
    if (!m_bRigidBody) return;
    if (m_collider) m_collider = nullptr;
    // Setup colliders
    m_colliderInfo = colliderInfo;
    glm::vec3 extent = m_colliderInfo.extent;
    glm::vec3 scale = m_transform.getScale();
    switch (m_colliderInfo.colliderType) {
        case LE3ColliderType::LE3ColliderType_Box:
            addBoxCollider(glm::vec3(extent.x * scale.x, extent.y * scale.y, extent.z * scale.z));
            break;
        case LE3ColliderType::LE3ColliderType_Sphere:
            addSphereCollider(m_colliderInfo.radius * m_transform.getScale().x); break;
        default:
            break;
    }
    if (!m_collider) return;

    m_rigidBody->m_transform = btTransform(
        btQuaternion(m_transform.getRotation().x, m_transform.getRotation().y, m_transform.getRotation().z, m_transform.getRotation().w),
        btVector3(m_transform.getPosition().x, m_transform.getPosition().y, m_transform.getPosition().z)
    );

    m_rigidBody->m_motionState = std::make_shared<btDefaultMotionState>(m_rigidBody->m_transform);
    btRigidBody::btRigidBodyConstructionInfo rbInfo = btRigidBody::btRigidBodyConstructionInfo(
        m_rigidBody->m_mass, m_rigidBody->m_motionState.get(), m_collider->m_collisionShape.get());
    m_rigidBody->m_rigidBody = std::make_shared<btRigidBody>(rbInfo);
}

void* LE3PhysicsComponent::getRigidBody() {
    if (!m_bRigidBody) return nullptr;
    return m_rigidBody->m_rigidBody.get();
}

bool LE3PhysicsComponent::update() {
    if (!m_bRigidBody) return false;
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

void LE3PhysicsComponent::warp(glm::vec3 position, glm::quat rotation) {
    if (!m_bRigidBody) return;
    m_rigidBody->m_rigidBody->setLinearVelocity(btVector3(0, 0, 0));
    m_rigidBody->m_rigidBody->setAngularVelocity(btVector3(0, 0, 0));
    m_rigidBody->m_motionState->setWorldTransform(btTransform(
        btQuaternion(rotation.x, rotation.y, rotation.z, rotation.w),
        btVector3(position.x, position.y, position.z)
    ));
    m_rigidBody->m_rigidBody->setMotionState(m_rigidBody->m_motionState.get());
    // m_rigidBody->m_rigidBody->setGravity(btVector3(0, -10, 0));
}

void LE3PhysicsComponent::setMass(float mass) {
    if (!m_bRigidBody) return;
    m_rigidBody->m_mass = mass;
    if (m_rigidBody->m_rigidBody)
        m_rigidBody->m_rigidBody->setMassProps(mass, btVector3());
}

float LE3PhysicsComponent::getMass() {
    return m_rigidBody->m_mass;
}