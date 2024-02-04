#pragma once

#include <map>
#include <string>

#include "le3_model.h"
#include "le3_material.h"
#include "le3_camera.h"
#include "le3_object.h"
#include "le3_shader.h"
#include "le3_texture.h"
#include "le3_draw_queue.h"
#include "le3_primitives.h"
#include "le3_scene_root.h"
#include "le3_framebuffer.h"
#include "le3_light_manager.h"

namespace le3 {
    struct LE3SceneViewport {
        LE3FramebufferPtr m_rawBuffer, m_postProcessBuffer;
        LE3ShaderPtr m_postProcessShader;
        LE3CameraPtr m_pCamera; 

        int m_width, m_height;

        void resize(int width, int height) {} // TODO: ...
    };

    class LE3Scene {
    public:
        void init(int width, int height);
        void reset();

        void resize(int width, int height);

        // Path to Lua file that creates a (global) table "Scene"
        void load(std::string path);
        
        void update(float deltaTime);
        void draw();
        void drawObjects(LE3ShaderPtr shaderOverride = nullptr, LE3FramebufferPtr buffer = nullptr, bool depth = true);
        void drawPostProcess();

        // Set false if we want to render to the inner postProccess buffer
        void setRenderDirectly(bool renderDirectly) { m_bRenderDirectly = renderDirectly; }
        LE3FramebufferPtr getSceneFramebuffer() { return m_postProcessBuffer; } // Applicable only if !m_bRenderDirectly

        // Shaders
        void addShaderFromFile(std::string name, std::string vertexShaderPath, std::string fragmentShaderPath);
        void addShaderFromSource(std::string name, std::string vertexShaderSource, std::string fragmentShaderSource);
        inline LE3ShaderPtr& getShader(std::string name) { return m_pShaders[name]; }

        // Materials
        void addMaterial(std::string name, std::string shaderName);
        inline LE3MaterialPtr& getMaterial(std::string name) { return m_pMaterials[name]; }

        // Textures
        void addTexture(std::string name, std::vector<unsigned char> data, int width, int height, int nChannels, bool interpolate = true);
        void addTexture(std::string name, std::string filename, bool interpolate = true);
        inline LE3TexturePtr& getTexture(std::string name) { return m_pTextures[name]; }

        // Meshes
        void addStaticMesh(std::string name, std::string filename);
        inline LE3StaticMeshPtr& getStaticMesh(std::string name) { return m_pStaticMeshes[name]; }

        // Object factory
        void addEmptyObject(std::string name, std::string parent = "");
        void addBox(std::string name, std::string materialName, glm::vec3 position = glm::vec3(0.f), glm::vec3 extent = glm::vec3(1.f), std::string parent = "");
        void addStaticModel(std::string name, std::string meshName, std::string materialName, std::string parent = "");

        void addFreeCamera(std::string name, std::string parent = "");
        void addOrbitCamera(std::string name, std::string parent = "");

        void addAmbientLight(std::string name, std::string parent = "");
        void addDirectionalLight(std::string name, std::string parent = "");
        void addPointLight(std::string name, std::string parent = "");
        void addSpotLight(std::string name, std::string parent = "");

        LE3SceneRootPtr getSceneRoot() const { return m_pRoot; }
        LE3ObjectPtr& getObject(std::string name) { return m_pObjects[name]; }
        LE3CameraPtr& getMainCamera() { return m_pMainCamera; }
        void setMainCamera(std::string camera);

        // Misc
        glm::vec3 getBackgroundColor() const { return m_backgroundColor; }
        void setBackgroundColor(glm::vec3 backgroundColor) { m_backgroundColor = backgroundColor; }

    private:
        std::map<std::string, LE3ShaderPtr> m_pShaders;
        std::map<std::string, LE3MaterialPtr> m_pMaterials;
        std::map<std::string, LE3TexturePtr> m_pTextures;
        std::map<std::string, LE3StaticMeshPtr> m_pStaticMeshes;

        LE3SceneRootPtr m_pRoot; // NOTE: root is not in pObjects
        LE3CameraPtr m_pMainCamera; 
        std::map<std::string, LE3ObjectPtr> m_pObjects;
        std::map<std::string, LE3ObjectPtr> m_pPrototypes; // Objects that are not present in scene, but can be duplicated
        LE3DrawQueue m_drawQueue;
        LE3LightManager m_lightManager;

        glm::vec3 m_backgroundColor = glm::vec3(1.f);

        LE3FramebufferPtr m_rawBuffer, m_postProcessBuffer;
        LE3ShaderPtr m_postProcessShader;
        int m_width, m_height;
        bool m_bRenderDirectly = true;
        
        void assertObjectName(std::string name);
        void attachObject(std::string name, LE3ObjectPtr obj, std::string parent);
        void attachCamera(LE3CameraPtr pCamera);

        void applyMainCamera(LE3ShaderPtr shader);

        // Helper methods
        std::string readFile(std::string filename);
        LE3StaticMeshPtr loadStaticMesh(std::string filename); // Implemented in le3_scene_assimp.cpp
    };
}