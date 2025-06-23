#include "scripting/le3_script_bindings.h"
#include "core/le3_engine_systems.h"
using namespace le3;

FBIND_OBJECT_GETTER_NUMBER(LE3Camera, get_fov, getFov)
FBIND_OBJECT_SETTER_NUMBER(LE3Camera, set_fov, setFov)

FBIND(LE3Camera, move_forward)
    GET_UDATA_OBJECT(camera, LE3Camera)
    GET_NUMBER(amount)
    camera->moveForward(amount);
FEND()
FBIND(LE3Camera, move_right)
    GET_UDATA_OBJECT(camera, LE3Camera)
    GET_NUMBER(amount)
    camera->moveRight(amount);
FEND()
FBIND(LE3Camera, move_up)
    GET_UDATA_OBJECT(camera, LE3Camera)
    GET_NUMBER(amount)
    camera->moveUp(amount);
FEND()
FBIND(LE3Camera, add_pitch_yaw)
    GET_UDATA_OBJECT(camera, LE3Camera)
    GET_NUMBER(pitch)
    GET_NUMBER(yaw)
    camera->addPitchYaw(pitch, yaw);
FEND()

FBIND_OBJECT_GETTER_VEC3(LE3Camera, get_forward, getForward)
FBIND_OBJECT_GETTER_VEC3(LE3Camera, get_right, getRight)
FBIND_OBJECT_GETTER_VEC3(LE3Camera, get_up, getUp)
FBIND_OBJECT_GETTER_QUAT(LE3Camera, get_xz_rotation, getXZRotation)

LIB(LE3Camera, 
    get_fov, set_fov,
    move_forward, move_right, move_up, add_pitch_yaw,
    get_xz_rotation,
    get_forward, get_right, get_up
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