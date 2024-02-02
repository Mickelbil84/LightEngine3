#pragma once

#include <lua.hpp>
#include <lauxlib.h>

#include "le3_scene.h"
#include "le3_shader.h"
#include "le3_texture.h"
#include "le3_material.h"

#include "le3_object.h"

namespace le3 {
    int luaopen_LE3Scene(lua_State* L);
    int luaopen_LE3Shader(lua_State* L);
    int luaopen_LE3Texture(lua_State* L);
    int luaopen_LE3Material(lua_State* L);
    int luaopen_LE3StaticMesh(lua_State* L);

    int luaopen_LE3Object(lua_State* L);

    void bindLE3Types(lua_State* L); // Is called when initializing the script system
}