#include "le3_script_bindings.h"
using namespace le3;

void le3::bindLE3Types(lua_State* L) {
    luaL_requiref(L, "LE3Scene", le3::luaopen_LE3Scene, 1);
    luaL_requiref(L, "LE3Shader", le3::luaopen_LE3Shader, 1);
    luaL_requiref(L, "LE3Texture", le3::luaopen_LE3Texture, 1);
    luaL_requiref(L, "LE3Material", le3::luaopen_LE3Material, 1);
    luaL_requiref(L, "LE3StaticMesh", le3::luaopen_LE3StaticMesh, 1);

    luaL_requiref(L, "LE3Object", le3::luaopen_LE3Object, 1);
    luaL_requiref(L, "LE3Transform", le3::luaopen_LE3Transform, 1);
    luaL_requiref(L, "LE3SceneRoot", le3::luaopen_LE3SceneRoot, 1);
    luaL_requiref(L, "LE3StaticModel", le3::luaopen_LE3StaticModel, 1);
    luaL_requiref(L, "LE3Input", le3::luaopen_LE3Input, 1);
    luaL_requiref(L, "LE3DrawableObject", le3::luaopen_LE3DrawableObject, 1);
    luaL_requiref(L, "LE3Camera", le3::luaopen_LE3Camera, 1);
    luaL_requiref(L, "LE3OrbitCamera", le3::luaopen_LE3OrbitCamera, 1);
    luaL_requiref(L, "LE3FreeCamera", le3::luaopen_LE3FreeCamera, 1);
    luaL_requiref(L, "LE3Box", le3::luaopen_LE3Box, 1);
}