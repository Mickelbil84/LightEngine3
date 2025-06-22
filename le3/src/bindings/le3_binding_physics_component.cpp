#include "scripting/le3_script_bindings.h"
#include "core/le3_engine_systems.h"
using namespace le3;


FBIND_GETTER_BOOL(LE3PhysicsComponent, is_trigger, isTrigger)
FBIND_SETTER_BOOL(LE3PhysicsComponent, set_is_trigger, setIsTrigger)

FBIND_GETTER_BOOL(LE3PhysicsComponent, is_rigidbody, isRigidBody)
FBIND_SETTER_BOOL(LE3PhysicsComponent, set_is_rigidbody, setIsRigidBody)

FBIND_GETTER_NUMBER(LE3PhysicsComponent, get_mass, getMass)
FBIND_SETTER_NUMBER(LE3PhysicsComponent, set_mass, setMass)

FBIND_SETTER_VEC3(LE3PhysicsComponent, set_linear_velocity, setLinearVelocity)
FBIND_SETTER_VEC3(LE3PhysicsComponent, set_angular_velocity, setAngularVelocity)
FBIND_SETTER_VEC3(LE3PhysicsComponent, set_angular_factor, setAngularFactor)

LIB(LE3PhysicsComponent,
    is_trigger, set_is_trigger,
    is_rigidbody, set_is_rigidbody,
    get_mass, set_mass,
    set_linear_velocity, set_angular_velocity, set_angular_factor
)