#pragma once

#include <map>
#include <string>

#include "le3_model.h"
#include "le3_shader.h"
#include "le3_texture.h"
#include "le3_geometry.h"

namespace le3 {
    const std::string DEFAULT_ENGINE_PREFIX = "__ENGINE__";

    const std::string DEFAULT_SHADER = "S_default";
    const std::string DEFAULT_OBJECTID_SHADER = "S_objectid";
    const std::string DEFAULT_POSTPROCESS_SHADER = "S_defaultPostProcess";
    const std::string DEFAULT_SHADOWMAP_SHADER = "S_shadowmap";
    const std::string DEFAULT_DEBUG_SHADER = "S_debug";
    const std::string DEFAULT_GIZMO_SHADER = "S_gizmo";

    const std::string DEFAULT_GIZMO_MATERIAL = DEFAULT_ENGINE_PREFIX + "M_gizmo";

    class LE3AssetManager {
    public:
        void init();

        // Shaders
        void addShaderFromFile(std::string name, std::string vertexShaderPath, std::string fragmentShaderPath);
        void addShaderFromSource(std::string name, std::string vertexShaderSource, std::string fragmentShaderSource);
        inline LE3ShaderPtr& getShader(std::string name) { return m_pShaders[name]; }
        inline std::map<std::string, LE3ShaderPtr> getShaders() { return m_pShaders; }

        // Materials
        void addMaterial(std::string name, std::string shaderName);
        inline LE3MaterialPtr& getMaterial(std::string name) { return m_pMaterials[name]; }

        // Textures
        void addTexture(std::string name, std::vector<unsigned char> data, int width, int height, int nChannels, bool interpolate = true);
        void addTexture(std::string name, std::string filename, bool interpolate = true);
        inline LE3TexturePtr& getTexture(std::string name) { return m_pTextures[name]; }

        // Meshes
        void addStaticMesh(std::string name, std::string filename, bool keepData = false);
        inline LE3StaticMeshPtr& getStaticMesh(std::string name) { return m_pStaticMeshes[name]; }
        void searchStaticMeshes(std::string prefix, std::vector<std::string>& out);

        void addSkeletalMesh(std::string name, std::string filename);
        inline LE3SkeletalMeshPtr& getSkeletalMesh(std::string name) { return m_pSkeletalMeshes[name]; }
        void addSkeletalAnimation(std::string name, std::string animationPath, std::string meshName); // Implemented in `le3_assimp.cpp`

        inline LE3ScreenRectPtr getScreenRect() { return m_screenRect; }
        inline LE3MeshPtr<LE3Vertex3p> getDebugLine() { return m_debugLine; }
        inline LE3MeshPtr<LE3Vertex3p> getDebugBox() { return m_debugBox; }
        inline LE3MeshPtr<LE3Vertex3p> getDebugCylinder() { return m_debugCylinder; }
        inline LE3MeshPtr<LE3Vertex3p> getDebugCone() { return m_debugCone; }

        inline LE3StaticMeshPtr getGizmoArrowMesh() { return m_gizmoArrow; }
        inline LE3StaticMeshPtr getGizmoCenterMesh() { return m_gizmoCenter; }


    private:
        // Asset maps
        std::map<std::string, LE3ShaderPtr> m_pShaders;
        std::map<std::string, LE3MaterialPtr> m_pMaterials;
        std::map<std::string, LE3TexturePtr> m_pTextures;
        std::map<std::string, LE3StaticMeshPtr> m_pStaticMeshes;
        std::map<std::string, LE3SkeletalMeshPtr> m_pSkeletalMeshes;

        LE3ScreenRectPtr m_screenRect = nullptr; // Create this crucial geometry only once

        // Debug meshes
        LE3MeshPtr<LE3Vertex3p> m_debugLine, m_debugBox, m_debugCylinder, m_debugCone;
        LE3StaticMeshPtr m_gizmoArrow, m_gizmoCenter;

        // Helper methods
        std::string readFile(std::string filename);
        LE3StaticMeshPtr loadStaticMesh(std::string filename, bool keepData); // Implemented in `le3_assimp.cpp`
        LE3SkeletalMeshPtr loadSkeletalMesh(std::string filename); // Implemented in `le3_assimp.cpp`
    }; 
}