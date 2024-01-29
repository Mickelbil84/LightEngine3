#include "le3_script_bindings.h"
#include "le3_engine_systems.h"
using namespace le3;

#include <fmt/core.h>
using fmt::print;

static int bnd_LE3Scene_test(lua_State* L) {
    print("It works! (kinda..)\n");
    print("");
    return 0;
}

static const luaL_Reg LE3SceneLib[] = {
    {"test", bnd_LE3Scene_test},
    {NULL, NULL}
};

int le3::luaopen_LE3Scene(lua_State* L) {
    luaL_newlib(L, LE3SceneLib);
    return 1;
}