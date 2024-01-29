#include "le3_script_bindings.h"
using namespace le3;

void le3::bindLE3Types(lua_State* L) {
    luaL_requiref(L, "LE3Scene", le3::luaopen_LE3Scene, 1);
}