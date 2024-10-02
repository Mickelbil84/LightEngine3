#pragma once

#include "le3ed_component.h"

namespace le3 {
    class LE3EditorGUI : public LE3EditorComponent{
    public:
        LE3ED_COMPONENT_DEAFULT_CTOR(LE3EditorGUI)
        void init();
        void update(float deltaTime);
    };
}