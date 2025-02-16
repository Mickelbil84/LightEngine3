#include "le3_script_system.h"
#include "le3_engine_systems.h"
#include "le3_script_bindings.h"
using namespace le3;

LE3ScriptSystem::LE3ScriptSystem() {
    reset();
}
LE3ScriptSystem::~LE3ScriptSystem() {
    if (L) lua_close(L);
}
void LE3ScriptSystem::reset() {
    if (L) lua_close(L);
    L = luaL_newstate();
    luaL_openlibs(L);
    bindLE3Types(L);
}

void LE3ScriptSystem::doString(std::string code) {
    if (luaL_dostring(L, code.c_str()))
        luaL_error(L, "Error: %s", lua_tostring(L, -1));
}
void LE3ScriptSystem::doFile(std::string filename) {
    doString(LE3GetDatFileSystem().getFileContent(filename).toString());
}


bool LE3ScriptSystem::isNil() {
    return lua_isnil(L, -1);
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
void LE3ScriptSystem::pushStringArray(std::vector<std::string> arr) {
    lua_newtable(L);
    for (int i = 0; i < arr.size(); i++) {
        lua_pushstring(L, arr[i].c_str());
        lua_rawseti(L, -2, i + 1);
    }
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

void LE3ScriptSystem::setGlobal(std::string name) {
    lua_setglobal(L, name.c_str());

}
void LE3ScriptSystem::getGlobal(std::string name) {
    lua_getglobal(L, name.c_str());
}

void LE3ScriptSystem::getField(std::string field) {
    lua_getfield(L, -1, field.c_str());
}

void LE3ScriptSystem::getRawi(int index) {
    lua_rawgeti(L, -1, index);
}

void LE3ScriptSystem::callFunction(int numArgs, int numResults) {
    if (lua_pcall(L, numArgs, numResults, 0) != 0) {
        try { lua_error(L);}
        catch (...) {
        }
    }
}

void LE3ScriptSystem::callFunction(std::string name, int numResults) {
    getGlobal(name);
    callFunction(0, numResults);
}

void LE3ScriptSystem::pushValue(int index) {
    lua_pushvalue(L, index);
}

void LE3ScriptSystem::pop(int cnt) {
    lua_pop(L, cnt);
}

void LE3ScriptSystem::createEmptyTable(std::string name) {
    lua_newtable(L);
    lua_setglobal(L, name.c_str());
}