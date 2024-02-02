#include "le3_script_bindings.h"
#include "le3_engine_systems.h"
using namespace le3;

static const luaL_Reg LE3ObjectLib[] = {
    {NULL, NULL}
};

int le3::luaopen_LE3Object(lua_State* L) {
    luaL_newlib(L, LE3ObjectLib);
    return 1;
}