#pragma once

#include <map>
#include <string>

#include "le3_mesh.h"
#include "le3_shader.h"
#include "le3_texture.h"
#include "le3_material.h"

struct LE3AssetPath
{
    std::string path;
    bool bIsLoaded;
};

class LE3AssetManager
{
public:
    void AddMeshPath(std::string name, std::string meshPath);
    void LoadMesh(std::string name, std::vector<LE3Vertex> data);
    void LoadMesh(std::string name, std::string meshPath);
    LE3Mesh<LE3Vertex>* GetMesh(std::string name);

    void AddTexturePath(std::string name, std::string texturePath);
    void LoadTexture(std::string name, std::string texturePath);
    LE3Texture* GetTexture(std::string name);

    void LoadShader(std::string name, std::string vertexShaderPath, std::string fragmentShaderPath);
    LE3Shader* GetShader(std::string name);


    void CreateMaterial(std::string name, std::string shaderName);
    LE3Material* GetMaterial(std::string name);

    /*
    *  Meshes and Textures can also be added lazily, and loaded on demand
    */
    std::map<std::string, LE3AssetPath> m_meshesPaths;
    std::map<std::string, LE3AssetPath> m_texturesPaths;

    std::map<std::string, LE3Mesh<LE3Vertex>> m_meshes;
    std::map<std::string, LE3Shader> m_shaders;
    std::map<std::string, LE3Texture> m_textures;
    std::map<std::string, LE3Material> m_materials;
};