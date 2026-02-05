#include "physics/le3_physics.h"
#include "physics/le3_physics_manager.h"
#include "core/le3_engine_systems.h"
using namespace le3;

#include <bullet/btBulletDynamicsCommon.h>
#include <bullet/BulletCollision/CollisionShapes/btShapeHull.h>

#define UUID_SYSTEM_GENERATOR
#include <uuid.h>

struct le3::LE3PhysicsCollider {
    std::shared_ptr<btCollisionShape> m_collisionShape;
    
    // For btCompoundShape
    std::vector<std::shared_ptr<btCollisionShape>> m_compoundSubshapes; // Also store smart pointers to subshapes

    // For btMultiSphereShape
    std::vector<btVector3> m_multiSpherePositions;
    std::vector<float> m_multiSphereRadii;
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

void LE3PhysicsComponent::setKinematic(bool kinematic) {
    if (!m_rigidBody->m_rigidBody) return;
    int flags = m_rigidBody->m_rigidBody->getCollisionFlags();
    if (kinematic)
        flags |= btCollisionObject::CF_KINEMATIC_OBJECT;
    else
        flags &= ~btCollisionObject::CF_KINEMATIC_OBJECT;
    m_rigidBody->m_rigidBody->setCollisionFlags(flags);
}
bool LE3PhysicsComponent::isKinematic() const {
    if (!m_rigidBody->m_rigidBody) return false;
    return (m_rigidBody->m_rigidBody->getCollisionFlags() & btCollisionObject::CF_KINEMATIC_OBJECT) != 0;
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
    m_collider->m_collisionShape = std::make_shared<btBoxShape>(0.5f * btVector3(size.x, size.y, size.z));
}
void LE3PhysicsComponent::addSphereCollider(float radius, glm::vec3 scaling) {
    bool isUniform = glm::all(glm::epsilonEqual(scaling, glm::vec3(scaling.x), 1e-6f));
    if (isUniform) {
        m_collider->m_collisionShape = std::make_shared<btSphereShape>(radius * scaling.x);
    }
    else {
        // Scaled sphere
        m_collider->m_multiSpherePositions.push_back(btVector3());
        m_collider->m_multiSphereRadii.push_back(radius);
        m_collider->m_collisionShape = std::make_shared<btMultiSphereShape>(
            &m_collider->m_multiSpherePositions[0],
            &m_collider->m_multiSphereRadii[0], 1
        );
        m_collider->m_collisionShape->setLocalScaling(btVector3(scaling.x, scaling.y, scaling.z));
    }
}
void LE3PhysicsComponent::addCylinderCollider(glm::vec3 size) {
    m_collider->m_collisionShape = std::make_shared<btCylinderShape>(0.5f * btVector3(size.x, size.y, size.z));
}
void LE3PhysicsComponent::addConeCollider(glm::vec3 size) {
    float radius = 0.5f * (size.x > size.z ? size.x : size.z);
    float height = size.y;
    m_collider->m_collisionShape = std::make_shared<btConeShape>(radius, height);
}
void LE3PhysicsComponent::addCapsuleCollider(glm::vec3 size) {
    float radius = 0.5f * (size.x > size.z ? size.x : size.z);
    float height = 0.5f * size.y;
    m_collider->m_collisionShape = std::make_shared<btCapsuleShape>(radius, height);
}
void LE3PhysicsComponent::addConvexHullCollider(std::vector<glm::vec3> vertices, glm::vec3 centroid, glm::vec3 scaling) {
    std::shared_ptr<btConvexHullShape> shape = std::make_shared<btConvexHullShape>();
    m_collider->m_collisionShape = std::dynamic_pointer_cast<btCollisionShape>(shape);
    for (glm::vec3 v : vertices) {
        v -= centroid;
        v *= scaling;
        btVector3 v_(v.x, v.y, v.z);
        shape->addPoint(v_);
    }
    shape->optimizeConvexHull();
    btShapeHull* shapeHull = new btShapeHull(shape.get());
    shapeHull->buildHull(0, 1);
    std::vector<LE3Vertex3p> hullVertices;
    std::vector<uint32_t> hullIndices;
    int idx = 0;
    auto vertexPtr = shapeHull->getVertexPointer();
    int n = shapeHull->numVertices();
    while (idx < n) {
        LE3Vertex3p v;
        v.position[0] = vertexPtr->x();
        v.position[1] = vertexPtr->y();
        v.position[2] = vertexPtr->z();
        hullVertices.push_back(v);
        vertexPtr++;
        idx++;
    }
    idx = 0;
    auto indexPtr = shapeHull->getIndexPointer();
    n = shapeHull->numIndices();
    while (idx < n) {
        hullIndices.push_back(*indexPtr);
        indexPtr++;
        idx++;
    }
    delete shapeHull;

    m_hullMesh = std::make_shared<LE3DebugMesh>(hullVertices, hullIndices);
}

void LE3PhysicsComponent::setupRigidBody(LE3ColliderInfo colliderInfo) {
    if (!m_bRigidBody) return;
    if (m_collider) m_collider = nullptr;
    // Setup colliders
    m_colliderInfo = colliderInfo;
    if (m_bColliderOverride) m_colliderInfo = m_colliderOverride;
    glm::vec3 extent = m_colliderInfo.extent;
    glm::vec3 scale = m_transform.getScale();
    m_collider = std::make_shared<LE3PhysicsCollider>();
    switch (m_colliderInfo.colliderType) {
        case LE3ColliderType::LE3ColliderType_Box:
            addBoxCollider(glm::vec3(extent.x * scale.x, extent.y * scale.y, extent.z * scale.z)); break;
        case LE3ColliderType::LE3ColliderType_Sphere:
            addSphereCollider(m_colliderInfo.radius, m_transform.getScale()); break;
        case LE3ColliderType::LE3ColliderType_Cone:
            addConeCollider(scale * extent); break; // Does not support non-uniform xz scaling 
        case LE3ColliderType::LE3ColliderType_Cylinder:
            addCylinderCollider(scale * extent); break; // Does not support non-uniform xz scaling
        case LE3ColliderType::LE3ColliderType_Capsule:
            addCapsuleCollider(scale * extent); break; // Does not support non-uniform xz scaling
        case LE3ColliderType::LE3ColliderType_ConvexHull:
            addConvexHullCollider(m_colliderInfo.decimatedVertices, m_colliderInfo.centroid, m_transform.getScale()); break;
        default:
            break;
    }
    if (!m_collider) return;

    glm::vec3 offset = m_colliderInfo.centroid;
    offset = glm::vec3(m_transform.getTransformMatrix() * glm::vec4(offset, 1.f));
    m_rigidBody->m_transform = btTransform(
        btQuaternion(m_transform.getRotation().x, m_transform.getRotation().y, m_transform.getRotation().z, m_transform.getRotation().w),
        btVector3(offset.x, offset.y, offset.z)
    );
    m_initialRotation = m_transform.getRotation();

    m_rigidBody->m_motionState = std::make_shared<btDefaultMotionState>(m_rigidBody->m_transform);
    btVector3 inertia(0,0,0);
    m_collider->m_collisionShape->calculateLocalInertia(m_rigidBody->m_mass, inertia);
    btRigidBody::btRigidBodyConstructionInfo rbInfo = btRigidBody::btRigidBodyConstructionInfo(
        m_rigidBody->m_mass, m_rigidBody->m_motionState.get(), m_collider->m_collisionShape.get(), inertia);
    m_rigidBody->m_rigidBody = std::make_shared<btRigidBody>(rbInfo);
    m_rigidBody->m_rigidBody->setLinearVelocity(btVector3(0,0,0));
    m_rigidBody->m_rigidBody->setAngularVelocity(btVector3(0,0,0));
    m_rigidBody->m_rigidBody->clearForces();
    m_rigidBody->m_rigidBody->setDamping(0.25f, 0.25f); // TODO: set this as controllable properties
    m_rigidBody->m_rigidBody->setActivationState(DISABLE_DEACTIVATION);
}

void* LE3PhysicsComponent::getRigidBody() {
    if (!m_bRigidBody) return nullptr;
    return m_rigidBody->m_rigidBody.get();
}

bool LE3PhysicsComponent::update() {
    if (LE3EngineSystems::instance().isEditModeEngine()) return false;
    if (!m_bRigidBody) return false;
    if (!m_bEnabled) return false;
    if (!m_rigidBody->m_rigidBody) return false;
    if (m_rigidBody->m_mass <= 0) return false;

    btTransform trans;
    m_rigidBody->m_rigidBody->getMotionState()->getWorldTransform(trans);
    glm::quat rot = glm::quat(trans.getRotation().getW(), trans.getRotation().getX(), trans.getRotation().getY(), trans.getRotation().getZ());
    glm::vec3 pos = glm::vec3(float(trans.getOrigin().getX()), float(trans.getOrigin().getY()), float(trans.getOrigin().getZ()));
    m_transform.setRotation(rot);
    m_transform.setPosition(pos);
    if (m_colliderInfo.colliderType != LE3ColliderType::LE3ColliderType_Capsule)
        m_transform.setPosition(glm::vec3(m_transform.getTransformMatrix() * glm::vec4(-m_colliderInfo.centroid, 1.f)));
    else 
        m_transform.setPosition(glm::vec3(m_transform.getTransformMatrix() * glm::vec4(0.f, 0.f, 0.f, 1.f)));

    return true;
}

void LE3PhysicsComponent::warp(glm::vec3 position, glm::quat rotation) {
    if (!m_bRigidBody) return;
    m_rigidBody->m_rigidBody->setLinearVelocity(btVector3(0, 0, 0));
    m_rigidBody->m_rigidBody->setAngularVelocity(btVector3(0, 0, 0));
    // Visual transform gets the position directly
    m_transform.setPosition(position);
    m_transform.setRotation(rotation);
    // Bullet body needs the centroid offset applied
    glm::vec3 bulletPos = glm::vec3(m_transform.getTransformMatrix() * glm::vec4(m_colliderInfo.centroid, 1.f));
    m_rigidBody->m_motionState->setWorldTransform(btTransform(
        btQuaternion(rotation.x, rotation.y, rotation.z, rotation.w),
        btVector3(bulletPos.x, bulletPos.y, bulletPos.z)
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

glm::vec3 LE3PhysicsComponent::getLinearVelocity() const {
    btVector3 v = m_rigidBody->m_rigidBody->getLinearVelocity();
    return glm::vec3(v.x(), v.y(), v.z());
}
void LE3PhysicsComponent::setLinearVelocity(glm::vec3 velocity) {
    m_rigidBody->m_rigidBody->setLinearVelocity(btVector3(velocity.x, velocity.y, velocity.z));
}

glm::vec3 LE3PhysicsComponent::getAngularVelocity() const {
    btVector3 v = m_rigidBody->m_rigidBody->getAngularVelocity();
    return glm::vec3(v.x(), v.y(), v.z());
}
void LE3PhysicsComponent::setAngularVelocity(glm::vec3 velocity) {
    m_rigidBody->m_rigidBody->setAngularVelocity(btVector3(velocity.x, velocity.y, velocity.z));
}
void LE3PhysicsComponent::setAngularFactor(glm::vec3 factor) {
    m_rigidBody->m_rigidBody->setAngularFactor(btVector3(factor.x, factor.y, factor.z));
}

void LE3PhysicsComponent::setRotation(glm::quat rotation) {
    btTransform t = m_rigidBody->m_rigidBody->getWorldTransform();
    rotation = rotation * m_initialRotation; // Apply new rotation on top of the initial rotation
    t.setRotation(btQuaternion(rotation.x, rotation.y, rotation.z, rotation.w));
    m_rigidBody->m_rigidBody->setWorldTransform(t);
    m_rigidBody->m_rigidBody->setInterpolationWorldTransform(t);
}

void LE3PhysicsComponent::applyImpulse(glm::vec3 impulse) {
    btVector3 impulseVec(impulse.x, impulse.y, impulse.z);
    btVector3 relPos;
    // m_rigidBody->m_rigidBody->applyImpulse(impulseVec, relPos);
    m_rigidBody->m_rigidBody->applyCentralImpulse(impulseVec);
}

glm::vec3 LE3PhysicsComponent::getTotalForce() const {
    btVector3 force = m_rigidBody->m_rigidBody->getTotalForce();
    return glm::vec3(force.x(), force.y(), force.z());
}

bool LE3PhysicsComponent::probeCollision(glm::vec3 probe) {
    btVector3 from = m_rigidBody->m_rigidBody->getWorldTransform().getOrigin();
    return LE3GetPhysicsManager().rayTest(glm::vec3(from.x(), from.y(), from.z()), glm::vec3(from.x(), from.y(), from.z()) + probe);
}