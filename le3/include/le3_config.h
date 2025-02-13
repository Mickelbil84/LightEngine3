#pragma once

#include <string>
#include <vector>
#include <sstream>

#include "le3_engine_systems.h"

namespace le3 {

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
                if (first) {first = false; continue; }
                LE3GetScriptSystem().getField(k);
            }
            T res = getValue<T>();
            LE3GetScriptSystem().pop(keys.size());
            return res;
        }
    private:
        template<typename T> static T getValue() {
            return T();
        }
    };

    template<> int LE3EngineConfig::getValue<int>();
    template<> float LE3EngineConfig::getValue<float>();
    template<> double LE3EngineConfig::getValue<double>();
    template<> bool LE3EngineConfig::getValue<bool>();
    template<> std::string LE3EngineConfig::getValue<std::string>();
}