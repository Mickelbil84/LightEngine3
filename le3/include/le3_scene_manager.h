#pragma once

#include <map>
#include <vector>
#include <memory>
#include <fstream>

#include <cereal/types/memory.hpp>
#include <cereal/cereal.hpp>
#include <cereal/archives/json.hpp>
#include <cereal/archives/binary.hpp>

#include "le3_camera.h"
#include "le3_physics.h"
#include "le3_scene_root.h"
#include "le3_static_mesh.h"
#include "le3_asset_manager.h"
#include "le3_light_manager.h"

#define DEFAULT_SHADER_NAME "S_default"
#define DEFAULT_MATERIAL_NAME "M_default"

class LE3SceneManager
{
public:
    LE3AssetManager assets;
    LE3LightManager lightManager;

    // void SaveScene(std::string serializationPath) const;
    // void LoadScene(std::string serializationPath);

    void Init();
    void Render();
    void Clear();

    void AddFreeCamera(glm::vec3 position=glm::vec3(0.f));
    void AddFPSCamera(glm::vec3 position=glm::vec3(0.f));

    void AddObject(std::string name, std::string parent="");
    void AddStaticMesh(std::string name, std::string meshName, std::string materialName, float scale=1.f, bool registerCollision=true, std::string parent="");
    void AddAmbientLight(glm::vec3 color=glm::vec3(1.f), float intensity=0.1f);
    void AddDirectionalLight(std::string name, glm::vec3 color=glm::vec3(1.f), float intensity=0.8f, std::string parent="");
    void AddPointLight(std::string name, glm::vec3 color=glm::vec3(1.f), float intensity=0.8f, float attn_const = 1.f, float attn_linear = 0.09f, float attn_exp = 0.032f, std::string parent="");

    std::shared_ptr<LE3SceneRoot> GetRoot() const;
    std::shared_ptr<LE3Camera> GetCamera() const;
    LE3PhysicsComponent* GetPhysics() const;

    std::shared_ptr<LE3Object> GetObject(std::string name);
    void Reparent(std::string object, std::string newParent);

protected:
    std::shared_ptr<LE3SceneRoot> root;
    std::shared_ptr<LE3Camera> camera;
    LE3PhysicsComponent physics;

public:
    std::map<std::string, std::shared_ptr<LE3Object>> objectPool;
    std::map<std::string, std::string> parentLinks;

public:
    // Use parent links to fix the scene graph
    void UpdateSceneGraph();
    void UpdateAssets();
    void UpdatePhysics();


public:
    template <class Archive>
    void save( Archive & ar ) const
    {
        ar(CEREAL_NVP(assets));
        ar(CEREAL_NVP(objectPool), CEREAL_NVP(parentLinks));
        ar(CEREAL_NVP(lightManager));
    }

    template <class Archive>
    void load( Archive & ar )
    {
        ar(assets);
        ar(objectPool, parentLinks);
        ar(lightManager);
        UpdateSceneGraph();
        UpdateAssets();
        UpdatePhysics();
    }
};

void SaveScene(LE3SceneManager& scene, std::string serializationPath);
void LoadScene(LE3SceneManager& scene, std::string serializationPath);