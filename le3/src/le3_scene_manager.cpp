#include "le3_scene_manager.h"

void SaveScene(LE3SceneManager& scene, std::string serializationPath)
{
    std::ofstream fp(serializationPath, std::ofstream::out);
    {
        cereal::JSONOutputArchive oarchive(fp);
        oarchive(CEREAL_NVP(scene));
    }
}
void LoadScene(LE3SceneManager& scene, std::string serializationPath)
{
    std::ifstream fp(serializationPath, std::ofstream::in);
    {
        cereal::JSONInputArchive iarchive(fp);
        iarchive(scene);
    }
}

void LE3SceneManager::Init()
{
    physics.Init();
    root = std::shared_ptr<LE3SceneRoot>(new LE3SceneRoot());

    // Create default shader and material
    assets.LoadShader(DEFAULT_SHADER_NAME, "../resources/shaders/default/default.vs", "../resources/shaders/default/default.fs");
    assets.CreateMaterial(DEFAULT_MATERIAL_NAME, DEFAULT_SHADER_NAME);
}

void LE3SceneManager::Clear()
{
    assets.Clear();
    objectPool.clear();
    parentLinks.clear();

    this->Init();
}

void LE3SceneManager::UpdateSceneGraph()
{
    for (auto& [name, obj]: objectPool)
    {
        std::string parentName = parentLinks[name];
        std::shared_ptr<LE3Object> parent = std::static_pointer_cast<LE3Object>(root);
        if (parentName.size())
            parent = objectPool[parentName];
        obj->Reparent(parent.get());
    }
}

void LE3SceneManager::UpdateAssets()
{
    for (auto& [name, obj]: objectPool)
    {
        obj->UpdateAssets(assets);
    }
}

void LE3SceneManager::UpdatePhysics()
{
    for (auto& [name, obj]: objectPool)
    {
        obj->UpdatePhysics(physics);
    }
}

std::shared_ptr<LE3SceneRoot> LE3SceneManager::GetRoot() const
{
    return root;
}
std::shared_ptr<LE3Camera> LE3SceneManager::GetCamera() const 
{
    return camera;
}

LE3PhysicsComponent* LE3SceneManager::GetPhysics() const
{
    return (LE3PhysicsComponent*)&physics;
}

std::shared_ptr<LE3Object> LE3SceneManager::GetObject(std::string name)
{
    return objectPool[name];
}

void LE3SceneManager::AddFreeCamera(glm::vec3 position)
{
    camera = std::shared_ptr<LE3Camera>(new LE3FreeCamera());
    camera->SetPosition(position);
    camera->SetHiddenInSceneGraph(true);
    objectPool["camera"] = std::static_pointer_cast<LE3Object>(camera);
    parentLinks["camera"] = "";
    UpdateSceneGraph();
}

void LE3SceneManager::AddFPSCamera(glm::vec3 position)
{
    camera = std::shared_ptr<LE3Camera>(new LE3FPSCamera());
    camera->SetPosition(position);
    camera->SetHiddenInSceneGraph(true);
    objectPool["camera"] = std::static_pointer_cast<LE3Object>(camera);
    parentLinks["camera"] = "";
    UpdateSceneGraph();
}

void LE3SceneManager::AddStaticMesh(std::string name, std::string meshName, std::string materialName, float scale, bool registerCollision, std::string parent)
{
    std::shared_ptr<LE3StaticMesh> obj(new LE3StaticMesh(name));
    obj->meshName = meshName;
    obj->materialName = materialName;
    obj->UpdateAssets(assets);
    obj->SetScale(scale);
    if (registerCollision)
        obj->RegisterCollision(&physics);
    objectPool[name] = std::static_pointer_cast<LE3Object>(obj);
    parentLinks[name] = parent;
    UpdateSceneGraph();
}

void LE3SceneManager::AddAmbientLight(glm::vec3 color, float intensity)
{
    std::shared_ptr<LE3AmbientLight> obj(new LE3AmbientLight(color, intensity));
    objectPool[obj->GetName()] = std::static_pointer_cast<LE3Object>(obj);
    parentLinks[obj->GetName()] = "";
    lightManager.SetAmbientLight(obj);
    UpdateSceneGraph();
}

void LE3SceneManager::AddDirectionalLight(std::string name, glm::vec3 color, float intensity, std::string parent)
{
    std::shared_ptr<LE3DirectionalLight> obj(new LE3DirectionalLight(name, color, intensity));
    objectPool[obj->GetName()] = std::static_pointer_cast<LE3Object>(obj);
    parentLinks[obj->GetName()] = parent;
    lightManager.AddDirectionalLight(obj);
    UpdateSceneGraph();
}

void LE3SceneManager::AddPointLight(std::string name, glm::vec3 color, float intensity, float attn_const, float attn_linear, float attn_exp, std::string parent)
{
    std::shared_ptr<LE3PointLight> obj(new LE3PointLight(name, color, intensity, attn_const, attn_linear, attn_exp));
    objectPool[obj->GetName()] = std::static_pointer_cast<LE3Object>(obj);
    parentLinks[obj->GetName()] = parent;
    lightManager.AddPointLight(obj);
    UpdateSceneGraph();
}

void LE3SceneManager::AddObject(std::string name, std::string parent)
{
    std::shared_ptr<LE3Object> obj(new LE3Object(name));
    objectPool[name] = obj;
    parentLinks[name] = parent;
    UpdateSceneGraph();
}

void LE3SceneManager::Reparent(std::string object, std::string newParent)
{
    parentLinks[object] = newParent;
    UpdateSceneGraph();
}

void LE3SceneManager::Render()
{
    for (const auto& [key, value] : assets.m_shaders)
    {
        LE3Shader* shader = assets.GetShader(key);
        shader->Use();
        shader ->Uniform("view", GetCamera()->GetViewMatrix());
        shader->Uniform("projection", GetCamera()->GetProjectionMatrix());
        lightManager.RenderLights(shader);
    }
    GetRoot()->Draw();
}