#include "le3_script_bindings.h"
#include "le3_engine_systems.h"
using namespace le3;

static int bnd_LE3Light_getColor(lua_State* L) {
    int idx = 1;
    LE3LightPtr light = getUserType_LE3Object<LE3Light>(idx++);
    glm::vec3 color = light->getColor();
    LE3GetScriptSystem().pushNumber(color.x);
    LE3GetScriptSystem().pushNumber(color.y);
    LE3GetScriptSystem().pushNumber(color.z);
    return 3;
}
static int bnd_LE3Light_setColor(lua_State* L) {
    int idx = 1;
    LE3LightPtr light = getUserType_LE3Object<LE3Light>(idx++);
    float x = LE3GetScriptSystem().getNumber(idx++);
    float y = LE3GetScriptSystem().getNumber(idx++);
    float z = LE3GetScriptSystem().getNumber(idx++);
    glm::vec3 color(x, y, z);
    light->setColor(color);
    return 0;
}
static int bnd_LE3Light_getIntensity(lua_State* L) {
    int idx = 1;
    LE3LightPtr light = getUserType_LE3Object<LE3Light>(idx++);
    LE3GetScriptSystem().pushNumber(light->getIntensity());
    return 1;
}
static int bnd_LE3Light_setIntensity(lua_State* L) {
    int idx = 1;
    LE3LightPtr light = getUserType_LE3Object<LE3Light>(idx++);
    float value = LE3GetScriptSystem().getNumber(idx++);
    light->setIntensity(value);
    return 0;
}

static const luaL_Reg LE3LightLib[] = {
    {"get_color", bnd_LE3Light_getColor},
    {"set_color", bnd_LE3Light_setColor},
    {"get_intensity", bnd_LE3Light_getIntensity},
    {"set_intensity", bnd_LE3Light_setIntensity},
    {NULL, NULL}
};

int le3::luaopen_LE3Light(lua_State* L) {
    luaL_newlib(L, LE3LightLib);
    return 1;
}

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
