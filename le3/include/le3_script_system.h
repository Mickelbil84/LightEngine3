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

        void moduleInit(std::string moduleName, const luaL_Reg* flist);

        void pushNil();
        void pushBool(bool b);
        void pushNumber(double d);
        void pushString(std::string str);
        template<typename T> void pushUserType(T* udata, std::string tname);

        bool getBool(int index);
        double getNumber(int index);
        std::string getString(int index);
        template<typename T> T* getUserType(int index, std::string tname);

    private:
        lua_State* L = nullptr;
    };

}