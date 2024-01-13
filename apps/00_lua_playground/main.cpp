#include <memory>
#include <string>
#include <iostream>

#include <fmt/core.h>
using fmt::format, fmt::print;

#include <lua.hpp>
#include <lauxlib.h>
#include <lualib.h>

static void stackDump (lua_State *L) {
    int i;
    int top = lua_gettop(L);  /* depth of the stack */
    for (i = 1; i <= top; i++) {  /* repeat for each level */
        int t = lua_type(L, i);
        switch (t) {
            case LUA_TSTRING: {  /* strings */
                printf("'%s'", lua_tostring(L, i));
                break;
            }
            case LUA_TBOOLEAN: {  /* Booleans */
                printf(lua_toboolean(L, i) ? "true" : "false");
                break; 
            }
            case LUA_TNUMBER: {  /* numbers */
                printf("%g", lua_tonumber(L, i));
                break;
            }
            default: {  /* other values */
                printf("%s", lua_typename(L, t));
                break; 
            }
        }
        printf("  ");  /* put a separator */
    }
    printf("\n");  /* end the listing */
}


int main() {
    lua_State* L = luaL_newstate();
    luaL_openlibs(L);

    lua_pushnumber(L, 3.5); // [3.5]
    lua_pushstring(L, "hello"); // [3.5, "hello"]
    lua_pushnil(L); // [3.5, "hello", nil]
    lua_rotate(L, 1, -1); // [3.5, nil, "hello"] or ["hello", nil, 3.5]
    lua_pushvalue(L, -2); // [3.5, nil, "hello", nil] or ["hello", nil, 3.5, nil]
    lua_remove(L, 1); // [3.5, "hello", nil] or [nil, 3.5, nil]
    lua_insert(L, -2); // [3.5, nil, "hello"] or [nil, nil, 3.5]

    // left is arrays starting with 0, right is with 1
    stackDump(L);

    lua_close(L);
    return 0;
}