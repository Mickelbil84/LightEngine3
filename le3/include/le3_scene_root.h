#pragma once

#include "le3_object.h"

namespace le3 {
    class LE3SceneRoot : public LE3Object {
    public:
        LE3SceneRoot() : LE3Object() {}
        virtual void update(float deltaTime) { updateRecurse(deltaTime, shared_from_this()); }
        virtual void draw() { drawRecurse(shared_from_this()); }

    private:
        void updateRecurse(float deltaTime, LE3ObjectPtr object);
        void drawRecurse(LE3ObjectPtr object);
    };
    using LE3SceneRootPtr = std::shared_ptr<LE3SceneRoot>;
}