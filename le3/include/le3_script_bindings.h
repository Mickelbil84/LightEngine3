#pragma once

#include <lua.hpp>
#include <lauxlib.h>

#include "le3_scene.h"
#include "le3_material.h"

namespace le3 {
    int luaopen_LE3Scene(lua_State* L);
    int luaopen_LE3Material(lua_State* L);

    void bindLE3Types(lua_State* L); // Is called when initializing the script system
}