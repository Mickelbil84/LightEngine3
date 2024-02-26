#pragma once

#include <string>

#if __has_include("lua.hpp")
    #include <lua.hpp>
    #include <lauxlib.h>
#elif __has_include("lua5.4/lua.hpp")
    #include <lua5.4/lua.hpp>
    #include <lua5.4/lauxlib.h>
#else
    #include <lua/lua.hpp>
    #include <lua/lauxlib.h>
#endif

namespace le3 {
    class LE3ScriptSystem {
    public:
        LE3ScriptSystem();
        ~LE3ScriptSystem();

        void doString(std::string code);
        void doFile(std::string filename);
        
        void pushNil();
        void pushBool(bool b);
        void pushNumber(double d);
        void pushString(std::string str);
        template<typename T> void pushUserType(T* udata) {
            lua_pushlightuserdata(L, reinterpret_cast<void*>(udata));
        }

        void setGlobal(std::string name); // set recently pushed var on stack as global
        void getGlobal(std::string name); // push global var to stack
        void getField(std::string field); // push field from table (the table is on top of stack) to stack

        bool getBool(int index);
        double getNumber(int index);
        std::string getString(int index);
        template<typename T> T* getUserType(int index) {
            void* udata = lua_touserdata(L, index);
            if (!udata) return nullptr;
            return reinterpret_cast<T*>(udata);
        }

        void callFunction(int numArgs, int numResults);
        void pushValue(int index);

    private:
        lua_State* L = nullptr;
    };

}