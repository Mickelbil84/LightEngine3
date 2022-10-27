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

class LE3SceneManager
{
public:
    LE3AssetManager assets;

    // void SaveScene(std::string serializationPath) const;
    // void LoadScene(std::string serializationPath);

    void Init();

    void AddFreeCamera(glm::vec3 position=glm::vec3(0.f));

    void AddObject(std::string name, std::string parent="");
    void AddStaticMesh(std::string name, std::string meshName, std::string materialName, float scale=1.f, bool registerCollision=true, std::string parent="");

    std::shared_ptr<LE3SceneRoot> GetRoot() const;
    std::shared_ptr<LE3Camera> GetCamera() const;
    LE3PhysicsComponent* GetPhysics() const;

    std::shared_ptr<LE3Object> GetObject(std::string name);
    void Reparent(std::string object, std::string newParent);

protected:
    std::shared_ptr<LE3SceneRoot> root;
    std::shared_ptr<LE3Camera> camera;
    LE3PhysicsComponent physics;
    
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
    }

    template <class Archive>
    void load( Archive & ar )
    {
        ar(assets);
        ar(objectPool, parentLinks);
        UpdateSceneGraph();
        UpdateAssets();
        UpdatePhysics();
    }
};

void SaveScene(LE3SceneManager& scene, std::string serializationPath);
void LoadScene(LE3SceneManager& scene, std::string serializationPath);