#pragma once

#include "scripting/le3_script_object.h"

namespace le3 {
    const std::string LE3_PLAYERSTART_OBJECT_NAME = "__playerStart";
    const std::string LE3_PLAYERSTART_DEFAULT_CLASS = "FreeCamPlayer";

    class LE3PlayerStart : public LE3ScriptObject {
        LE3PlayerStart(std::string classname = LE3_PLAYERSTART_DEFAULT_CLASS);
        LE3_TYPE_RETURN(LE3PlayerStart)
    };
}