#include "scripting/le3_script_object.h"
#include "core/le3_engine_systems.h"
using namespace le3;

#include <fmt/core.h>


LE3ScriptObject::LE3ScriptObject(std::string classname, std::string ref) :
    LE3DrawableObject(LE3MaterialPtr()), classname(classname), ref(ref) {
    if (LE3EngineSystems::instance().isEditModeEngine()) return;
    LE3GetScriptSystem().doString(
        fmt::format("{}._refs[\"{}\"] = {}:new(); {}._refs[\"{}\"]._ref = \"{}\"",
            classname, ref, classname, 
            classname, ref, ref));
}

void LE3ScriptObject::update(float deltaTime)
{
    LE3DrawableObject::update(deltaTime);
    if (LE3EngineSystems::instance().isEditModeEngine()) return;
    LE3GetScriptSystem().doString(
        fmt::format("{}._refs[\"{}\"]:update({})",
            classname, ref, deltaTime));
}

void LE3ScriptObject::draw(LE3ShaderPtr shaderOverride)
{
    if (LE3EngineSystems::instance().isEditModeEngine()) return;
    LE3GetScriptSystem().doString(
        fmt::format("{}._refs[\"{}\"]:draw()",
            classname, ref));
}
