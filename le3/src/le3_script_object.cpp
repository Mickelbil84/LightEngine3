#include "le3_script_object.h"
#include "le3_engine_systems.h"
using namespace le3;

#include <fmt/core.h>


LE3ScriptObject::LE3ScriptObject(std::string classname, std::string ref) :
    LE3DrawableObject(nullptr), classname(classname), ref(ref) {
    LE3GetScriptSystem().doString(
        fmt::format("{}._refs[\"{}\"] = {}:new(); {}._refs[\"{}\"]._ref = \"{}\"",
            classname, ref, classname, 
            classname, ref, ref));
}

void LE3ScriptObject::update(float deltaTime)
{
    LE3DrawableObject::update(deltaTime);
    LE3GetScriptSystem().doString(
        fmt::format("{}._refs[\"{}\"]:update({})",
            classname, ref, deltaTime));
}

void LE3ScriptObject::draw(LE3ShaderPtr shaderOverride)
{
    LE3GetScriptSystem().doString(
        fmt::format("{}._refs[\"{}\"]:draw()",
            classname, ref));
}
