#pragma once

#include "graphics/le3_model.h"
#include "graphics/le3_primitives.h"

namespace le3 {
    class LE3UIObject : public LE3StaticModel {
    public:
        LE3UIObject();
        LE3_TYPE_RETURN(LE3UIObject)

        virtual void draw(LE3ShaderPtr shaderOverride = LE3ShaderPtr());
    };
    using LE3UIObjectPtr = std::shared_ptr<LE3UIObject>;
}