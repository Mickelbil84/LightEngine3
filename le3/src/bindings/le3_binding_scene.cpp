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

static int bnd_LE3Scene_addBox(lua_State* L) {
    int idx = 1;
    LE3Scene* scene = LE3GetScriptSystem().getUserType<LE3Scene>(idx++);
    std::string name = LE3GetScriptSystem().getString(idx++);
    std::string materialName = LE3GetScriptSystem().getString(idx++);
    float x0 = LE3GetScriptSystem().getNumber(idx++);
    float y0 = LE3GetScriptSystem().getNumber(idx++);
    float z0 = LE3GetScriptSystem().getNumber(idx++);
    float width = LE3GetScriptSystem().getNumber(idx++);
    float height = LE3GetScriptSystem().getNumber(idx++);
    float depth = LE3GetScriptSystem().getNumber(idx++);
    glm::vec3 position(x0, y0, z0), extent(width, height, depth);
    scene->addBox(name, materialName, position, extent);
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

static int bnd_LE3Scene_addAmbientLight(lua_State* L) {
    int idx = 1;
    LE3Scene* scene = LE3GetScriptSystem().getUserType<LE3Scene>(idx++);
    std::string name = LE3GetScriptSystem().getString(idx++);
    scene->addAmbientLight(name);
    return 0;
}
static int bnd_LE3Scene_addDirectionalLight(lua_State* L) {
    int idx = 1;
    LE3Scene* scene = LE3GetScriptSystem().getUserType<LE3Scene>(idx++);
    std::string name = LE3GetScriptSystem().getString(idx++);
    scene->addDirectionalLight(name);
    return 0;
}
static int bnd_LE3Scene_addPointLight(lua_State* L) {
    int idx = 1;
    LE3Scene* scene = LE3GetScriptSystem().getUserType<LE3Scene>(idx++);
    std::string name = LE3GetScriptSystem().getString(idx++);
    scene->addPointLight(name);
    return 0;
}
static int bnd_LE3Scene_addSpotLight(lua_State* L) {
    int idx = 1;
    LE3Scene* scene = LE3GetScriptSystem().getUserType<LE3Scene>(idx++);
    std::string name = LE3GetScriptSystem().getString(idx++);
    scene->addSpotLight(name);
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

static int bnd_LE3Scene_getObject(lua_State* L) {
    int idx = 1;
    LE3Scene* scene = LE3GetScriptSystem().getUserType<LE3Scene>(idx++);
    std::string name = LE3GetScriptSystem().getString(idx++);
    LE3ObjectPtr& object = scene->getObject(name);
    LE3GetScriptSystem().pushUserType<LE3ObjectPtr>(&object);
    return 1;
}

static int bnd_LE3Scene_getBackgroundColor(lua_State* L) {
    int idx = 1;
    LE3Scene* scene = LE3GetScriptSystem().getUserType<LE3Scene>(idx++);
    glm::vec3 color = scene->getBackgroundColor();
    LE3GetScriptSystem().pushNumber(color.x);
    LE3GetScriptSystem().pushNumber(color.y);
    LE3GetScriptSystem().pushNumber(color.z);
    return 3;
}

static int bnd_LE3Scene_setBackgroundColor(lua_State* L) {
    int idx = 1;
    LE3Scene* scene = LE3GetScriptSystem().getUserType<LE3Scene>(idx++);
    float r = LE3GetScriptSystem().getNumber(idx++);
    float g = LE3GetScriptSystem().getNumber(idx++);
    float b = LE3GetScriptSystem().getNumber(idx++);
    scene->setBackgroundColor(glm::vec3(r, g, b));
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
    {"add_box", bnd_LE3Scene_addBox},
    {"add_static_model", bnd_LE3Scene_addStaticModel},

    {"add_free_camera", bnd_LE3Scene_addFreeCamera},
    {"add_orbit_camera", bnd_LE3Scene_addOrbitCamera},
    {"set_main_camera", bnd_LE3Scene_setMainCamera},

    {"add_ambient_light", bnd_LE3Scene_addAmbientLight},
    {"add_directional_light", bnd_LE3Scene_addDirectionalLight},
    {"add_point_light", bnd_LE3Scene_addPointLight},
    {"add_spot_light", bnd_LE3Scene_addSpotLight},

    {"reparent", bnd_LE3Scene_reparent},

    {"get_object", bnd_LE3Scene_getObject},

    {"get_background_color", bnd_LE3Scene_getBackgroundColor},
    {"set_background_color", bnd_LE3Scene_setBackgroundColor},

    {NULL, NULL}
};

int le3::luaopen_LE3Scene(lua_State* L) {
    luaL_newlib(L, LE3SceneLib);
    return 1;
}