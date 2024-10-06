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

        void addEngineAssetsCheckbox();
        static bool isEngineAsset(std::string name, std::string path);

        ImGuiTableFlags flags;
        bool m_bShowEngineAssets;
    };
}