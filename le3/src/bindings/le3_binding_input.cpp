#include "le3_script_bindings.h"
#include "le3_engine_systems.h"
using namespace le3;

static const luaL_Reg LE3InputLib[] = {
    {NULL, NULL}
};

int le3::luaopen_LE3Input(lua_State* L) {
    luaL_newlib(L, LE3InputLib);
    return 1;
}