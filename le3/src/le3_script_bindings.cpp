#include "le3_script_bindings.h"
using namespace le3;

void le3::bindLE3Types(lua_State* L) {
    luaL_requiref(L, "LE3Scene", le3::luaopen_LE3Scene, 1);
    luaL_requiref(L, "LE3Shader", le3::luaopen_LE3Shader, 1);
    luaL_requiref(L, "LE3Texture", le3::luaopen_LE3Texture, 1);
    luaL_requiref(L, "LE3Material", le3::luaopen_LE3Material, 1);
    luaL_requiref(L, "LE3StaticMesh", le3::luaopen_LE3StaticMesh, 1);

    luaL_requiref(L, "LE3Object", le3::luaopen_LE3Object, 1);
}