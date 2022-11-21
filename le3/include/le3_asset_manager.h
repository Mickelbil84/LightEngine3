#pragma once

#include <map>
#include <string>

#include <cereal/cereal.hpp>
#include <cereal/types/map.hpp>
#include <cereal/types/string.hpp>

#include "le3_utils.h"
#include "le3_mesh.h"
#include "le3_shader.h"
#include "le3_texture.h"
#include "le3_material.h"
#include "le3_primitives.h"

const char gPrimitivePathPrefix = '$';
const char gPrimitivePathDelimiter = '_';
extern const char* gTokenBox;
extern const char* gTokenCylinder;

struct LE3PrimitiveTokens
{
    std::string token;
    std::vector<float> params;
};
LE3PrimitiveTokens ParsePrimitivePath(std::string primitiveDescription);

struct LE3AssetPath
{
    LE3AssetPath();

    std::string path;
    bool bIsLoaded;

    template <class Archive>
    void serialize(Archive & ar)
    {
        ar(CEREAL_NVP(path));
    }
};

struct LE3ShaderPath
{
    LE3ShaderPath();

    std::string vertexShaderPath, fragmentShaderPath;
    bool bIsLoaded;

    template <class Archive>
    void serialize(Archive & ar)
    {
        ar(CEREAL_NVP(vertexShaderPath));
        ar(CEREAL_NVP(fragmentShaderPath));
    }
};

class LE3AssetManager
{
public:
    void Clear();

    void AddMeshPath(std::string name, std::string meshPath);
    void LoadMesh(std::string name, std::vector<LE3Vertex> data);
    void LoadMesh(std::string name, std::string meshPath);
    void LoadMeshPrimitive(std::string name, std::string primitiveDescription);
    LE3Mesh<LE3Vertex>* GetMesh(std::string name);

    void AddTexturePath(std::string name, std::string texturePath);
    void LoadTexture(std::string name, std::string texturePath);
    LE3Texture* GetTexture(std::string name);

    void AddShaderPath(std::string name, std::string vertexShaderPath, std::string fragmentShaderPath);
    void LoadShader(std::string name, std::string vertexShaderPath, std::string fragmentShaderPath);
    LE3Shader* GetShader(std::string name);

    void CreateMaterial(std::string name, std::string shaderName);
    LE3Material* GetMaterial(std::string name);

    /*
    *  Meshes and Textures can also be added lazily, and loaded on demand
    */
    std::map<std::string, LE3AssetPath> m_meshesPaths;
    std::map<std::string, LE3AssetPath> m_texturesPaths;
    std::map<std::string, LE3ShaderPath> m_shadersPaths;

    std::map<std::string, LE3Mesh<LE3Vertex>> m_meshes;
    std::map<std::string, LE3Shader> m_shaders;
    std::map<std::string, LE3Texture> m_textures;
    std::map<std::string, LE3Material> m_materials;

    template <class Archive>
    void save( Archive & ar ) const
    {
        ar(CEREAL_NVP(m_meshesPaths));
        ar(CEREAL_NVP(m_texturesPaths));
        ar(CEREAL_NVP(m_shadersPaths));
        ar(CEREAL_NVP(m_materials));
    }

    template <class Archive>
    void load( Archive & ar )
    {
        ar(m_meshesPaths);
        ar(m_texturesPaths);
        ar(m_shadersPaths);
        ar(m_materials);

        for (auto& [name, material] : m_materials)
        {
            material.SetShader(GetShader(material.shaderName));
            if (material.diffuseTextureName.size())
                material.SetDiffuseTexture(GetTexture(material.diffuseTextureName));
        }
    }


};