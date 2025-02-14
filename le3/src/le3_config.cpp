#include "le3_config.h"
using namespace le3;

template<> int LE3EngineConfig::getValue<int>() {
    return (int)LE3GetScriptSystem().getNumber(-1);
}
template<> float LE3EngineConfig::getValue<float>() {
    return (float)LE3GetScriptSystem().getNumber(-1);
}
template<> double LE3EngineConfig::getValue<double>() {
    return LE3GetScriptSystem().getNumber(-1);
}
template<> bool LE3EngineConfig::getValue<bool>() {
    return LE3GetScriptSystem().getBool(-1);
}
template<> std::string LE3EngineConfig::getValue<std::string>() {
    return LE3GetScriptSystem().getString(-1);
}
template<> std::vector<std::string> LE3EngineConfig::getValue<std::vector<std::string>>() {
    std::vector<std::string> res;
    int idx = 1;
    do {
        LE3GetScriptSystem().getRawi(idx++);
        if (LE3GetScriptSystem().isNil()) break;
        res.push_back(LE3GetScriptSystem().getString(-1));
        LE3GetScriptSystem().pop(1);
    } while (true);
    return res;
}