#include "le3_script_system.h"
#include "le3_engine_systems.h"
#include "le3_script_bindings.h"
using namespace le3;

LE3ScriptSystem::LE3ScriptSystem() {
    L = luaL_newstate();
    luaL_openlibs(L);
    bindLE3Types(L);
}
LE3ScriptSystem::~LE3ScriptSystem() {
    if (L) lua_close(L);
}

void LE3ScriptSystem::doString(std::string code) {
    if (luaL_dostring(L, code.c_str()))
        luaL_error(L, "Error: %s", lua_tostring(L, -1));
}
void LE3ScriptSystem::doFile(std::string filename) {
    doString(LE3GetDatFileSystem().getFileContent(filename).toString());
}

void LE3ScriptSystem::pushNil() {
    lua_pushnil(L);
}
void LE3ScriptSystem::pushBool(bool b) {
    lua_pushboolean(L, b);
}
void LE3ScriptSystem::pushNumber(double d) {
    lua_pushnumber(L, d);
}
void LE3ScriptSystem::pushString(std::string str) {
    lua_pushstring(L, str.c_str());
}

bool LE3ScriptSystem::getBool(int index) {
    return (bool)lua_toboolean(L, index);
}
double LE3ScriptSystem::getNumber(int index) {
    return lua_tonumber(L, index);
}
std::string LE3ScriptSystem::getString(int index) {
    return std::string(lua_tostring(L, index));
}

template<typename T> 
void LE3ScriptSystem::pushUserType(T* udata, std::string tname) {
    lua_pushlightuserdata(L, reinterpret_cast<void*>(udata));
}

template<typename T> 
T* LE3ScriptSystem::getUserType(int index, std::string tname) {
    void* udata = lua_touserdata(L, index);
    if (!udata) luaL_typeerror(L, index, tname.c_str());
    return reinterpret_cast<T*>(udata);
}

void LE3ScriptSystem::moduleInit(std::string moduleName, const luaL_Reg* flist) {
    // luaL_setfuncs(L, flist, 0);
    luaL_newlib(L, flist);
}