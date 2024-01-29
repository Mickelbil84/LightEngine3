#include "le3_script_bindings.h"
#include "le3_engine_systems.h"
using namespace le3;

static int bnd_LE3Scene_addShader(lua_State* L) {
    LE3Scene* scene = LE3GetScriptSystem().getUserType<LE3Scene>(1);
    std::string name = LE3GetScriptSystem().getString(2);
    std::string vertexSource = LE3GetScriptSystem().getString(3);
    std::string fragmentSource = LE3GetScriptSystem().getString(4);
    scene->addShaderFromFile(name, vertexSource, fragmentSource);
    return 0;
}
static int bnd_LE3Scene_getShader(lua_State* L) {
    LE3Scene* scene = LE3GetScriptSystem().getUserType<LE3Scene>(1);
    std::string name = LE3GetScriptSystem().getString(2);
    LE3ShaderPtr& shader = scene->getShader(name);
    LE3GetScriptSystem().pushUserType<LE3ShaderPtr>(&shader);
    return 1;
}

static int bnd_LE3Scene_addTexture(lua_State* L) {
    LE3Scene* scene = LE3GetScriptSystem().getUserType<LE3Scene>(1);
    std::string name = LE3GetScriptSystem().getString(2);
    std::string filename = LE3GetScriptSystem().getString(3);
    bool interpolate = LE3GetScriptSystem().getBool(4);
    scene->addTexture(name, filename, interpolate);
    return 0;
}

static int bnd_LE3Scene_getTexture(lua_State* L) {
    LE3Scene* scene = LE3GetScriptSystem().getUserType<LE3Scene>(1);
    std::string name = LE3GetScriptSystem().getString(2);
    LE3TexturePtr& texture = scene->getTexture(name);
    LE3GetScriptSystem().pushUserType<LE3TexturePtr>(&texture);
    return 1;
}

static int bnd_LE3Scene_addMaterial(lua_State* L) {
    LE3Scene* scene = LE3GetScriptSystem().getUserType<LE3Scene>(1);
    std::string name = LE3GetScriptSystem().getString(2);
    std::string shaderName = LE3GetScriptSystem().getString(3);
    scene->addMaterial(name, shaderName);
    return 0;
}

static int bnd_LE3Scene_getMaterial(lua_State* L) {
    LE3Scene* scene = LE3GetScriptSystem().getUserType<LE3Scene>(1);
    std::string name = LE3GetScriptSystem().getString(2);
    LE3MaterialPtr& material = scene->getMaterial(name);
    LE3GetScriptSystem().pushUserType<LE3MaterialPtr>(&material);
    return 1;
}

static int bnd_LE3Scene_addStaticMesh(lua_State* L) {
    LE3Scene* scene = LE3GetScriptSystem().getUserType<LE3Scene>(1);
    std::string name = LE3GetScriptSystem().getString(2);
    std::string filename = LE3GetScriptSystem().getString(3);
    scene->addStaticMesh(name, filename);
    return 0;
}

static int bnd_LE3Scene_getStaticMesh(lua_State* L) {
    LE3Scene* scene = LE3GetScriptSystem().getUserType<LE3Scene>(1);
    std::string name = LE3GetScriptSystem().getString(2);
    LE3StaticMeshPtr& mesh = scene->getStaticMesh(name);
    LE3GetScriptSystem().pushUserType<LE3StaticMeshPtr>(&mesh);
    return 1;
}


static const luaL_Reg LE3SceneLib[] = {
    {"add_shader", bnd_LE3Scene_addShader},
    {"get_shader", bnd_LE3Scene_getShader},

    {"add_texture", bnd_LE3Scene_addTexture},
    {"get_texture", bnd_LE3Scene_getTexture},

    {"add_material", bnd_LE3Scene_addMaterial},
    {"get_material", bnd_LE3Scene_getMaterial},

    {"add_static_mesh", bnd_LE3Scene_addStaticMesh},
    {"get_static_mesh", bnd_LE3Scene_getStaticMesh},

    {NULL, NULL}
};

int le3::luaopen_LE3Scene(lua_State* L) {
    luaL_newlib(L, LE3SceneLib);
    return 1;
}