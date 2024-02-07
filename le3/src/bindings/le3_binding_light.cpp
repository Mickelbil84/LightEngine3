#include "le3_script_bindings.h"
#include "le3_engine_systems.h"
using namespace le3;

FBIND_OBJECT_GETTER_VEC3(LE3Light, get_color, getColor)
FBIND_OBJECT_SETTER_VEC3(LE3Light, set_color, setColor)
FBIND_OBJECT_GETTER_NUMBER(LE3Light, get_intensity, getIntensity)
FBIND_OBJECT_SETTER_NUMBER(LE3Light, set_intensity, setIntensity)

// LBIND(LE3Light)
//     LADD(LE3Light, get_color)
//     LADD(LE3Light, set_color)
//     LADD(LE3Light, get_intensity)
//     LADD(LE3Light, set_intensity)
// LEND()

LIB(LE3Light, get_color, set_color, get_intensity, set_intensity)

// LOPEN(LE3Light)

// ----------------------------------------------------------------

static const luaL_Reg LE3AmbientLightLib[] = {
    {NULL, NULL}
};

int le3::luaopen_LE3AmbientLight(lua_State* L) {
    luaL_newlib(L, LE3AmbientLightLib);
    return 1;
}


// ----------------------------------------------------------------

static const luaL_Reg LE3DirectionalLightLib[] = {
    {NULL, NULL}
};

int le3::luaopen_LE3DirectionalLight(lua_State* L) {
    luaL_newlib(L, LE3DirectionalLightLib);
    return 1;
}

// ----------------------------------------------------------------

static int bnd_LE3PointLight_getAttnConst(lua_State* L) {
    int idx = 1;
    LE3PointLightPtr light = getUserType_LE3Object<LE3PointLight>(idx++);
    LE3GetScriptSystem().pushNumber(light->getAttnConst());
    return 1;
}
static int bnd_LE3PointLight_setAttnConst(lua_State* L) {
    int idx = 1;
    LE3PointLightPtr light = getUserType_LE3Object<LE3PointLight>(idx++);
    float value = LE3GetScriptSystem().getNumber(idx++);
    light->setAttnConst(value);
    return 0;
}
static int bnd_LE3PointLight_getAttnLinear(lua_State* L) {
    int idx = 1;
    LE3PointLightPtr light = getUserType_LE3Object<LE3PointLight>(idx++);
    LE3GetScriptSystem().pushNumber(light->getAttnLinear());
    return 1;
}
static int bnd_LE3PointLight_setAttnLinear(lua_State* L) {
    int idx = 1;
    LE3PointLightPtr light = getUserType_LE3Object<LE3PointLight>(idx++);
    float value = LE3GetScriptSystem().getNumber(idx++);
    light->setAttnLinear(value);
    return 0;
}
static int bnd_LE3PointLight_getAttnExp(lua_State* L) {
    int idx = 1;
    LE3PointLightPtr light = getUserType_LE3Object<LE3PointLight>(idx++);
    LE3GetScriptSystem().pushNumber(light->getAttnExp());
    return 1;
}
static int bnd_LE3PointLight_setAttnExp(lua_State* L) {
    int idx = 1;
    LE3PointLightPtr light = getUserType_LE3Object<LE3PointLight>(idx++);
    float value = LE3GetScriptSystem().getNumber(idx++);
    light->setAttnExp(value);
    return 0;
}

static const luaL_Reg LE3PointLightLib[] = {
    {"get_attn_const", bnd_LE3PointLight_getAttnConst},
    {"get_attn_linear", bnd_LE3PointLight_getAttnLinear},
    {"get_attn_exp", bnd_LE3PointLight_getAttnExp},
    {"set_attn_const", bnd_LE3PointLight_setAttnConst},
    {"set_attn_linear", bnd_LE3PointLight_setAttnLinear},
    {"set_attn_exp", bnd_LE3PointLight_setAttnExp},
    {NULL, NULL}
};

int le3::luaopen_LE3PointLight(lua_State* L) {
    luaL_newlib(L, LE3PointLightLib);
    return 1;
}

// ----------------------------------------------------------------

static int bnd_LE3SpotLight_getCutoff(lua_State* L) {
    int idx = 1;
    LE3SpotLightPtr light = getUserType_LE3Object<LE3SpotLight>(idx++);
    LE3GetScriptSystem().pushNumber(light->getCutoff());
    return 1;
}
static int bnd_LE3SpotLight_setCutoff(lua_State* L) {
    int idx = 1;
    LE3SpotLightPtr light = getUserType_LE3Object<LE3SpotLight>(idx++);
    float value = LE3GetScriptSystem().getNumber(idx++);
    light->setCutoff(value);
    return 0;
}
static int bnd_LE3SpotLight_getOuterCutoff(lua_State* L) {
    int idx = 1;
    LE3SpotLightPtr light = getUserType_LE3Object<LE3SpotLight>(idx++);
    LE3GetScriptSystem().pushNumber(light->getOuterCutoff());
    return 1;
}
static int bnd_LE3SpotLight_setOuterCutoff(lua_State* L) {
    int idx = 1;
    LE3SpotLightPtr light = getUserType_LE3Object<LE3SpotLight>(idx++);
    float value = LE3GetScriptSystem().getNumber(idx++);
    light->setOuterCutoff(value);
    return 0;
}

static const luaL_Reg LE3SpotLightLib[] = {
    {"get_cutoff", bnd_LE3SpotLight_getCutoff},
    {"get_outer_cutoff", bnd_LE3SpotLight_getOuterCutoff},
    {"set_cutoff", bnd_LE3SpotLight_setCutoff},
    {"set_outer_cutoff", bnd_LE3SpotLight_setOuterCutoff},
    {NULL, NULL}
};

int le3::luaopen_LE3SpotLight(lua_State* L) {
    luaL_newlib(L, LE3SpotLightLib);
    return 1;
}
