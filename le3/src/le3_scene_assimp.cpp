#include "le3_scene.h"
using namespace le3;

#include <gl/glew.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "le3_engine_systems.h"

#include <fmt/core.h>
using fmt::format;

void AssimpSceneToVertexBuffer(std::vector<LE3Vertex>& buffer, std::vector<GLuint>& indices, aiNode* node, const aiScene* scene);
// void AssimpSkeletalSceneToVertexBuffer(std::vector<LE3VertexSkeletal>& buffer, std::vector<GLuint>& indices, LE3Skeleton& skeleton, aiNode* node, const aiScene* scene);
// void AssimpGetNodeVector(aiNode* node, std::vector<aiNode*>& nodes);
// void AssimpSkeletonHierarchy(LE3Skeleton& skeleton, std::vector<aiNode*> nodes);
// void AssimpSkeletalAddBoneWeights(aiMesh* mesh, LE3Skeleton& skeleton, std::vector<LE3VertexSkeletal>& vertices, int buffer_offset);

// ------------------------------------------------


LE3StaticMeshPtr LE3Scene::loadStaticMesh(std::string filename) {
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
    if (!scene) throw std::runtime_error(format("Could not load static mesh: {}", filename));

    std::vector<LE3Vertex> buffer;
    std::vector<GLuint> indices; 
    AssimpSceneToVertexBuffer(buffer, indices, scene->mRootNode, scene);

    return std::make_shared<LE3StaticMesh>(buffer, indices);
}

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