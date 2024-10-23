#pragma once

#include <map>
#include <string>

#include "le3_model.h"
#include "le3_shader.h"
#include "le3_texture.h"
#include "le3_geometry.h"

namespace le3 {

    const std::string DEFAULT_ENGINE_PREFIX = "__ENGINE__";

    const std::string ERROR_SHADER_VERTEX_PATH = "/engine/shaders/error/error.vs";
    const std::string ERROR_SHADER_FRAGMENT_PATH = "/engine/shaders/error/error.fs";
    const std::string ERROR_SHADER = DEFAULT_ENGINE_PREFIX + "S_error";
    const std::string ERROR_TEXTURE_PATH = "/engine/textures/error.png";
    const std::string ERROR_TEXTURE = DEFAULT_ENGINE_PREFIX + "T_error";
    const std::string ERROR_MATERIAL = DEFAULT_ENGINE_PREFIX + "M_error";


    const std::string DEFAULT_SHADER = "S_default";
    const std::string DEFAULT_OBJECTID_SHADER = "S_objectid";
    const std::string DEFAULT_POSTPROCESS_SHADER = "S_defaultPostProcess";
    const std::string DEFAULT_SHADOWMAP_SHADER = "S_shadowmap";
    const std::string DEFAULT_DEBUG_SHADER = "S_debug";
    const std::string DEFAULT_GIZMO_SHADER = "S_gizmo";

    const std::string DEFAULT_SPRITE_SHADER = "S_sprite";
    const std::string DEFAULT_SPRITE_MATERIAL = DEFAULT_ENGINE_PREFIX + "M_sprite";

    const std::string SPRITE_AMBIENT_LIGHT = DEFAULT_ENGINE_PREFIX + "T_sprite_ambient";
    const std::string SPRITE_DIRECTIONAL_LIGHT = DEFAULT_ENGINE_PREFIX + "T_sprite_directional";
    const std::string SPRITE_POINT_LIGHT = DEFAULT_ENGINE_PREFIX + "T_sprite_point";
    const std::string SPRITE_SPOT_LIGHT = DEFAULT_ENGINE_PREFIX + "T_sprite_spot";

    const std::string DEFAULT_GIZMO_MATERIAL = DEFAULT_ENGINE_PREFIX + "M_gizmo";

    class LE3AssetManager {
    public:
        void init();
        void refreshPointers(); // In case of asset deletions, make sure everything is still kosher

        // Shaders
        void addShaderFromFile(std::string name, std::string vertexShaderPath, std::string fragmentShaderPath);
        void addShaderFromSource(std::string name, std::string vertexShaderSource, std::string fragmentShaderSource);
        inline LE3ShaderPtr getShader(std::string name) { return m_pShaders[name]; }
        inline std::map<std::string, std::shared_ptr<LE3Shader>> getShaders() { return m_pShaders; }
        void setShaderPaths(std::string name, std::string vertexShaderPath, std::string fragmentShaderPath) {
            if (name != "" && m_shadersPaths.contains(name))
                m_shadersPaths[name] = std::make_pair(vertexShaderPath, fragmentShaderPath);
        }
        std::pair<std::string, std::string> getShaderPaths(std::string name) {
            if (m_shadersPaths.contains(name)) return m_shadersPaths[name];
            return std::make_pair("", "");
        }
        void renameShader(std::string oldName, std::string newName);
        bool hasShader(std::string name) { return m_pShaders.contains(name); }
        void deleteShader(std::string name);

        // Materials
        void addMaterial(std::string name, std::string shaderName);
        inline LE3MaterialPtr getMaterial(std::string name) { return m_pMaterials[name]; }
        inline std::map<std::string, std::shared_ptr<LE3Material>> getMaterials() { return m_pMaterials; }
        bool hasMaterial(std::string name) { return m_pMaterials.contains(name); }
        void renameMaterial(std::string oldName, std::string newName);
        void deleteMaterial(std::string name);

        // Textures
        void addTexture(std::string name, std::vector<unsigned char> data, int width, int height, int nChannels, bool interpolate = true);
        void addTexture(std::string name, std::string filename, bool interpolate = true);
        inline LE3TexturePtr getTexture(std::string name) { 
            if (!m_pTextures.contains(name)) return LE3TexturePtr();
            return m_pTextures[name]; 
        }
        inline std::string getTexturePath(std::string name) { 
            if (!m_texturesPaths.contains(name)) return "";
            return m_texturesPaths[name]; 
        }
        void setTexturePath(std::string name, std::string path) { m_texturesPaths[name] = path; }
        bool hasTexture(std::string name) { return m_pTextures.contains(name); }
        void reloadTexture(std::string name, std::string filename, bool interpolate = true);
        void renameTexture(std::string oldName, std::string newName);
        void deleteTexture(std::string name);

        // Meshes
        void addStaticMesh(std::string name, std::string filename, bool keepData = false);
        inline LE3StaticMeshPtr getStaticMesh(std::string name) { return m_pStaticMeshes[name]; }
        void searchStaticMeshes(std::string prefix, std::vector<std::string>& out);
        bool hasStaticMesh(std::string name) { return m_pStaticMeshes.contains(name); }
        void reloadStaticMesh(std::string name, std::string filename, bool keepData = false);
        void renameStaticMesh(std::string oldName, std::string newName);
        void deleteStaticMesh(std::string name);

        void addSkeletalMesh(std::string name, std::string filename);
        inline LE3SkeletalMeshPtr getSkeletalMesh(std::string name) { return m_pSkeletalMeshes[name]; }
        void addSkeletalAnimation(std::string name, std::string animationPath, std::string meshName); // Implemented in `le3_assimp.cpp`
        bool isSkeletalMesh(std::string name);
        bool hasSkeletalMesh(std::string name) { return m_pSkeletalMeshes.contains(name); }
        void reloadSkeletalMesh(std::string name, std::string filename);
        void renameSkeletalMesh(std::string oldName, std::string newName);
        void deleteSkeletalMesh(std::string name);

        inline std::string getMeshPath(std::string name) { return m_meshesPaths[name]; }
        void setMeshPath(std::string name, std::string path) { m_meshesPaths[name] = path; }

        inline std::shared_ptr<LE3ScreenRect> getScreenRect() { return m_screenRect; }
        inline LE3MeshPtr<LE3Vertex3p> getDebugLine() { return m_debugLine; }
        inline LE3MeshPtr<LE3Vertex3p> getDebugBox() { return m_debugBox; }
        inline LE3MeshPtr<LE3Vertex3p> getDebugCylinder() { return m_debugCylinder; }
        inline LE3MeshPtr<LE3Vertex3p> getDebugCone() { return m_debugCone; }

        inline LE3StaticMeshPtr getGizmoArrowMesh() { return m_gizmoArrow; }
        inline LE3StaticMeshPtr getGizmoScaleArrowMesh() { return m_gizmoScaleArrow; }
        inline LE3StaticMeshPtr getGizmoCircleMesh() { return m_gizmoCircle; }
        inline LE3StaticMeshPtr getGizmoPlaneMesh() { return m_gizmoPlane; }
        inline LE3StaticMeshPtr getGizmoCenterMesh() { return m_gizmoCenter; }

        inline std::map<std::string, std::pair<std::string, std::string>> getShadersPaths() { return m_shadersPaths; }
        inline std::map<std::string, std::string> getTexturesPaths() { return m_texturesPaths; }
        inline std::map<std::string, std::string> getMeshesPaths() { return m_meshesPaths; }

        inline LE3ShaderPtr getErrorShader() { return m_gErrorShader; }
        inline LE3TexturePtr getErrorTexture() { return m_gErrorTexture; }
        inline LE3MaterialPtr getErrorMaterial() { return m_gErrorMaterial; }

    private:
        // Asset maps
        std::map<std::string, std::shared_ptr<LE3Shader>> m_pShaders;
        std::map<std::string, std::shared_ptr<LE3Material>> m_pMaterials;
        std::map<std::string, std::shared_ptr<LE3Texture>> m_pTextures;
        std::map<std::string, std::shared_ptr<LE3StaticMesh>> m_pStaticMeshes;
        std::map<std::string, std::shared_ptr<LE3SkeletalMesh>> m_pSkeletalMeshes;

        // Asset paths
        std::map<std::string, std::pair<std::string, std::string>> m_shadersPaths;
        std::map<std::string, std::string> m_texturesPaths;
        std::map<std::string, std::string> m_meshesPaths;

        std::shared_ptr<LE3ScreenRect> m_screenRect = nullptr; // Create this crucial geometry only once

        // Debug meshes
        std::shared_ptr<LE3Mesh<LE3Vertex3p>> m_debugLine, m_debugBox, m_debugCylinder, m_debugCone;
        std::shared_ptr<LE3StaticMesh> m_gizmoArrow, m_gizmoScaleArrow, m_gizmoCircle, m_gizmoPlane, m_gizmoCenter;

        // Error (missing) assets
        std::shared_ptr<LE3Shader> m_gErrorShader;
        std::shared_ptr<LE3Texture> m_gErrorTexture;
        std::shared_ptr<LE3Material> m_gErrorMaterial;

        // Recently deleted assets (for consumption in `refreshPointers`)
        std::string 
            m_lastDeletedShader = "", 
            m_lastDeletedTexture = "", 
            m_lastDeletedMaterial = "", 
            m_lastDeletedStaticMesh = "", m_lastDeletedSkeletalMesh = "";

        // Helper methods
        std::string readFile(std::string filename);
        std::shared_ptr<LE3StaticMesh> loadStaticMesh(std::string filename, bool keepData); // Implemented in `le3_assimp.cpp`
        void reloadStaticMesh(std::shared_ptr<LE3StaticMesh> mesh, std::string filename, bool keepData); // Implemented in `le3_assimp.cpp`
        std::shared_ptr<LE3SkeletalMesh> loadSkeletalMesh(std::string filename); // Implemented in `le3_assimp.cpp`
        void reloadSkeletalMesh(std::shared_ptr<LE3SkeletalMesh> mesh, std::string filename); // Implemented in `le3_assimp.cpp`
    }; 
}