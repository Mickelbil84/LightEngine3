#include "le3_script_bindings.h"
#include "le3_engine_systems.h"
using namespace le3;

static int bnd_LE3Material_addShader(lua_State* L) {
    
    return 0;
}

static const luaL_Reg LE3MaterialLib[] = {
    {NULL, NULL}
};

int le3::luaopen_LE3Material(lua_State* L) {
    luaL_newlib(L, LE3MaterialLib);
    return 1;
}