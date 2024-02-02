#include "le3_script_bindings.h"
#include "le3_engine_systems.h"
using namespace le3;

static const luaL_Reg LE3CameraLib[] = {
    {NULL, NULL}
};

int le3::luaopen_LE3Camera(lua_State* L) {
    luaL_newlib(L, LE3CameraLib);
    return 1;
}

static const luaL_Reg LE3OrbitCameraLib[] = {
    {NULL, NULL}
};

int le3::luaopen_LE3OrbitCamera(lua_State* L) {
    luaL_newlib(L, LE3OrbitCameraLib);
    return 1;
}

static const luaL_Reg LE3FreeCameraLib[] = {
    {NULL, NULL}
};

int le3::luaopen_LE3FreeCamera(lua_State* L) {
    luaL_newlib(L, LE3FreeCameraLib);
    return 1;
}