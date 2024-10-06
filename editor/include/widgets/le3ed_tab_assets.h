#pragma once

#include <le3.h>

namespace le3 {
    class LE3EditorTabAssets {
    public:
        void init();
        void update();

    private:        
        void updateShaders();
        void updateMaterials();
        void updateTextures();
        void updateMeshes();

        ImGuiTableFlags flags;
    };
}