#pragma once

#include <string>

#include <lua.hpp>
#include <lauxlib.h>

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

        bool getBool(int index);
        double getNumber(int index);
        std::string getString(int index);
        void getGlobal(std::string name); // push global var to stack
        template<typename T> T* getUserType(int index) {
            void* udata = lua_touserdata(L, index);
            if (!udata) return nullptr;
            return reinterpret_cast<T*>(udata);
        }

        void callFunction(int numArgs, int numResults);

    private:
        lua_State* L = nullptr;
    };

}