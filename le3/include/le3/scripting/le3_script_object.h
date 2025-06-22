#pragma once

#include <string>
#include <memory>

#include "graphics/le3_drawable_object.h"

namespace le3 {
    class LE3ScriptObject : public LE3DrawableObject {
    public:
        LE3ScriptObject(std::string classname, std::string ref);
        LE3_TYPE_RETURN(LE3ScriptObject)

        virtual void update(float deltaTime);
        virtual void draw(LE3ShaderPtr shaderOverride);
        
        // Warning! These should be called only by the editor
        void updateInternals(std::string classname, std::string ref) {
            this->classname = classname; this->ref = ref;
        }
        std::string getClassname() const { return classname; }

    protected:
        std::string classname, ref;

        bool shouldSkip();
    };
    using LE3ScriptObjectPtr = std::shared_ptr<LE3ScriptObject>;
}