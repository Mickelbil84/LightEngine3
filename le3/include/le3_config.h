#pragma once

#include <string>
#include <vector>
#include <sstream>

#include "le3_engine_systems.h"

namespace le3 {

    class LE3ConfigKeyNotFound : public std::runtime_error { public: LE3ConfigKeyNotFound(std::string msg) : std::runtime_error(msg) {} };

    class LE3EngineConfig {
    public:
        template<typename T> static T get(const std::string key) {
            LE3GetScriptSystem().getGlobal("get_config");
            LE3GetScriptSystem().pushString(key);
            LE3GetScriptSystem().callFunction(1, 1);
            _testnil(key, 1);
            T res = getValue<T>();
            LE3GetScriptSystem().pop(1);
            return res;
        }

        template<typename T> static T get(const std::string key, T dflt) {
            try {
                return get<T>(key);
            }
            catch (LE3ConfigKeyNotFound e) {
                return dflt;
            }
        }

        template<typename T> static void set(const std::string key, T value) {
            LE3GetScriptSystem().getGlobal("set_config");
            LE3GetScriptSystem().pushString(key);
            setValue<T>(value);
            LE3GetScriptSystem().callFunction(2, 0);
        }

    private:
        template<typename T> static T getValue() {
            return T();
        }

        template<typename T> static void setValue(T value) {
        }

        static void _testnil(std::string key, int popCnt ) {
            if (LE3GetScriptSystem().isNil()) { 
                //if (popCnt > 0) LE3GetScriptSystem().pop(popCnt);
                throw LE3ConfigKeyNotFound(fmt::format("Config key [{}] not found", key)); 
            }
        }
    };

    template<> int LE3EngineConfig::getValue<int>();
    template<> void LE3EngineConfig::setValue<int>(int value);

    template<> float LE3EngineConfig::getValue<float>();
    template<> void LE3EngineConfig::setValue<float>(float value);

    template<> double LE3EngineConfig::getValue<double>();
    template<> void LE3EngineConfig::setValue<double>(double value);
    
    template<> bool LE3EngineConfig::getValue<bool>();
    template<> void LE3EngineConfig::setValue<bool>(bool value);

    template<> std::string LE3EngineConfig::getValue<std::string>();
    template<> void LE3EngineConfig::setValue<std::string>(std::string value);

    template<> std::vector<std::string> LE3EngineConfig::getValue<std::vector<std::string>>();
    template<> void LE3EngineConfig::setValue<std::vector<std::string>>(std::vector<std::string> value);

    #define LE3GetConfig LE3EngineConfig::get
}