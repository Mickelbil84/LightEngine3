#include "le3_script_bindings.h"
#include "le3_engine_systems.h"
using namespace le3;

static int bnd_LE3Camera_getFov(lua_State* L) {
    int idx = 1;
    LE3CameraPtr camera = getUserType_LE3Object<LE3Camera>(idx++);
    LE3GetScriptSystem().pushNumber(camera->getFov());
    return 1;
}

static int bnd_LE3Camera_setFov(lua_State* L) {
    int idx = 1;
    LE3CameraPtr camera = getUserType_LE3Object<LE3Camera>(idx++);
    float fov = LE3GetScriptSystem().getNumber(idx++);
    camera->setFov(fov);
    return 0;
}

static const luaL_Reg LE3CameraLib[] = {
    {"get_fov", bnd_LE3Camera_getFov},
    {"set_fov", bnd_LE3Camera_setFov},
    {NULL, NULL}
};

int le3::luaopen_LE3Camera(lua_State* L) {
    luaL_newlib(L, LE3CameraLib);
    return 1;
}

//---------------------------------------------------

static int bnd_LE3Camera_getOffset(lua_State* L) {
    int idx = 1;
    LE3OrbitCameraPtr camera = getUserType_LE3Object<LE3OrbitCamera>(idx++);
    LE3GetScriptSystem().pushNumber((camera)->getOffset());
    return 1;
}

static int bnd_LE3Camera_setOffset(lua_State* L) {
    int idx = 1;
    LE3OrbitCameraPtr camera = getUserType_LE3Object<LE3OrbitCamera>(idx++);
    float offset = LE3GetScriptSystem().getNumber(idx++);
    (camera)->setOffset(offset);
    return 0;
}

static int bnd_LE3Camera_getOrigin(lua_State* L) {
    int idx = 1;
    LE3OrbitCameraPtr camera = getUserType_LE3Object<LE3OrbitCamera>(idx++);
    glm::vec3 origin = (camera)->getOrigin();
    LE3GetScriptSystem().pushNumber(origin.x);
    LE3GetScriptSystem().pushNumber(origin.y);
    LE3GetScriptSystem().pushNumber(origin.z);
    return 3;
}

static int bnd_LE3Camera_setOrigin(lua_State* L) {
    int idx = 1;
    LE3OrbitCameraPtr camera = getUserType_LE3Object<LE3OrbitCamera>(idx++);
    float x = LE3GetScriptSystem().getNumber(idx++);
    float y = LE3GetScriptSystem().getNumber(idx++);
    float z = LE3GetScriptSystem().getNumber(idx++);
    (camera)->setOrigin(glm::vec3(x, y, z));
    return 0;
}

static const luaL_Reg LE3OrbitCameraLib[] = {
    {"get_offset", bnd_LE3Camera_getOffset},
    {"set_offset", bnd_LE3Camera_setOffset},
    {"get_origin", bnd_LE3Camera_getOrigin},
    {"set_origin", bnd_LE3Camera_setOrigin},
    {NULL, NULL}
};

int le3::luaopen_LE3OrbitCamera(lua_State* L) {
    luaL_newlib(L, LE3OrbitCameraLib);
    return 1;
}

//---------------------------------------------------

static const luaL_Reg LE3FreeCameraLib[] = {
    {NULL, NULL}
};

int le3::luaopen_LE3FreeCamera(lua_State* L) {
    luaL_newlib(L, LE3FreeCameraLib);
    return 1;
}