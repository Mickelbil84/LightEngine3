#include "le3_asset_manager.h"
#include "le3_print.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

const char* gTokenBox = "BOX";

LE3AssetPath::LE3AssetPath() :
    path(""),
    bIsLoaded(false)
{

}

LE3ShaderPath::LE3ShaderPath() :
    vertexShaderPath(""),
    fragmentShaderPath(""),
    bIsLoaded(false)
{

}

void AssimpSceneToVertexBuffer(std::vector<LE3Vertex>& buffer, std::vector<GLuint>& indices, aiNode* node, const aiScene* scene);

void LE3AssetManager::AddMeshPath(std::string name, std::string meshPath)
{
    LE3AssetPath ap;
    ap.path = meshPath;
    ap.bIsLoaded = false;
    m_meshesPaths[name] = ap;
}

void LE3AssetManager::LoadMesh(std::string name, std::vector<LE3Vertex> data)
{
    LE3Mesh<LE3Vertex> mesh;
    mesh.LoadMeshData(data);
    m_meshes[name] = mesh;
}

void LE3AssetManager::LoadMesh(std::string name, std::string meshPath)
{
    if (meshPath[0] == gPrimitivePathPrefix)
    {
        LoadMeshPrimitive(name, meshPath);
        return;
    }

    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(meshPath, 
        aiProcess_FlipUVs |
        aiProcess_Triangulate
        );
    if (!scene)
    {
        #ifndef NDEBUG
        PrintTitle("Load Mesh Error");
        std::cout << "Failed loading mesh:\t" << meshPath << std::endl;
        #endif
        return;
    }

    std::vector<LE3Vertex> buffer;
    std::vector<GLuint> indices;
    AssimpSceneToVertexBuffer(buffer, indices, scene->mRootNode, scene);

    LE3Mesh<LE3Vertex> mesh;
    mesh.LoadMeshDataIndexed(buffer, indices);
    m_meshes[name] = mesh;

    AddMeshPath(name, meshPath);
    m_meshesPaths[name].bIsLoaded = true;
}

void LE3AssetManager::LoadMeshPrimitive(std::string name, std::string primitiveDescription)
{
    std::vector<LE3Vertex> data;
    
    int i = 1;
    std::vector<float> params;
    std::string token, tmp;
    bool bTokenDone = false;
    while (i < primitiveDescription.size())
    {
        if (primitiveDescription[i] == gPrimitivePathDelimiter)
        {
            if (!bTokenDone)
            {
                token = tmp;
                bTokenDone = true;
            }
            else
            {
                params.push_back(std::stof(tmp));
            }
            tmp = "";
        }
        else
        {
            tmp += primitiveDescription[i];
        }
        i++;
    }

    if (token == gTokenBox)
    {
        AddBox(data, params[0], params[1], params[2], params[3], params[4], params[5]);
    }
    else
    {
        #ifndef NDEBUG
        PrintTitle("Primitive mesh error");
        std::cout << "Could not find token '" << token << "'." << std::endl;
        #endif
    }

    LE3Mesh<LE3Vertex> mesh;
    mesh.LoadMeshData(data);
    m_meshes[name] = mesh;

    AddMeshPath(name, primitiveDescription);
    m_meshesPaths[name].bIsLoaded = true;
}

void AssimpSceneToVertexBuffer(std::vector<LE3Vertex>& buffer, std::vector<GLuint>& indices, aiNode* node, const aiScene* scene)
{
    for (unsigned int i = 0; i < node->mNumMeshes; ++i)
    {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        for (unsigned int j = 0; j < mesh->mNumVertices; ++j)
        {
            LE3Vertex vertex;
            vertex.position[0] = mesh->mVertices[j].x;
            vertex.position[1] = mesh->mVertices[j].y;
            vertex.position[2] = mesh->mVertices[j].z;
            if (mesh->mTextureCoords[0])
            {
                vertex.uv[0] = mesh->mTextureCoords[0][j].x;
                vertex.uv[1] = mesh->mTextureCoords[0][j].y;
            }
            else
            {
                vertex.uv[0] = vertex.uv[1] = 0.f;
            }
            vertex.normal[0] = mesh->mNormals[j].x;
            vertex.normal[1] = mesh->mNormals[j].y;
            vertex.normal[2] = mesh->mNormals[j].z;
            buffer.push_back(vertex);
        }
        for (unsigned int j = 0; j < mesh->mNumFaces; ++j)
        {
            aiFace face = mesh->mFaces[j];
            for (unsigned int k = 0; k < face.mNumIndices; ++k)
                indices.push_back(face.mIndices[k]);
        }
    }

    for (unsigned int i = 0; i < node->mNumChildren; ++i)
        AssimpSceneToVertexBuffer(buffer, indices, node->mChildren[i], scene);
}

LE3Mesh<LE3Vertex>* LE3AssetManager::GetMesh(std::string name)
{
    LE3AssetPath& ap = m_meshesPaths[name];
    if (!ap.bIsLoaded && ap.path.size() > 0)
    {
        LoadMesh(name, ap.path);
        ap.bIsLoaded = true;
    }

    return &m_meshes[name];
    
}

void LE3AssetManager::AddShaderPath(std::string name, std::string vertexShaderPath, std::string fragmentShaderPath)
{
    LE3ShaderPath sp;
    sp.vertexShaderPath = vertexShaderPath;
    sp.fragmentShaderPath = fragmentShaderPath;
    sp.bIsLoaded = false;
    m_shadersPaths[name] = sp;
}
void LE3AssetManager::LoadShader(std::string name, std::string vertexShaderPath, std::string fragmentShaderPath)
{
    LE3Shader shader;
    shader.CompileShader(vertexShaderPath, fragmentShaderPath);
    shader.SetName(name);
    m_shaders[name] = shader;
    AddShaderPath(name, vertexShaderPath, fragmentShaderPath);
    m_shadersPaths[name].bIsLoaded = true;
}
LE3Shader* LE3AssetManager::GetShader(std::string name)
{
    LE3ShaderPath& sp = m_shadersPaths[name];
    if (!sp.bIsLoaded)
    {
        LoadShader(name, sp.vertexShaderPath, sp.fragmentShaderPath);
        sp.bIsLoaded = true;
    }

    return &m_shaders[name];
}

void LE3AssetManager::AddTexturePath(std::string name, std::string texturePath)
{
    LE3AssetPath ap;
    ap.path = texturePath;
    ap.bIsLoaded = false;
    m_texturesPaths[name] = ap;
}

void LE3AssetManager::LoadTexture(std::string name, std::string texturePath)
{
    LE3Texture texture;
    texture.Load(texturePath);
    texture.SetName(name);
    m_textures[name] = texture;
    AddTexturePath(name, texturePath);
    m_texturesPaths[name].bIsLoaded = true;
}
LE3Texture* LE3AssetManager::GetTexture(std::string name)
{
    if (!name.size())
        return nullptr;
    LE3AssetPath& ap = m_texturesPaths[name];
    if (!ap.bIsLoaded)
    {
        LoadTexture(name, ap.path);
        ap.bIsLoaded = true;
    }

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