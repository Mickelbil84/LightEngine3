#include "le3_script_bindings.h"
#include "le3_engine_systems.h"
using namespace le3;


FBIND_GETTER_VEC3(LE3Transform, get_position, getPosition)
FBIND_SETTER_VEC3(LE3Transform, set_position, setPosition)

FBIND_GETTER_QUAT(LE3Transform, get_rotation, getRotation)
FBIND_SETTER_QUAT(LE3Transform, set_rotation, setRotation)

FBIND_GETTER_VEC3(LE3Transform, get_scale, getScale)
FBIND_SETTER_VEC3(LE3Transform, set_scale, setScale)

LIB(LE3Transform,
    get_position, set_position,
    get_rotation, set_rotation,
    get_scale, set_scale,
)