#pragma once

#include <lua.hpp>
#include <lauxlib.h>

#include "le3_input.h"
#include "le3_scene.h"
#include "le3_shader.h"
#include "le3_texture.h"
#include "le3_material.h"

#include "le3_model.h"
#include "le3_camera.h"
#include "le3_object.h"
#include "le3_transform.h"
#include "le3_scene_root.h"
#include "le3_drawable_object.h"


namespace le3 {
    int luaopen_LE3Scene(lua_State* L);
    int luaopen_LE3Shader(lua_State* L);
    int luaopen_LE3Texture(lua_State* L);
    int luaopen_LE3Material(lua_State* L);
    int luaopen_LE3StaticMesh(lua_State* L);

    int luaopen_LE3Transform(lua_State* L);
    int luaopen_LE3Object(lua_State* L);
    int luaopen_LE3SceneRoot(lua_State* L);
    int luaopen_LE3StaticModel(lua_State* L);
    int luaopen_LE3Input(lua_State* L);
    int luaopen_LE3DrawableObject(lua_State* L);
    int luaopen_LE3Camera(lua_State* L);
    int luaopen_LE3OrbitCamera(lua_State* L);
    int luaopen_LE3FreeCamera(lua_State* L);

    void bindLE3Types(lua_State* L); // Is called when initializing the script system
}