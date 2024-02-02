#include "le3_script_bindings.h"
#include "le3_engine_systems.h"
using namespace le3;

static const luaL_Reg LE3SceneRootLib[] = {
    {NULL, NULL}
};

int le3::luaopen_LE3SceneRoot(lua_State* L) {
    luaL_newlib(L, LE3SceneRootLib);
    return 1;
}