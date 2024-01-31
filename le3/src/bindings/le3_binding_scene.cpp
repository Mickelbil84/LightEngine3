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

static int bnd_LE3Scene_addEmptyObject(lua_State* L) {
    int idx = 1;
    LE3Scene* scene = LE3GetScriptSystem().getUserType<LE3Scene>(idx++);
    std::string name = LE3GetScriptSystem().getString(idx++);
    scene->addEmptyObject(name);
    return 0;
}

static int bnd_LE3Scene_addCube(lua_State* L) {
    int idx = 1;
    LE3Scene* scene = LE3GetScriptSystem().getUserType<LE3Scene>(idx++);
    std::string name = LE3GetScriptSystem().getString(idx++);
    std::string materialName = LE3GetScriptSystem().getString(idx++);
    scene->addCube(name, materialName);
    return 0;
}

static int bnd_LE3Scene_addStaticModel(lua_State* L) {
    int idx = 1;
    LE3Scene* scene = LE3GetScriptSystem().getUserType<LE3Scene>(idx++);
    std::string name = LE3GetScriptSystem().getString(idx++);
    std::string meshName = LE3GetScriptSystem().getString(idx++);
    std::string materialName = LE3GetScriptSystem().getString(idx++);
    scene->addStaticModel(name, meshName, materialName);
    return 0;
}

static int bnd_LE3Scene_addFreeCamera(lua_State* L) {
    int idx = 1;
    LE3Scene* scene = LE3GetScriptSystem().getUserType<LE3Scene>(idx++);
    std::string name = LE3GetScriptSystem().getString(idx++);
    scene->addFreeCamera(name);
    return 0;
}

static int bnd_LE3Scene_addOrbitCamera(lua_State* L) {
    int idx = 1;
    LE3Scene* scene = LE3GetScriptSystem().getUserType<LE3Scene>(idx++);
    std::string name = LE3GetScriptSystem().getString(idx++);
    scene->addOrbitCamera(name);
    return 0;
}

static int bnd_LE3Scene_setMainCamera(lua_State* L) {
    int idx = 1;
    LE3Scene* scene = LE3GetScriptSystem().getUserType<LE3Scene>(idx++);
    std::string camera = LE3GetScriptSystem().getString(idx++);
    scene->setMainCamera(camera);
    return 0;
}

static int bnd_LE3Scene_reparent(lua_State* L) {
    int idx = 1;
    LE3Scene* scene = LE3GetScriptSystem().getUserType<LE3Scene>(idx++);
    std::string child = LE3GetScriptSystem().getString(idx++);
    std::string parent = LE3GetScriptSystem().getString(idx++);
    scene->getObject(child)->reparent(scene->getObject(parent));
    return 0;
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

    {"add_empty_object", bnd_LE3Scene_addEmptyObject},
    {"add_cube", bnd_LE3Scene_addCube},
    {"add_static_model", bnd_LE3Scene_addStaticModel},

    {"add_free_camera", bnd_LE3Scene_addFreeCamera},
    {"add_orbit_camera", bnd_LE3Scene_addOrbitCamera},
    {"set_main_camera", bnd_LE3Scene_setMainCamera},

    {"reparent", bnd_LE3Scene_reparent},

    {NULL, NULL}
};

int le3::luaopen_LE3Scene(lua_State* L) {
    luaL_newlib(L, LE3SceneLib);
    return 1;
}