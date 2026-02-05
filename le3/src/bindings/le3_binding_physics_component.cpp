#include "scripting/le3_script_bindings.h"
#include "core/le3_engine_systems.h"
using namespace le3;


FBIND_GETTER_BOOL(LE3PhysicsComponent, is_trigger, isTrigger)
FBIND_SETTER_BOOL(LE3PhysicsComponent, set_is_trigger, setIsTrigger)

FBIND_GETTER_BOOL(LE3PhysicsComponent, is_kinematic, isKinematic)
FBIND_SETTER_BOOL(LE3PhysicsComponent, set_kinematic, setKinematic)

FBIND_GETTER_BOOL(LE3PhysicsComponent, is_rigidbody, isRigidBody)
FBIND_SETTER_BOOL(LE3PhysicsComponent, set_is_rigidbody, setIsRigidBody)

FBIND_GETTER_NUMBER(LE3PhysicsComponent, get_mass, getMass)
FBIND_SETTER_NUMBER(LE3PhysicsComponent, set_mass, setMass)

FBIND_GETTER_VEC3(LE3PhysicsComponent, get_linear_velocity, getLinearVelocity)
FBIND_SETTER_VEC3(LE3PhysicsComponent, set_linear_velocity, setLinearVelocity)
FBIND_GETTER_VEC3(LE3PhysicsComponent, get_angular_velocity, getAngularVelocity)
FBIND_SETTER_VEC3(LE3PhysicsComponent, set_angular_velocity, setAngularVelocity)
FBIND_SETTER_VEC3(LE3PhysicsComponent, set_angular_factor, setAngularFactor)

FBIND_SETTER_QUAT(LE3PhysicsComponent, set_rotation, setRotation)

FBIND_SETTER_BOOL(LE3PhysicsComponent, set_manual_collider_override, setManualColliderOverride)
FBIND_GETTER_BOOL(LE3PhysicsComponent, is_manual_collider_override, isManualColliderOverride)
FBIND_SETTER_VEC3(LE3PhysicsComponent, set_manual_centroid, setManualCentroid)
FBIND_GETTER_VEC3(LE3PhysicsComponent, get_manual_centroid, getManualCentroid)
FBIND_SETTER_VEC3(LE3PhysicsComponent, set_manual_extent, setManualExtent)
FBIND_GETTER_VEC3(LE3PhysicsComponent, get_manual_extent, getManualExtent)
FBIND_GETTER_NUMBER(LE3PhysicsComponent, get_manual_radius, getManualRadius)
FBIND_SETTER_NUMBER(LE3PhysicsComponent, set_manual_radius, setManualRadius)

FBIND(LE3PhysicsComponent, set_manual_collider_type)
    GET_UDATA(component, LE3PhysicsComponent)
    GET_STRING(type)
    LE3ColliderType colliderType = LE3ColliderType_fromString(type);
    component->setManualColliderType(colliderType);
FEND()

FBIND(LE3PhysicsComponent, get_manual_collider_type)
    GET_UDATA(component, LE3PhysicsComponent)
    PUSH_STRING(LE3ColliderType_toString(component->getManualColliderType()))
FEND()

FBIND(LE3PhysicsComponent, warp)
    GET_UDATA(component, LE3PhysicsComponent)
    GET_VEC3_(position)
    GET_QUAT(rotation)
    component->warp(position, rotation);
FEND()

FBIND_GETTER_VEC3(LE3PhysicsComponent, get_total_force, getTotalForce)
FBIND_SETTER_VEC3(LE3PhysicsComponent, apply_impulse, applyImpulse)

FBIND(LE3PhysicsComponent, probe_collision)
    GET_UDATA(component, LE3PhysicsComponent)
    GET_VEC3(probe)
    bool result = component->probeCollision(probe);
    PUSH_BOOL(result);
FEND()

LIB(LE3PhysicsComponent,
    is_trigger, set_is_trigger,
    is_kinematic, set_kinematic,
    is_rigidbody, set_is_rigidbody,
    get_mass, set_mass,
    get_linear_velocity, set_linear_velocity, get_angular_velocity, set_angular_velocity, set_angular_factor,
    set_rotation,
    warp,
    get_total_force, apply_impulse, probe_collision,

    set_manual_collider_override, is_manual_collider_override,
    set_manual_collider_type, get_manual_collider_type,
    set_manual_centroid, get_manual_centroid,
    set_manual_extent, get_manual_extent,
    get_manual_radius, set_manual_radius
)