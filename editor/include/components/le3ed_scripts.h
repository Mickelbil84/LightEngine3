#pragma once

#include "le3ed_component.h"
#include "le3ed_constants.h"

namespace le3 {
    class LE3EditorScripts : public LE3EditorComponent{
    public:
        LE3ED_COMPONENT_DEAFULT_CTOR(LE3EditorScripts)
        void init();
        void update(float deltaTime);

    private:
    };
}