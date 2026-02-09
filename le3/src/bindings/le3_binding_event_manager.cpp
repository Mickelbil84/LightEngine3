#include "scripting/le3_script_bindings.h"
#include "core/le3_engine_systems.h"
using namespace le3;

// Holds the Lua data value during a synchronous notify->callback cycle
static int s_notifyDataRef = LUA_NOREF;

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
            int nargs = 0;
            if (s_notifyDataRef != LUA_NOREF) {
                lua_rawgeti(L, LUA_REGISTRYINDEX, s_notifyDataRef);
                nargs = 1;
            }
            if (lua_pcall(L, nargs, 0, 0) != 0) {
                lua_pop(L, 1);
            }
        });
    }
FEND()

FBIND(LE3EventManager, notify)
    GET_STRING(event)
    // Optionally capture a data argument (e.g. a Lua table)
    if (lua_gettop(L) >= idx && !lua_isnil(L, idx)) {
        lua_pushvalue(L, idx);
        s_notifyDataRef = luaL_ref(L, LUA_REGISTRYINDEX);
    }
    LE3GetEventManager().notify(event, nullptr);
    // Clean up after all callbacks have fired
    if (s_notifyDataRef != LUA_NOREF) {
        luaL_unref(L, LUA_REGISTRYINDEX, s_notifyDataRef);
        s_notifyDataRef = LUA_NOREF;
    }
FEND()

LIB(LE3EventManager,
    subscribe, notify
)
