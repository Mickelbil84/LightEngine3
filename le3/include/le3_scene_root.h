#pragma once

#include "le3_object.h"

namespace le3 {
    class LE3SceneRoot : public LE3Object {
    public:
        LE3SceneRoot() : LE3Object() {}
        virtual void update(float deltaTime) { updateRecurse(deltaTime, shared_from_this()); }
        virtual void preUpdate() { preUpdateRecurse(shared_from_this()); }
        virtual void postUpdate() { postUpdateRecurse(shared_from_this()); }

    private:
        void updateRecurse(float deltaTime, LE3ObjectPtr object);
        void preUpdateRecurse(LE3ObjectPtr object);
        void postUpdateRecurse(LE3ObjectPtr object);
    };
    using LE3SceneRootPtr = std::shared_ptr<LE3SceneRoot>;
}