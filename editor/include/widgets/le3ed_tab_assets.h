#pragma once

#include <le3.h>

#include "widgets/popups/le3ed_pop_add_shader.h"

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
        void updateAnimations();

        void addEngineAssetsCheckbox();
        static bool isEngineAsset(std::string name, std::string path);

        ImGuiTableFlags flags;
        bool m_bShowEngineAssets;

        // Popups
        LE3EdPopAddShader m_popAddShader;
    };
}