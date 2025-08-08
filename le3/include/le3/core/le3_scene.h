#pragma once

#include <map>
#include <string>
#include <functional>

#include "algorithms/le3_bsp.h"

#include "core/le3_object.h"
#include "core/le3_scene_root.h"
#include "core/le3_event_manager.h"

#include "graphics/le3_model.h"
#include "graphics/le3_material.h"
#include "graphics/le3_camera.h"
#include "graphics/le3_shader.h"
#include "graphics/le3_texture.h"
#include "graphics/le3_sprite.h"
#include "graphics/le3_draw_queue.h"
#include "graphics/le3_primitives.h"
#include "graphics/le3_framebuffer.h"
#include "graphics/le3_light_manager.h"
#include "graphics/le3_point_cloud.h"

#include "utils/le3_gizmo.h"
#include "gameplay/le3_playerstart.h"
#include "scripting/le3_script_object.h"
#include "networking/le3_network_spinner.h"

namespace le3 {
    struct LE3SceneGraph {
        LE3SceneRootPtr m_pRoot; // NOTE: root is not in pObjects
        LE3ObjectPtr m_pRootObj; // Should point to same location as m_pRoot (used as ObjectPtr& for reparenting)
        std::map<std::string, LE3ObjectPtr> m_pObjects;
        LE3DrawQueue m_drawQueue;
        LE3BSPManager m_bspManager;
        LE3LightManager m_lightManager;
        std::vector<LE3ObjectWeakPtr> m_inspectedUpdate;
    };
    using LE3SceneGraphPtr = std::shared_ptr<LE3SceneGraph>;

    namespace LE3SceneEvents {
        ADD_EVENT(LE3_EVENT_OBJECT_RENAME);
    }

    class LE3Scene {
    public:
        LE3Scene(std::string name = "") : m_name(name) {}
        std::string getName() const { return m_name; }

        void init(int width, int height);
        void init_inspector(int width, int height, LE3Scene& original); // Observe another scene by sharing a scene graph
        void reset();

        void resize(int width, int height);
        void updateOffset(int offsetX, int offsetY);

        // Path to Lua file that creates a (global) table "Scene"
        void load(std::string path);
        void save(std::string path, bool shared); // Shared scene saves only assets and objects under __shared__ object, regular scene only save objects!
        
        void update(float deltaTime);
        void preUpdate();
        void postUpdate();
        void draw();
        void drawSSAO();
        void drawLights();
        void drawObjects(LE3ShaderPtr shaderOverride = LE3ShaderPtr(), LE3FramebufferPtr buffer = nullptr, bool depth = true, bool shadowPhase = false);
        void drawObjectIDs();
        void drawSelected();
        void drawPostProcess();
        void drawColliders();
        void drawObjectPositions();
        void setPostProcessShader(LE3ShaderPtr shader) { m_postProcessShader = shader; }

        void rebuild(); // Call whenever major structural changes happen to scene graph (like shader change/deletion)

        // Set false if we want to render to the inner postProccess buffer
        void setRenderDirectly(bool renderDirectly) { m_bRenderDirectly = renderDirectly; }
        bool isRenderDirectly() { return m_bRenderDirectly; }
        LE3FramebufferPtr getSceneFramebuffer() { return m_postProcessBuffer; } // Applicable only if !m_bRenderDirectly

        // Object factory
        void addEmptyObject(std::string name, std::string parent = "");
        void addBox(std::string name, std::string materialName, glm::vec3 position = glm::vec3(0.f), glm::vec3 extent = glm::vec3(1.f), std::string parent = "");
        void addCylinder(std::string name, std::string materialName, glm::vec3 position = glm::vec3(0.f), float radius = 1.f, float height = 1.f, int resolution = 16, bool withCaps = true, std::string parent = "");
        void addCone(std::string name, std::string materialName, glm::vec3 position = glm::vec3(0.f), float radius = 1.f, float height = 1.f, int resolution = 16, bool withCaps = true, std::string parent = "");
        void addTorus(std::string name, std::string materialName, glm::vec3 position = glm::vec3(0.f), float majorRadius = 1.f, float minorRadius = 0.5f, int resolution = 16, std::string parent = "");
        void addSphere(std::string name, std::string materialName, glm::vec3 position = glm::vec3(0.f), float radius = 1.f, int resolution = 32, std::string parent = "");

        void addStaticModel(std::string name, std::string meshName, std::string materialName, std::string parent = "", LE3DrawPriority priority = DRAW_PRIORITY_LOW);
        void addSkeletalModel(std::string name, std::string meshName, std::string materialName, std::string parent = "");
        void addPointCloud(std::string name, std::string parent = "");
        void addSprite(std::string name, std::string textureName, std::string parent = "");

        void addBSPBrush(std::string name, LE3BSPBrushType brushType = LE3_BRUSH_ADDITIVE);
        void buildBSP();

        void addPlayerStart(std::string classname = LE3_PLAYERSTART_DEFAULT_CLASS);
        void addFreeCamera(std::string name, std::string parent = "");
        void addOrbitCamera(std::string name, std::string parent = "");

        void addAmbientLight(std::string name, std::string parent = "");
        void addDirectionalLight(std::string name, std::string parent = "");
        void addPointLight(std::string name, std::string parent = "");
        void addSpotLight(std::string name, std::string parent = "");

        void addScriptObject(std::string name, std::string classname, std::string parent = "");
        void addCustomObject(std::string name, std::shared_ptr<LE3Object> obj, std::string parent = ""); // DANGER! Use with caution

        void deleteObject(std::string name);
        void renameObject(std::string oldName, std::string newName);

        LE3SceneRootPtr getSceneRoot() const { return m_sceneGraph->m_pRoot; }
        LE3CameraPtr& getMainCamera() { return m_pMainCamera; }
        void setMainCamera(std::string camera);

        void addInspectedUpdate(std::string name) { if (!m_bInspected) return; m_sceneGraph->m_inspectedUpdate.push_back(getObject(name)); }
        bool isInspected() const { return m_bInspected; }

        inline LE3ObjectPtr& getObject(std::string name) { 
            if (name == getSceneRoot()->getName()) return m_sceneGraph->m_pRootObj;
            if (!m_sceneGraph->m_pObjects.contains(name)) return m_nullptr;
            return m_sceneGraph->m_pObjects[name]; 
        }
        template <typename T>
        std::shared_ptr<T> getObject(std::string name) {
            return std::dynamic_pointer_cast<T>(getObject(name));
        }
        // std::string getObjectName(LE3ObjectPtr obj);
        std::map<std::string, LE3ObjectPtr>& getObjects() { return m_sceneGraph->m_pObjects; }

        LE3BSPManager& getBSPManager() { return m_sceneGraph->m_bspManager; }

        // Misc
        glm::vec3 getBackgroundColor() const { return m_backgroundColor; }
        void setBackgroundColor(glm::vec3 backgroundColor) { m_backgroundColor = backgroundColor; }
        void setCulling(bool culling) { m_bCulling = culling; }
        int getWidth() const { return m_width; }
        int getHeight() const { return m_height; }
        void setLightSpriteVisibility(bool bVisible) { m_sceneGraph->m_lightManager.setLightSpriteVisibility(bVisible); }

        std::string getNextAvailableName(std::string objectName);

        // Returns the global cursor location in the scene's region, normalized to [-1, 1]
        // This also includes the case for multiple scenes rendering at the same time
        // The cursor is only relevant if the z coord is > 0.f
        glm::vec3 getCursorLocation();

        std::function<void()> drawDebug = nullptr;
        std::function<void(LE3ShaderPtr pPostProcessShader)> postProcessUniforms = nullptr;

        void propagateDeleteMaterial(std::string name); // Fix material pointers on deletion

    private:
        LE3SceneGraphPtr m_sceneGraph;
        LE3ObjectPtr m_nullptr = nullptr;
        std::string m_name;
        uint32_t m_ticket = 0;

        // For inspector scenes (update only very specific objects)
        bool m_bInspected;

        glm::vec3 m_backgroundColor = glm::vec3(1.f);
        bool m_bCulling = false;

        LE3FramebufferPtr m_rawBuffer, m_postProcessBuffer, m_ssaoBuffer, m_positionsBuffer, m_objectIdsBuffer, m_selectedObjectsBuffer;
        LE3ShaderPtr m_postProcessShader;
        int m_width, m_height;
        int m_offsetX = 0, m_offsetY = 0;
        bool m_bRenderDirectly = true;
        LE3CameraPtr m_pMainCamera; 
        
        void assertObjectName(std::string name);
        void attachObject(std::string name, LE3ObjectPtr obj, std::string parent);
        void attachCamera(LE3CameraPtr pCamera);

        void applyMainCamera(LE3ShaderPtr shader);

        LE3ObjectPtr getObjectByID(uint32_t oid);
        LE3ObjectPtr getObjectByID(glm::vec4 color);
        void updateHoveredObject();
    };
    using LE3ScenePtr = std::shared_ptr<LE3Scene>;
}
