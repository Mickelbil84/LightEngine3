#include "le3_script_bindings.h"
#include "le3_engine_systems.h"
using namespace le3;

static int bnd_LE3Material_setDiffuseColor(lua_State* L) {
    int idx = 1;
    LE3MaterialPtr* material = LE3GetScriptSystem().getUserType<LE3MaterialPtr>(idx++);
    float r = LE3GetScriptSystem().getNumber(idx++);
    float g = LE3GetScriptSystem().getNumber(idx++);
    float b = LE3GetScriptSystem().getNumber(idx++);
    float a = LE3GetScriptSystem().getNumber(idx++);
    (*material)->diffuseColor = glm::vec4(r, g, b, a);
    return 0;
}

static int bnd_LE3Material_setDiffuseTexture(lua_State* L) {
    int idx = 1;
    LE3MaterialPtr* material = LE3GetScriptSystem().getUserType<LE3MaterialPtr>(idx++);
    LE3TexturePtr* texture = LE3GetScriptSystem().getUserType<LE3TexturePtr>(idx++);
    (*material)->diffuseTexture = *texture;
    (*material)->bUseDiffuseTexture = (texture != nullptr);
    return 0;
}

static int bnd_LE3Material_setSpecularColor(lua_State* L) {
    int idx = 1;
    LE3MaterialPtr* material = LE3GetScriptSystem().getUserType<LE3MaterialPtr>(idx++);
    float r = LE3GetScriptSystem().getNumber(idx++);
    float g = LE3GetScriptSystem().getNumber(idx++);
    float b = LE3GetScriptSystem().getNumber(idx++);
    float a = LE3GetScriptSystem().getNumber(idx++);
    (*material)->specularColor = glm::vec4(r, g, b, a);
    return 0;
}

static int bnd_LE3Material_setSpecularIntensity(lua_State* L) {
    int idx = 1;
    LE3MaterialPtr* material = LE3GetScriptSystem().getUserType<LE3MaterialPtr>(idx++);
    float val = LE3GetScriptSystem().getNumber(idx++);
    (*material)->specularIntensity = val;
    return 0;
}

static int bnd_LE3Material_setShininess(lua_State* L) {
    int idx = 1;
    LE3MaterialPtr* material = LE3GetScriptSystem().getUserType<LE3MaterialPtr>(idx++);
    float val = LE3GetScriptSystem().getNumber(idx++);
    (*material)->shininess = val;
    return 0;
}

static int bnd_LE3Material_setSpecularTexture(lua_State* L) {
    int idx = 1;
    LE3MaterialPtr* material = LE3GetScriptSystem().getUserType<LE3MaterialPtr>(idx++);
    LE3TexturePtr* texture = LE3GetScriptSystem().getUserType<LE3TexturePtr>(idx++);
    (*material)->specularTexture = *texture;
    (*material)->bUseSpecularTexture = (texture == nullptr);
    return 0;
}

static int bnd_LE3Material_setNormalTexture(lua_State* L) {
    int idx = 1;
    LE3MaterialPtr* material = LE3GetScriptSystem().getUserType<LE3MaterialPtr>(idx++);
    LE3TexturePtr* texture = LE3GetScriptSystem().getUserType<LE3TexturePtr>(idx++);
    (*material)->normalTexture = *texture;
    (*material)->bUseNormalTexture = (texture == nullptr);
    return 0;
}

static int bnd_LE3Material_setCubemap(lua_State* L) {
    int idx = 1;
    LE3MaterialPtr* material = LE3GetScriptSystem().getUserType<LE3MaterialPtr>(idx++);
    LE3TexturePtr* texture = LE3GetScriptSystem().getUserType<LE3TexturePtr>(idx++);
    (*material)->cubemap = *texture;
    return 0;
}

static int bnd_LE3Material_setReflectionIntensity(lua_State* L) {
    int idx = 1;
    LE3MaterialPtr* material = LE3GetScriptSystem().getUserType<LE3MaterialPtr>(idx++);
    float val = LE3GetScriptSystem().getNumber(idx++);
    (*material)->reflectionIntensity = val;
    return 0;
}

static int bnd_LE3Material_setTiling(lua_State* L) {
    int idx = 1;
    LE3MaterialPtr* material = LE3GetScriptSystem().getUserType<LE3MaterialPtr>(idx++);
    float x = LE3GetScriptSystem().getNumber(idx++);
    float y = LE3GetScriptSystem().getNumber(idx++);
    (*material)->tilingX = x;
    (*material)->tilingY = y;
    return 0;
}

static const luaL_Reg LE3MaterialLib[] = {
    {"set_diffuse_color", bnd_LE3Material_setDiffuseColor},
    {"set_diffuse_texture", bnd_LE3Material_setDiffuseTexture},
    {"set_specular_color", bnd_LE3Material_setSpecularColor},
    {"set_specular_intensity", bnd_LE3Material_setSpecularIntensity},
    {"set_shininess", bnd_LE3Material_setShininess},
    {"set_specular_texture", bnd_LE3Material_setSpecularTexture},
    {"set_normal_texture", bnd_LE3Material_setNormalTexture},
    {"set_cubemap", bnd_LE3Material_setCubemap},
    {"set_reflection_intensity", bnd_LE3Material_setReflectionIntensity},
    {"set_tiling", bnd_LE3Material_setTiling},
    {NULL, NULL}
};

int le3::luaopen_LE3Material(lua_State* L) {
    luaL_newlib(L, LE3MaterialLib);
    return 1;
}