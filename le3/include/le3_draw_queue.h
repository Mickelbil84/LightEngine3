#pragma once

#include <map>
#include <vector>

#include "le3_drawable_object.h"

namespace le3 {
    // Data structure (including an iterator) for batched drawing objects
    // Objects using the same shader are batched together (with only one "use" call).
    struct LE3DrawQueue {
    public:
        LE3DrawQueue();

        void draw(LE3ShaderPtr shaderOverride = nullptr, bool shadowPhase = false);
        void addObject(std::weak_ptr<LE3DrawableObject> object);

    private:
        // For each priority:
        //      We have a mapping of shdaer key -> list of objects that use the shader
        //      TODO: check if shader was changed for material and if material was changed to object (and update)
        //      TODO: check for invalidated weak pointers
        std::map<
            LE3DrawPriority, 
            std::map<int, std::vector<std::weak_ptr<LE3DrawableObject>>>> m_drawQueue;
    };
}