#include "le3_scene.h"
using namespace le3;

#include <stdexcept>

#ifdef __linux__
#include <GL/glew.h>
#else
#include <gl/glew.h>
#endif

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "le3_engine_systems.h"

#include <fmt/core.h>

void AssimpSceneToVertexBuffer(std::vector<LE3Vertex>& buffer, std::vector<GLuint>& indices, aiNode* node, const aiScene* scene);
void AssimpSkeletalSceneToVertexBuffer(std::vector<LE3VertexSkeletal>& buffer, std::vector<GLuint>& indices, LE3Skeleton& skeleton, aiNode* node, const aiScene* scene);
void AssimpGetNodeVector(aiNode* node, std::vector<aiNode*>& nodes);
void AssimpSkeletonHierarchy(LE3Skeleton& skeleton, std::vector<aiNode*> nodes);
void AssimpSkeletalAddBoneWeights(aiMesh* mesh, LE3Skeleton& skeleton, std::vector<LE3VertexSkeletal>& vertices, int buffer_offset);

void _DBG_SkeletalPrint(LE3Skeleton& skeleton);
void _DBG_aiScenePrint(const aiScene* scene);

inline glm::mat4 aiMatrix4x4toGLM(aiMatrix4x4& mtx)
{
    glm::mat4 glmMtx;
    glmMtx[0][0] = mtx.a1; glmMtx[1][0] = mtx.a2; glmMtx[2][0] = mtx.a3; glmMtx[3][0] = mtx.a4;
    glmMtx[0][1] = mtx.b1; glmMtx[1][1] = mtx.b2; glmMtx[2][1] = mtx.b3; glmMtx[3][1] = mtx.b4;
    glmMtx[0][2] = mtx.c1; glmMtx[1][2] = mtx.c2; glmMtx[2][2] = mtx.c3; glmMtx[3][2] = mtx.c4;
    glmMtx[0][3] = mtx.d1; glmMtx[1][3] = mtx.d2; glmMtx[2][3] = mtx.d3; glmMtx[3][3] = mtx.d4;
    return glmMtx;  
};

// ------------------------------------------------


LE3StaticMeshPtr LE3AssetManager::loadStaticMesh(std::string filename, bool keepData) {
    LE3StaticMeshPtr mesh;

    LE3DatBuffer data = LE3GetDatFileSystem().getFileContent(filename);

    Assimp::Importer importer;
    // const aiScene* scene = importer.ReadFile(filename,
    //     aiProcess_FlipUVs |
    //     aiProcess_Triangulate | 
    //     aiProcess_CalcTangentSpace
    // );
    const aiScene* scene = importer.ReadFileFromMemory(&data.data[0], data.data.size(), 
        aiProcess_FlipUVs |
        aiProcess_Triangulate | 
        aiProcess_CalcTangentSpace
    );
    if (!scene) throw std::runtime_error(fmt::format("Could not load static mesh: {}", filename));

    std::vector<LE3Vertex> buffer;
    std::vector<GLuint> indices; 
    AssimpSceneToVertexBuffer(buffer, indices, scene->mRootNode, scene);

    return std::make_shared<LE3StaticMesh>(buffer, indices, keepData);
}

LE3SkeletalMeshPtr LE3AssetManager::loadSkeletalMesh(std::string meshPath)
{
    Assimp::Importer importer;
    LE3DatBuffer data = LE3GetDatFileSystem().getFileContent(meshPath);
    const aiScene* scene = importer.ReadFileFromMemory(&data.data[0], data.data.size(), 
        aiProcess_FlipUVs |
        aiProcess_Triangulate | 
        aiProcess_CalcTangentSpace
    );
    if (!scene) throw std::runtime_error(fmt::format("Could not load skeletal mesh: {}", meshPath));

    std::vector<LE3VertexSkeletal> buffer;
    std::vector<GLuint> indices;

    LE3Skeleton skeleton;
    skeleton.m_globalInverseTransform = glm::inverse(aiMatrix4x4toGLM(scene->mRootNode->mTransformation));

    AssimpSkeletalSceneToVertexBuffer(buffer, indices, skeleton, scene->mRootNode, scene);

    std::vector<aiNode*> nodes;
    AssimpGetNodeVector(scene->mRootNode, nodes);
    AssimpSkeletonHierarchy(skeleton, nodes);

    // _DBG_SkeletalPrint(skeleton);
    // _DBG_aiScenePrint(scene);

    LE3SkeletalMeshPtr mesh = std::make_shared<LE3SkeletalMesh>(buffer, indices);
    mesh->setSkeleton(skeleton);
    return mesh;
}

// -----------------------------------------------------------------------------

void AssimpSceneToVertexBuffer(std::vector<LE3Vertex>& buffer, std::vector<GLuint>& indices, aiNode* node, const aiScene* scene) {
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
            skeleton.addBone(boneName);
            skeleton.getBone(boneName)->offset = aiMatrix4x4toGLM(bone->mOffsetMatrix);
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
                    vertices[vertexId].bones[k] = skeleton.getBone(boneName)->id;
                    vertices[vertexId].weights[k] = vertexWeight.mWeight;
                }
                else
                {
                    if (vertices[vertexId].bones2[k-4] >= 0) continue;
                    vertices[vertexId].bones2[k-4] = skeleton.getBone(boneName)->id;
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
                bone->parent = skeleton.getBone(std::string(node->mParent->mName.C_Str()));
                break;
            }
        }
    }
}

void _DBG_SkeletalPrint(LE3Skeleton& skeleton)
{
    fmt::print("m_globalInverseTransform:\n");
    // printMatrix(skeleton.m_globalInverseTransform);
    fmt::print("\n");

    for (auto bone : skeleton.m_bones)
    {
        fmt::print("Bone: {}\n", bone->name);
        // printMatrix(bone->offset);
        fmt::print("\n");
    }
    fmt::print("\n");
}

void _DBG_aiScenePrint(const aiScene* scene)
{
    fmt::print("Num Animations: {}\n\n", scene->mNumAnimations);

    aiAnimation* animation = scene->mAnimations[0];
    fmt::print("Animation Metadata:\n");
    fmt::print("\tDuration = {}\n", animation->mDuration);
    fmt::print("\tName = {}\n", animation->mName.C_Str());
    fmt::print("\tNum Channels = {}\n", animation->mNumChannels);
    fmt::print("\tTicks Per Second = {}\n", animation->mTicksPerSecond);

    aiNodeAnim* nodeAnim = animation->mChannels[1];
    fmt::print("\nNode 1:\n");
    fmt::print("\tName = {}\n", nodeAnim->mNodeName.C_Str());
    fmt::print("\tNum Position Keys = {}\n", nodeAnim->mNumPositionKeys);
    fmt::print("\tNum Rotation Keys = {}\n", nodeAnim->mNumRotationKeys);
    fmt::print("\tNum Scale Keys = {}\n", nodeAnim->mNumScalingKeys);
}

void LE3AssetManager::addSkeletalAnimation(std::string name, std::string animationPath, std::string meshName) {
    LE3SkeletalMeshPtr mesh = getSkeletalMesh(meshName);

    Assimp::Importer importer;
    LE3DatBuffer data = LE3GetDatFileSystem().getFileContent(animationPath);
    const aiScene* scene = importer.ReadFileFromMemory(&data.data[0], data.data.size(), 
        aiProcess_FlipUVs |
        aiProcess_Triangulate | 
        aiProcess_CalcTangentSpace
    );
    if (!scene) throw std::runtime_error(fmt::format("Could not load animation: {}", animationPath));

    // Load Animations (currently only the first one)
    for (int i = 0; i < scene->mNumAnimations; ++i) {
        LE3AnimationTrack animTrack;
        animTrack.skeleton = &mesh->getSkeleton();
        animTrack.loadAnimationTrack(scene, i);
        mesh->addAnimationTrack(name, animTrack);
        break;
    }
}

// void LE3AssetManager::AddAnimationPath(std::string name, std::string animationPath, std::string skeletalMeshName)
// {
//     LE3AnimationPath ap;
//     ap.path = animationPath;
//     ap.skeletalMeshName = skeletalMeshName;
//     ap.bIsLoaded = false;
//     m_animationPaths[name] = ap;
// }
// void LE3AssetManager::LoadAnimations(std::string animationName)
// {
//     LE3AnimationPath ap = m_animationPaths[animationName];
//     LE3Mesh<LE3VertexSkeletal>* mesh = GetSkeletalMesh(ap.skeletalMeshName);
//     if (!mesh) return;

//     Assimp::Importer importer;
//     const aiScene* scene = importer.ReadFile(ap.path, 
//         aiProcess_FlipUVs |
//         aiProcess_Triangulate |
//         aiProcess_CalcTangentSpace
//         );
//     if (!scene)
//     {
//         #ifndef NDEBUG
//         PrintTitle("Load Animation Error");
//         std::cout << "Failed loading animation:\t" << ap.path << std::endl;
//         #endif
//         return;
//     }

//     // Load Animations
//     for (int i = 0; i < scene->mNumAnimations; ++i)
//     {
//         LE3AnimationTrack animTrack(&mesh->m_skeleton);
//         animTrack.LoadAnimationTrack(scene, i);
//         mesh->m_animationTracks[animationName] = animTrack;
//         break;
//     }
// }