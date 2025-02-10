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
            LE3GetScriptSystem().getGlobal("LE3EngineConfig");
            for (auto k : keys) {
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

        template<> static int getValue<int>() {
            return (int)LE3GetScriptSystem().getNumber(-1);
        }
        template<> static float getValue<float>() {
            return (float)LE3GetScriptSystem().getNumber(-1);
        }
        template<> static double getValue<double>() {
            return LE3GetScriptSystem().getNumber(-1);
        }
        // template<> static bool getValue<bool>() {
        //     return LE3GetScriptSystem().getBool(-1);
        // } // Commented out since Ubuntu gcc apparently does not like that
        template<> static std::string getValue<std::string>() {
            return LE3GetScriptSystem().getString(-1);
        }
    };
}