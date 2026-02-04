#include "scripting/le3_script_bindings.h"
#include "core/le3_engine_systems.h"
using namespace le3;

FBIND(LE3EventManager, subscribe)
    GET_STRING(event)
    GET_STRING(subscriberName)
    // 3rd argument is a Lua function
    luaL_checktype(L, idx, LUA_TFUNCTION);
    lua_pushvalue(L, idx);
    int callbackRef = luaL_ref(L, LUA_REGISTRYINDEX);

    LE3ObjectPtr subscriber = LE3GetActiveScene()->getObject(subscriberName);
    if (subscriber) {
        LE3GetEventManager().subscribe(event, subscriber, [callbackRef](void* data) {
            lua_State* L = LE3GetScriptSystem().getLuaState();
            lua_rawgeti(L, LUA_REGISTRYINDEX, callbackRef);
            if (lua_pcall(L, 0, 0, 0) != 0) {
                lua_pop(L, 1);
            }
        });
    }
FEND()

FBIND(LE3EventManager, notify)
    GET_STRING(event)
    LE3GetEventManager().notify(event, nullptr);
FEND()

LIB(LE3EventManager,
    subscribe, notify
)
