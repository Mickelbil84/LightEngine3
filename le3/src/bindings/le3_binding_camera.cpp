#include "le3_script_bindings.h"
#include "le3_engine_systems.h"
using namespace le3;

FBIND_OBJECT_GETTER_NUMBER(LE3Camera, get_fov, getFov)
FBIND_OBJECT_SETTER_NUMBER(LE3Camera, set_fov, setFov)

LIB(LE3Camera, 
    get_fov, set_fov
)

//---------------------------------------------------


FBIND_OBJECT_GETTER_NUMBER(LE3OrbitCamera, get_offset, getOffset)
FBIND_OBJECT_SETTER_NUMBER(LE3OrbitCamera, set_offset, setOffset)

FBIND_OBJECT_GETTER_VEC3(LE3OrbitCamera, get_origin, getOrigin)
FBIND_OBJECT_SETTER_VEC3(LE3OrbitCamera, set_origin, setOrigin)

LIB(LE3OrbitCamera,
    get_offset, set_offset,
    get_origin, set_origin
)

//---------------------------------------------------

LIB(LE3FreeCamera)