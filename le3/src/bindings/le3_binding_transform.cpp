#include "le3_script_bindings.h"
#include "le3_engine_systems.h"
using namespace le3;

static int bnd_LE3Transform_getPosition(lua_State* L) {
    int idx = 1;
    LE3Transform* transform = LE3GetScriptSystem().getUserType<LE3Transform>(idx++);
    glm::vec3 position = transform->getPosition();
    LE3GetScriptSystem().pushNumber(position.x);
    LE3GetScriptSystem().pushNumber(position.y);
    LE3GetScriptSystem().pushNumber(position.z);
    return 3;
}
static int bnd_LE3Transform_getRotation(lua_State* L) {
    int idx = 1;
    LE3Transform* transform = LE3GetScriptSystem().getUserType<LE3Transform>(idx++);
    glm::quat rot = transform->getRotation();
    LE3GetScriptSystem().pushNumber(rot.w);
    LE3GetScriptSystem().pushNumber(rot.x);
    LE3GetScriptSystem().pushNumber(rot.y);
    LE3GetScriptSystem().pushNumber(rot.z);
    return 4;
}
static int bnd_LE3Transform_getScale(lua_State* L) {
    int idx = 1;
    LE3Transform* transform = LE3GetScriptSystem().getUserType<LE3Transform>(idx++);
    glm::vec3 scale = transform->getScale();
    LE3GetScriptSystem().pushNumber(scale.x);
    LE3GetScriptSystem().pushNumber(scale.y);
    LE3GetScriptSystem().pushNumber(scale.z);
    return 3;
}

static int bnd_LE3Transform_setPosition(lua_State* L) {
    int idx = 1;
    LE3Transform* transform = LE3GetScriptSystem().getUserType<LE3Transform>(idx++);
    float x = LE3GetScriptSystem().getNumber(idx++);
    float y = LE3GetScriptSystem().getNumber(idx++);
    float z = LE3GetScriptSystem().getNumber(idx++);
    glm::vec3 position(x, y, z);
    transform->setPosition(position);
    return 0;
}
static int bnd_LE3Transform_setRotation(lua_State* L) {
    int idx = 1;
    LE3Transform* transform = LE3GetScriptSystem().getUserType<LE3Transform>(idx++);
    float w = LE3GetScriptSystem().getNumber(idx++);
    float x = LE3GetScriptSystem().getNumber(idx++);
    float y = LE3GetScriptSystem().getNumber(idx++);
    float z = LE3GetScriptSystem().getNumber(idx++);
    glm::quat rot(w, x, y, z);
    transform->setRotation(rot);
    return 0;
}
static int bnd_LE3Transform_setScale(lua_State* L) {
    int idx = 1;
    LE3Transform* transform = LE3GetScriptSystem().getUserType<LE3Transform>(idx++);
    float x = LE3GetScriptSystem().getNumber(idx++);
    float y = LE3GetScriptSystem().getNumber(idx++);
    float z = LE3GetScriptSystem().getNumber(idx++);
    glm::vec3 scale(x, y, z);
    transform->setScale(scale);
    return 0;
}

static const luaL_Reg LE3TransformLib[] = {
    {"get_position", bnd_LE3Transform_getPosition},
    {"get_rotation", bnd_LE3Transform_getRotation},
    {"get_scale", bnd_LE3Transform_getScale},

    {"set_position", bnd_LE3Transform_setPosition},
    {"set_rotation", bnd_LE3Transform_setRotation},
    {"set_scale", bnd_LE3Transform_setScale},

    {NULL, NULL}
};

int le3::luaopen_LE3Transform(lua_State* L) {
    luaL_newlib(L, LE3TransformLib);
    return 1;
}