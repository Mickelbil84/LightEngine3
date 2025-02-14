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
            /////////////////////////////////////
            // keys = key.split('.') // python
            std::vector<std::string> keys;
            std::stringstream ss(key);
            std::string token;
            while (std::getline(ss, token, '.')) {
                keys.push_back(token);
            }
            /////////////////////////////////////
            LE3GetScriptSystem().getGlobal(keys[0]);
            bool first = true;
            for (auto k : keys) {
                _testnil(key);
                if (first) {first = false; continue; }
                LE3GetScriptSystem().getField(k);
            }
            _testnil(key);
            T res = getValue<T>();
            LE3GetScriptSystem().pop(keys.size());
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

    private:
        template<typename T> static T getValue() {
            return T();
        }

        static void _testnil(std::string key) {
            if (LE3GetScriptSystem().isNil()) { throw LE3ConfigKeyNotFound(fmt::format("Config key [{}] not found", key)); }
        }
    };

    template<> int LE3EngineConfig::getValue<int>();
    template<> float LE3EngineConfig::getValue<float>();
    template<> double LE3EngineConfig::getValue<double>();
    template<> bool LE3EngineConfig::getValue<bool>();
    template<> std::string LE3EngineConfig::getValue<std::string>();
    template<> std::vector<std::string> LE3EngineConfig::getValue<std::vector<std::string>>();

    #define LE3GetConfig LE3EngineConfig::get
}