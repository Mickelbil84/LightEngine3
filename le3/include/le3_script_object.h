#pragma once

#include <string>
#include <memory>

#include "le3_drawable_object.h"

namespace le3 {
    class LE3ScriptObject : public LE3DrawableObject {
    public:
        LE3ScriptObject(std::string classname, std::string ref);

        virtual void update(float deltaTime);
        virtual void draw(LE3ShaderPtr shaderOverride);

    protected:
        std::string classname, ref;
    };
    using LE3ScriptObjectPtr = std::shared_ptr<LE3ScriptObject>;
}