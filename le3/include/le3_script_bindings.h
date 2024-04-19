#pragma once

#if __has_include("lua.hpp")
    #include <lua.hpp>
    #include <lauxlib.h>
#elif __has_include("lua5.4/lua.hpp")
    #include <lua5.4/lua.hpp>
    #include <lua5.4/lauxlib.h>
#else
    #include <lua/lua.hpp>
    #include <lua/lauxlib.h>
#endif

#include "le3_input.h"
#include "le3_light.h"
#include "le3_scene.h"
#include "le3_shader.h"
#include "le3_texture.h"
#include "le3_material.h"

#include "le3_model.h"
#include "le3_camera.h"
#include "le3_object.h"
#include "le3_transform.h"
#include "le3_scene_root.h"
#include "le3_script_object.h"
#include "le3_drawable_object.h"

#include "le3_engine_systems.h"


namespace le3 {

    /*
    * Specific for LE3Object hirerachy: in Lua, the lightuserdata will always point to
    * the corresponding LE3ObjectPtr object in the scene. But then we want to downcast it.
    * Hence this method does exactly that: gets an Object pointer and then dynamically casts it downwards *safely*.
    */
    template<typename T>
    std::shared_ptr<T> getUserType_LE3Object(int idx) {
        LE3ObjectPtr* object = LE3GetScriptSystem().getUserType<LE3ObjectPtr>(idx++);
        return std::dynamic_pointer_cast<T>(*object);
    }

    /////////////////////
    // Binding macros
    /////////////////////

    // Pop from Lua stack. All macros create a new variable name. We assume that `int idx = 1` was initialized.
    #define GET_BOOL(varname) bool varname = LE3GetScriptSystem().getBool(idx++);
    #define GET_NUMBER(varname) double varname = LE3GetScriptSystem().getNumber(idx++);
    #define GET_INT(varname) int varname = (int)LE3GetScriptSystem().getNumber(idx++);
    #define GET_STRING(varname) std::string varname = LE3GetScriptSystem().getString(idx++);
    #define GET_UDATA(varname, type) type* varname = (type*)(LE3GetScriptSystem().getUserType<type>(idx++));
    #define GET_UDATA_OBJECT(varname, type) std::shared_ptr<type> varname = le3::getUserType_LE3Object<type>(idx++);
    #define GET_VEC3(varname) GET_NUMBER(x) GET_NUMBER(y) GET_NUMBER(z) glm::vec3 varname(x, y, z);
    #define GET_VEC3_(varname) GET_NUMBER(varname##x) GET_NUMBER(varname##y) GET_NUMBER(varname##z) glm::vec3 varname(varname##x, varname##y, varname##z);
    #define GET_VEC4(varname) GET_NUMBER(x) GET_NUMBER(y) GET_NUMBER(z) GET_NUMBER(w) glm::vec4 varname(x, y, z, w);
    #define GET_QUAT(varname) GET_NUMBER(w) GET_NUMBER(x) GET_NUMBER(y) GET_NUMBER(z)  glm::quat varname(w, x, y, z);

    // Push to Lua stack
    #define PUSH_NIL() LE3GetScriptSystem().pushNil(); rcount++;
    #define PUSH_BOOL(b) LE3GetScriptSystem().pushBool((b)); rcount++;
    #define PUSH_NUMBER(n) LE3GetScriptSystem().pushNumber((n)); rcount++;
    #define PUSH_STRING(s) LE3GetScriptSystem().pushString((s)); rcount++;
    #define PUSH_UDATA(udata, type) LE3GetScriptSystem().pushUserType<type>(udata); rcount++;
    #define PUSH_VEC3(v) PUSH_NUMBER((v).x) PUSH_NUMBER((v).y) PUSH_NUMBER((v).z)
    #define PUSH_VEC4(v) PUSH_NUMBER((v).x) PUSH_NUMBER((v).y) PUSH_NUMBER((v).z) PUSH_NUMBER((v).w)
    #define PUSH_QUAT(v) PUSH_NUMBER((v).w) PUSH_NUMBER((v).x) PUSH_NUMBER((v).y) PUSH_NUMBER((v).z) 

    // Add globals
    #define SET_GLOBAL_NUMBER(L, name, val) lua_pushnumber(L, val); lua_setglobal(L, name);

    // Easier binding syntax
    #define FNAME(type, foo) type##_##foo
    #define FBIND(type, foo) static int FNAME(type, foo)(lua_State* L) { int idx = 1, rcount = 0, tmpidx;
    #define FEND() return rcount; }
    #define LBIND(type) static const luaL_Reg type##_lib[] = {
    #define LADD(type, foo) {#foo, FNAME(type, foo)},
    #define LEND() {NULL, NULL}};
    #define LOPEN_DECLARE(type) int luaopen_##type(lua_State* L)
    #define LOPEN(type) namespace le3 {LOPEN_DECLARE(type){luaL_newlib(L, type##_lib); return 1;}}
    // #define LOPEN_EMPTY(type) LBIND(type) LEND() LOPEN(type)
    #define REGISTER(type) luaL_requiref(L, #type, luaopen_##type, 1);

    // Even easier lib binding code, thanks to https://www.scs.stanford.edu/~dm/blog/va-opt.html
    #define PARENS ()
    #define EXPAND(...) EXPAND4(EXPAND4(EXPAND4(EXPAND4(__VA_ARGS__))))
    #define EXPAND4(...) EXPAND3(EXPAND3(EXPAND3(EXPAND3(__VA_ARGS__))))
    #define EXPAND3(...) EXPAND2(EXPAND2(EXPAND2(EXPAND2(__VA_ARGS__))))
    #define EXPAND2(...) EXPAND1(EXPAND1(EXPAND1(EXPAND1(__VA_ARGS__))))
    #define EXPAND1(...) __VA_ARGS__
    #define FOR_EACH_TYPE(macro, type, ...)                                    \
    __VA_OPT__(EXPAND(FOR_EACH_TYPE_HELPER(macro, type, __VA_ARGS__)))
    #define FOR_EACH_TYPE_HELPER(macro, type, a1, ...)                         \
    macro(type, a1)                                                     \
    __VA_OPT__(FOR_EACH_TYPE_AGAIN PARENS (macro, type, __VA_ARGS__))
    #define FOR_EACH_TYPE_AGAIN() FOR_EACH_TYPE_HELPER

    #define LIB(type, ...) LBIND(type) FOR_EACH_TYPE(LADD, type, __VA_ARGS__) LEND() LOPEN(type)

    // Getters and setters auto implementation
    #define FBIND_GETTER_RAW(type, foo, getter, push, fself) FBIND(type, foo) fself(self, type) push((self->getter)()) FEND()
    #define FBIND_SETTER_RAW(type, foo, setter, get, fself) FBIND(type, foo) fself(self, type) get(val) (self->setter)(val); FEND()
    #define FBIND_SETTER_CAST_RAW(type, foo, setter, get, fself, cast) FBIND(type, foo) fself(self, type) get(val) (self->setter)((cast)val); FEND()
    
    #define FBIND_OBJECT_GETTER(type, foo, getter, push) FBIND_GETTER_RAW(type, foo, getter, push, GET_UDATA_OBJECT)
    #define FBIND_OBJECT_SETTER(type, foo, setter, get) FBIND_SETTER_RAW(type, foo, setter, get, GET_UDATA_OBJECT)
    
    #define FBIND_OBJECT_GETTER_NUMBER(type, foo, getter) FBIND_OBJECT_GETTER(type, foo, getter, PUSH_NUMBER)
    #define FBIND_OBJECT_SETTER_NUMBER(type, foo, setter) FBIND_OBJECT_SETTER(type, foo, setter, GET_NUMBER)
    #define FBIND_GETTER_NUMBER(type, foo, getter) FBIND_GETTER_RAW(type, foo, getter, PUSH_NUMBER, GET_UDATA)
    #define FBIND_SETTER_NUMBER(type, foo, setter) FBIND_SETTER_RAW(type, foo, setter, GET_NUMBER, GET_UDATA)
    
    #define FBIND_OBJECT_SETTER_INT(type, foo, setter) FBIND_OBJECT_SETTER(type, foo, setter, GET_INT)
    #define FBIND_OBJECT_SETTER_ENUM(type, foo, setter, enumtype) FBIND_SETTER_CAST_RAW(type, foo, setter, GET_INT, GET_UDATA_OBJECT, enumtype)

    #define FBIND_OBJECT_GETTER_BOOL(type, foo, getter) FBIND_OBJECT_GETTER(type, foo, getter, PUSH_BOOL)
    #define FBIND_OBJECT_SETTER_BOOL(type, foo, setter) FBIND_OBJECT_SETTER(type, foo, setter, GET_BOOL)
    #define FBIND_GETTER_BOOL(type, foo, getter) FBIND_GETTER_RAW(type, foo, getter, PUSH_BOOL, GET_UDATA)
    #define FBIND_SETTER_BOOL(type, foo, setter) FBIND_SETTER_RAW(type, foo, setter, GET_BOOL, GET_UDATA)
    
    #define FBIND_OBJECT_GETTER_STRING(type, foo, getter) FBIND_OBJECT_GETTER(type, foo, getter, PUSH_STRING)
    #define FBIND_OBJECT_SETTER_STRING(type, foo, setter) FBIND_OBJECT_SETTER(type, foo, setter, GET_STRING)
    #define FBIND_GETTER_STRING(type, foo, getter) FBIND_GETTER_RAW(type, foo, getter, PUSH_STRING, GET_UDATA)
    #define FBIND_SETTER_STRING(type, foo, setter) FBIND_SETTER_RAW(type, foo, setter, GET_STRING, GET_UDATA)
    
    #define FBIND_OBJECT_GETTER_VEC3(type, foo, getter) FBIND_OBJECT_GETTER(type, foo, getter, PUSH_VEC3)
    #define FBIND_OBJECT_SETTER_VEC3(type, foo, setter) FBIND_OBJECT_SETTER(type, foo, setter, GET_VEC3)
    #define FBIND_GETTER_VEC3(type, foo, getter) FBIND_GETTER_RAW(type, foo, getter, PUSH_VEC3, GET_UDATA)
    #define FBIND_SETTER_VEC3(type, foo, setter) FBIND_SETTER_RAW(type, foo, setter, GET_VEC3, GET_UDATA)

    #define FBIND_OBJECT_GETTER_VEC4(type, foo, getter) FBIND_OBJECT_GETTER(type, foo, getter, PUSH_VEC4)
    #define FBIND_OBJECT_SETTER_VEC4(type, foo, setter) FBIND_OBJECT_SETTER(type, foo, setter, GET_VEC4)
    #define FBIND_GETTER_VEC4(type, foo, getter) FBIND_GETTER_RAW(type, foo, getter, PUSH_VEC4, GET_UDATA)
    #define FBIND_SETTER_VEC4(type, foo, setter) FBIND_SETTER_RAW(type, foo, setter, GET_VEC4, GET_UDATA)

    #define FBIND_OBJECT_GETTER_QUAT(type, foo, getter) FBIND_OBJECT_GETTER(type, foo, getter, PUSH_QUAT)
    #define FBIND_OBJECT_SETTER_QUAT(type, foo, setter) FBIND_OBJECT_SETTER(type, foo, setter, GET_QUAT)
    #define FBIND_GETTER_QUAT(type, foo, getter) FBIND_GETTER_RAW(type, foo, getter, PUSH_QUAT, GET_UDATA)
    #define FBIND_SETTER_QUAT(type, foo, setter) FBIND_SETTER_RAW(type, foo, setter, GET_QUAT, GET_UDATA)
    

    /////////////////////
    /////////////////////

    LOPEN_DECLARE(LE3EngineConfig);
    LOPEN_DECLARE(LE3AssetManager);
    LOPEN_DECLARE(LE3VisualDebug);

    LOPEN_DECLARE(LE3Scene);
    LOPEN_DECLARE(LE3Shader);
    LOPEN_DECLARE(LE3Texture);
    LOPEN_DECLARE(LE3Material);
    LOPEN_DECLARE(LE3StaticMesh);
    LOPEN_DECLARE(LE3SkeletalMesh);

    LOPEN_DECLARE(LE3Transform);
    LOPEN_DECLARE(LE3Object);
    LOPEN_DECLARE(LE3ScriptObject);
    LOPEN_DECLARE(LE3SceneRoot);
    LOPEN_DECLARE(LE3StaticModel);
    LOPEN_DECLARE(LE3SkeletalModel);
    LOPEN_DECLARE(LE3PointCloud);
    LOPEN_DECLARE(LE3Input);
    LOPEN_DECLARE(LE3DrawableObject);
    LOPEN_DECLARE(LE3Camera);
    LOPEN_DECLARE(LE3OrbitCamera);
    LOPEN_DECLARE(LE3FreeCamera);
    LOPEN_DECLARE(LE3Box);
    LOPEN_DECLARE(LE3Cylinder);
    LOPEN_DECLARE(LE3Cone);

    LOPEN_DECLARE(LE3Light);
    LOPEN_DECLARE(LE3AmbientLight);
    LOPEN_DECLARE(LE3DirectionalLight);
    LOPEN_DECLARE(LE3PointLight);
    LOPEN_DECLARE(LE3SpotLight);

    void bindLE3Types(lua_State* L); // Is called when initializing the script system
}