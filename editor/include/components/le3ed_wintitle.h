#pragma once

#include "le3ed_component.h"
#include "le3ed_constants.h"

namespace le3 {
    class LE3EditorWindowTitle : public LE3EditorComponent{
    public:
        LE3ED_COMPONENT_DEAFULT_CTOR(LE3EditorWindowTitle)
        void init();
        void update(float deltaTime) {}

    private:
        void OnTitleUpdate();
    };
}