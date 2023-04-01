#include "le3_asset_manager.h"
#include "le3_print.h"
#include "le3_utils.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <fmt/core.h>
using fmt::print;

const char* gTokenBox = "BOX";
const char* gTokenCylinder = "CYL";
const char* gTokenCone = "CON";
const char* gTokenTorus = "TOR";
const char* gTokenSphere = "SPH";

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

LE3AnimationPath::LE3AnimationPath() :
    path(""),
    skeletalMeshName(""),
    bIsLoaded(false)
{
}

void AssimpSceneToVertexBuffer(std::vector<LE3Vertex>& buffer, std::vector<GLuint>& indices, aiNode* node, const aiScene* scene);
void AssimpSkeletalSceneToVertexBuffer(std::vector<LE3VertexSkeletal>& buffer, std::vector<GLuint>& indices, LE3Skeleton& skeleton, aiNode* node, const aiScene* scene);
void AssimpGetNodeVector(aiNode* node, std::vector<aiNode*>& nodes);
void AssimpSkeletonHierarchy(LE3Skeleton& skeleton, std::vector<aiNode*> nodes);
void AssimpSkeletalAddBoneWeights(aiMesh* mesh, LE3Skeleton& skeleton, std::vector<LE3VertexSkeletal>& vertices, int buffer_offset);
void _DBG_SkeletalPrint(LE3Skeleton& skeleton);
void _DBG_aiScenePrint(const aiScene* scene);

LE3PrimitiveTokens ParsePrimitivePath(std::string primitiveDescription)
{
    int i = 1;
    LE3PrimitiveTokens res;
    std::string tmp;
    bool bTokenDone = false;
    while (i < primitiveDescription.size())
    {
        if (primitiveDescription[i] == gPrimitivePathDelimiter)
        {
            if (!bTokenDone)
            {
                res.token = tmp;
                bTokenDone = true;
            }
            else
                res.params.push_back(std::stof(tmp));
            tmp = "";
        }
        else
            tmp += primitiveDescription[i];
        i++;
    }
    return res;
}

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
        aiProcess_Triangulate |
        aiProcess_CalcTangentSpace
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
    
    LE3PrimitiveTokens tokens = ParsePrimitivePath(primitiveDescription);
    if (tokens.token == gTokenBox)
    {
        AddBox(data, tokens.params[0], tokens.params[1], tokens.params[2], tokens.params[3], tokens.params[4], tokens.params[5]);
    }
    else if (tokens.token == gTokenCylinder)
    {
        if (tokens.params.size() < 7)
            AddCylinder(data, tokens.params[0], tokens.params[1], tokens.params[2], tokens.params[3], tokens.params[4], (GLushort)tokens.params[5]);
        else 
            AddCylinder(data, tokens.params[0], tokens.params[1], tokens.params[2], tokens.params[3], tokens.params[4], (GLushort)tokens.params[5], (GLushort)tokens.params[6]);
    }
    else if (tokens.token == gTokenCone)
    {
        AddCone(data, tokens.params[0], tokens.params[1], tokens.params[2], tokens.params[3], tokens.params[4], (GLushort)tokens.params[5]);
    }
    else if (tokens.token == gTokenTorus)
    {
        AddTorus(data, tokens.params[0], tokens.params[1], tokens.params[2], tokens.params[3], tokens.params[4], (GLushort)tokens.params[5]);
    }
    else if (tokens.token == gTokenSphere)
    {
        AddSphere(data, tokens.params[0], tokens.params[1], tokens.params[2], tokens.params[3], (GLushort)tokens.params[4]);
    }
    else
    {
        #ifndef NDEBUG
        PrintTitle("Primitive mesh error");
        std::cout << "Could not find token '" << tokens.token << "'." << std::endl;
        #endif
    }

    LE3Mesh<LE3Vertex> mesh;
    mesh.LoadMeshData(data);
    m_meshes[name] = mesh;

    AddMeshPath(name, primitiveDescription);
    m_meshesPaths[name].bIsLoaded = true;
}

void LE3AssetManager::AddSkeletalMeshPath(std::string name, std::string meshPath)
{
    LE3AssetPath ap;
    ap.path = meshPath;
    ap.bIsLoaded = false;
    m_skeletalMeshesPaths[name] = ap;
}
LE3Mesh<LE3VertexSkeletal>* LE3AssetManager::GetSkeletalMesh(std::string name)
{
    LE3AssetPath& ap = m_skeletalMeshesPaths[name];
    if (!ap.bIsLoaded && ap.path.size() > 0)
    {
        LoadSkeletalMesh(name, ap.path);
        ap.bIsLoaded = true;
    }

    return &m_skeletalMeshes[name];
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

void LE3AssetManager::Clear()
{
    m_meshesPaths.clear();
    m_texturesPaths.clear();
    m_shadersPaths.clear();

    m_meshes.clear();
    m_shaders.clear();
    m_textures.clear();
    m_materials.clear();
}

// ---------------------------------------------------------------------------

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
            vertex.tangent[0] = mesh->mTangents[j].x;
            vertex.tangent[1] = mesh->mTangents[j].y;
            vertex.tangent[2] = mesh->mTangents[j].z;
            vertex.bitangent[0] = mesh->mBitangents[j].x;
            vertex.bitangent[1] = mesh->mBitangents[j].y;
            vertex.bitangent[2] = mesh->mBitangents[j].z;
            buffer.push_back(vertex);
        }
        for (unsigned int j = 0; j < mesh->mNumFaces; ++j)
        {
            aiFace face = mesh->mFaces[j];
            for (unsigned int k = 0; k < face.mNumIndices; ++k)
                indices.push_back(buffer.size() - mesh->mNumVertices + face.mIndices[k]);
        }
    }

    for (unsigned int i = 0; i < node->mNumChildren; ++i)
        AssimpSceneToVertexBuffer(buffer, indices, node->mChildren[i], scene);
}

void LE3AssetManager::LoadSkeletalMesh(std::string name, std::string meshPath)
{
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(meshPath, 
        aiProcess_FlipUVs |
        aiProcess_Triangulate |
        aiProcess_CalcTangentSpace
        );
    if (!scene)
    {
        #ifndef NDEBUG
        PrintTitle("Load Mesh Error");
        std::cout << "Failed loading mesh:\t" << meshPath << std::endl;
        #endif
        return;
    }

    std::vector<LE3VertexSkeletal> buffer;
    std::vector<GLuint> indices;
    LE3Mesh<LE3VertexSkeletal> mesh;
    mesh.m_skeleton.m_globalInverseTransform = glm::inverse(aiMatrix4x4toGLM(scene->mRootNode->mTransformation));

    AssimpSkeletalSceneToVertexBuffer(buffer, indices, mesh.m_skeleton, scene->mRootNode, scene);

    std::vector<aiNode*> nodes;
    AssimpGetNodeVector(scene->mRootNode, nodes);
    AssimpSkeletonHierarchy(mesh.m_skeleton, nodes);

    // _DBG_SkeletalPrint(mesh.m_skeleton);
    // _DBG_aiScenePrint(scene);

    mesh.LoadMeshDataIndexed(buffer, indices);
    m_skeletalMeshes[name] = mesh;

    AddSkeletalMeshPath(name, meshPath);
    m_skeletalMeshesPaths[name].bIsLoaded = true;

}

void AssimpSkeletalSceneToVertexBuffer(std::vector<LE3VertexSkeletal>& buffer, std::vector<GLuint>& indices, LE3Skeleton& skeleton, aiNode* node, const aiScene* scene)
{
    for (unsigned int i = 0; i < node->mNumMeshes; ++i)
    {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        for (unsigned int j = 0; j < mesh->mNumVertices; ++j)
        {
            LE3VertexSkeletal vertex;
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
            vertex.tangent[0] = mesh->mTangents[j].x;
            vertex.tangent[1] = mesh->mTangents[j].y;
            vertex.tangent[2] = mesh->mTangents[j].z;
            vertex.bitangent[0] = mesh->mBitangents[j].x;
            vertex.bitangent[1] = mesh->mBitangents[j].y;
            vertex.bitangent[2] = mesh->mBitangents[j].z;
            for(int k = 0; k < 4; ++k)
                vertex.bones[k] = -1;
            for(int k = 0; k < 4; ++k)
                vertex.bones2[k] = -1;
            buffer.push_back(vertex);
        }
        for (unsigned int j = 0; j < mesh->mNumFaces; ++j)
        {
            aiFace face = mesh->mFaces[j];
            for (unsigned int k = 0; k < face.mNumIndices; ++k)
                indices.push_back(buffer.size() - mesh->mNumVertices + face.mIndices[k]);
        }
        for (unsigned int j = 0; j < mesh->mNumBones; ++j)
        {
            aiBone* bone = mesh->mBones[j];
            std::string boneName = std::string(bone->mName.C_Str());
            skeleton.AddBone(boneName);
            skeleton.GetBone(boneName)->offset = aiMatrix4x4toGLM(bone->mOffsetMatrix);
        }

        AssimpSkeletalAddBoneWeights(mesh, skeleton, buffer, buffer.size() - mesh->mNumVertices);
    }


    for (unsigned int i = 0; i < node->mNumChildren; ++i)
        AssimpSkeletalSceneToVertexBuffer(buffer, indices, skeleton, node->mChildren[i], scene);
}

void AssimpSkeletalAddBoneWeights(aiMesh* mesh, LE3Skeleton& skeleton, std::vector<LE3VertexSkeletal>& vertices, int buffer_offset)
{
    for (unsigned int i = 0; i < mesh->mNumBones; ++i)
    {
        aiBone* bone = mesh->mBones[i];
        std::string boneName = std::string(bone->mName.C_Str());
        
        for (unsigned int j = 0; j < bone->mNumWeights; ++j)
        {
            aiVertexWeight vertexWeight = bone->mWeights[j];
            GLuint vertexId = vertexWeight.mVertexId + buffer_offset;
            for (unsigned int k = 0; k < MAX_BONES_PER_VERTEX; k++)
            {
                if (k < 4)
                {
                    if (vertices[vertexId].bones[k] >= 0) continue;
                    vertices[vertexId].bones[k] = skeleton.GetBone(boneName)->id;
                    vertices[vertexId].weights[k] = vertexWeight.mWeight;
                }
                else
                {
                    if (vertices[vertexId].bones2[k-4] >= 0) continue;
                    vertices[vertexId].bones2[k-4] = skeleton.GetBone(boneName)->id;
                    vertices[vertexId].weights2[k-4] = vertexWeight.mWeight;
                }
                break;
            }
        }   
    }
}


void AssimpGetNodeVector(aiNode* node, std::vector<aiNode*>& nodes)
{
    if (!node) return;
    nodes.push_back(node);
    for (unsigned int i = 0; i < node->mNumChildren; ++i)
        AssimpGetNodeVector(node->mChildren[i], nodes);
}

void AssimpSkeletonHierarchy(LE3Skeleton& skeleton, std::vector<aiNode*> nodes)
{
    // skeleton.AddBone("_root");
    for (auto bone : skeleton.m_bones)
    {
        // Find the corresponding aiNode
        for (auto node : nodes)
        {
            if ((std::string(node->mName.C_Str()) == bone->name) && node->mParent)
            {
                bone->parent = skeleton.GetBone(std::string(node->mParent->mName.C_Str()));
                break;
            }
        }
    }
}


void _DBG_SkeletalPrint(LE3Skeleton& skeleton)
{
    print("m_globalInverseTransform:\n");
    printMatrix(skeleton.m_globalInverseTransform);
    print("\n");

    for (auto bone : skeleton.m_bones)
    {
        print("Bone: {}\n", bone->name);
        printMatrix(bone->offset);
        print("\n");
    }
    print("\n");
}

void _DBG_aiScenePrint(const aiScene* scene)
{
    print("Num Animations: {}\n\n", scene->mNumAnimations);

    aiAnimation* animation = scene->mAnimations[0];
    print("Animation Metadata:\n");
    print("\tDuration = {}\n", animation->mDuration);
    print("\tName = {}\n", animation->mName.C_Str());
    print("\tNum Channels = {}\n", animation->mNumChannels);
    print("\tTicks Per Second = {}\n", animation->mTicksPerSecond);

    aiNodeAnim* nodeAnim = animation->mChannels[1];
    print("\nNode 1:\n");
    print("\tName = {}\n", nodeAnim->mNodeName.C_Str());
    print("\tNum Position Keys = {}\n", nodeAnim->mNumPositionKeys);
    print("\tNum Rotation Keys = {}\n", nodeAnim->mNumRotationKeys);
    print("\tNum Scale Keys = {}\n", nodeAnim->mNumScalingKeys);
}

void LE3AssetManager::AddAnimationPath(std::string name, std::string animationPath, std::string skeletalMeshName)
{
    LE3AnimationPath ap;
    ap.path = animationPath;
    ap.skeletalMeshName = skeletalMeshName;
    ap.bIsLoaded = false;
    m_animationPaths[name] = ap;
}
void LE3AssetManager::LoadAnimations(std::string animationName)
{
    LE3AnimationPath ap = m_animationPaths[animationName];
    LE3Mesh<LE3VertexSkeletal>* mesh = GetSkeletalMesh(ap.skeletalMeshName);
    if (!mesh) return;

    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(ap.path, 
        aiProcess_FlipUVs |
        aiProcess_Triangulate |
        aiProcess_CalcTangentSpace
        );
    if (!scene)
    {
        #ifndef NDEBUG
        PrintTitle("Load Animation Error");
        std::cout << "Failed loading animation:\t" << ap.path << std::endl;
        #endif
        return;
    }

    // Load Animations
    for (int i = 0; i < scene->mNumAnimations; ++i)
    {
        LE3AnimationTrack animTrack(&mesh->m_skeleton);
        animTrack.LoadAnimationTrack(scene, i);
        mesh->m_animationTracks[animationName] = animTrack;
        break;
    }
}