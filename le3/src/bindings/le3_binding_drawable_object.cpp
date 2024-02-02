#include "le3_script_bindings.h"
#include "le3_engine_systems.h"
using namespace le3;

static int bnd_LE3DrawableObject_getDrawPriority(lua_State* L) {
    int idx = 1;
    LE3DrawableObjectPtr* object = LE3GetScriptSystem().getUserType<LE3DrawableObjectPtr>(idx++);
    LE3GetScriptSystem().pushNumber((*object)->getDrawPriority());
    return 1;
}

static int bnd_LE3DrawableObject_setDrawPriority(lua_State* L) {
    int idx = 1;
    LE3DrawableObjectPtr* object = LE3GetScriptSystem().getUserType<LE3DrawableObjectPtr>(idx++);
    LE3DrawPriority priority = (LE3DrawPriority) (int)LE3GetScriptSystem().getNumber(idx++);
    (*object)->setDrawPriority(priority);
    return 0;
}

static int bnd_LE3DrawableObject_getMaterial(lua_State* L) {
    int idx = 1;
    LE3DrawableObjectPtr* object = LE3GetScriptSystem().getUserType<LE3DrawableObjectPtr>(idx++);
    LE3MaterialPtr& material = (*object)->getMaterial();
    LE3GetScriptSystem().pushUserType<LE3MaterialPtr>(&material);
    return 1;
}

static int bnd_LE3DrawableObject_setMaterial(lua_State* L) {
    int idx = 1;
    LE3DrawableObjectPtr* object = LE3GetScriptSystem().getUserType<LE3DrawableObjectPtr>(idx++);
    LE3MaterialPtr* material = LE3GetScriptSystem().getUserType<LE3MaterialPtr>(idx++);
    (*object)->setMaterial(*material);
    return 0;
}

static int bnd_LE3DrawableObject_getHidden(lua_State* L) {
    int idx = 1;
    LE3DrawableObjectPtr* object = LE3GetScriptSystem().getUserType<LE3DrawableObjectPtr>(idx++);
    LE3GetScriptSystem().pushBool((*object)->isHidden());
    return 1;
}

static int bnd_LE3DrawableObject_setHidden(lua_State* L) {
    int idx = 1;
    LE3DrawableObjectPtr* object = LE3GetScriptSystem().getUserType<LE3DrawableObjectPtr>(idx++);
    bool hidden = LE3GetScriptSystem().getBool(idx++);
    (*object)->setHidden(hidden);
    return 0;
}

static const luaL_Reg LE3DrawableObjectLib[] = {
    {"get_draw_priority", bnd_LE3DrawableObject_getDrawPriority},
    {"set_draw_priority", bnd_LE3DrawableObject_setDrawPriority},
    {"get_material", bnd_LE3DrawableObject_getMaterial},
    // {"set_material", bnd_LE3DrawableObject_setMaterial},
    {"get_hidden", bnd_LE3DrawableObject_getHidden},
    {"set_hidden", bnd_LE3DrawableObject_setHidden},
    {NULL, NULL}
};

void bnd_LE3DrawPriority(lua_State* L) {
    lua_pushnumber(L, 0);
    lua_setglobal(L, "DRAW_PRIORITY_LOW");
    lua_pushnumber(L, 1);
    lua_setglobal(L, "DRAW_PRIORITY_MEDIUM");
    lua_pushnumber(L, 2);
    lua_setglobal(L, "DRAW_PRIORITY_HIGH");
    lua_pushnumber(L, 3);
    lua_setglobal(L, "DRAW_PRIORITY_UI");
}

int le3::luaopen_LE3DrawableObject(lua_State* L) {
    luaL_newlib(L, LE3DrawableObjectLib);
    // bnd_LE3DrawPriority();
    return 1;
}