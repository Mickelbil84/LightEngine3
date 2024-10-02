#pragma once

#include "le3ed_component.h"

namespace le3 {

    class LE3EditorScenes : public LE3EditorComponent {
    public:
        LE3ED_COMPONENT_DEAFULT_CTOR(LE3EditorScenes)
        void init();
        void update(float deltaTime);
        void render();
    
    private:
        void initCameras();
        void initScenes();
        void initGizmo();
    };

}