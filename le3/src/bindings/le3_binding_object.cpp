#include "le3_script_bindings.h"
#include "le3_engine_systems.h"
using namespace le3;

static int bnd_LE3Object_getTransform(lua_State* L) {
    int idx = 1;
    LE3ObjectPtr* object = LE3GetScriptSystem().getUserType<LE3ObjectPtr>(idx++);
    LE3Transform& transform = (*object)->getTransform();
    LE3GetScriptSystem().pushUserType<LE3Transform>(&transform);
    return 1;
}

static const luaL_Reg LE3ObjectLib[] = {
    {"get_transform", bnd_LE3Object_getTransform},
    {NULL, NULL}
};

int le3::luaopen_LE3Object(lua_State* L) {
    luaL_newlib(L, LE3ObjectLib);
    return 1;
}