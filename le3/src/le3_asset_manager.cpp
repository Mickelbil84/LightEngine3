#include "le3_asset_manager.h"

void LE3AssetManager::LoadMesh(std::string name, std::vector<LE3Vertex> data)
{
    LE3Mesh<LE3Vertex> mesh;
    mesh.LoadMeshData(data);
    m_meshes[name] = mesh;
}
LE3Mesh<LE3Vertex>* LE3AssetManager::GetMesh(std::string name)
{
    return &m_meshes[name];
}

void LE3AssetManager::LoadShader(std::string name, std::string vertexShaderPath, std::string fragmentShaderPath)
{
    LE3Shader shader;
    shader.CompileShader(vertexShaderPath, fragmentShaderPath);
    m_shaders[name] = shader;
}
LE3Shader* LE3AssetManager::GetShader(std::string name)
{
    return &m_shaders[name];
}

void LE3AssetManager::LoadTexture(std::string name, std::string texturePath)
{
    LE3Texture texture;
    texture.Load(texturePath);
    m_textures[name] = texture;
}
LE3Texture* LE3AssetManager::GetTexture(std::string name)
{
    return &m_textures[name];
}

void LE3AssetManager::CreateMaterial(std::string name, std::string shaderName)
{
    LE3Material material(GetShader(shaderName));
    m_materials[name] = material;
}
LE3Material* LE3AssetManager::GetMaterial(std::string name)
{
    return &m_materials[name];
}