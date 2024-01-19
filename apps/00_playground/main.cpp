#include <memory>
#include <string>
#include <queue>
#include <iostream>

#include <fmt/core.h>
using fmt::format, fmt::print;

#include <lua.hpp>
#include <lauxlib.h>
#include <lualib.h>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

inline glm::mat4 aiMatrix4x4toGLM(aiMatrix4x4& mtx)
{
    glm::mat4 glmMtx;
    glmMtx[0][0] = mtx.a1; glmMtx[1][0] = mtx.a2; glmMtx[2][0] = mtx.a3; glmMtx[3][0] = mtx.a4;
    glmMtx[0][1] = mtx.b1; glmMtx[1][1] = mtx.b2; glmMtx[2][1] = mtx.b3; glmMtx[3][1] = mtx.b4;
    glmMtx[0][2] = mtx.c1; glmMtx[1][2] = mtx.c2; glmMtx[2][2] = mtx.c3; glmMtx[3][2] = mtx.c4;
    glmMtx[0][3] = mtx.d1; glmMtx[1][3] = mtx.d2; glmMtx[2][3] = mtx.d3; glmMtx[3][3] = mtx.d4;
    return glmMtx;  
};


int main() {
    Assimp::Importer importer;
    const char* meshPath = "./resources/models/cars/Audi R8.fbx";
    const aiScene* scene = importer.ReadFile(meshPath, 
        aiProcess_FlipUVs | 
        aiProcess_Triangulate | 
        aiProcess_CalcTangentSpace
    );
    if (!scene) throw std::runtime_error("Failed loading mesh.\n");

    std::queue<aiNode*> Q;
    Q.push(scene->mRootNode);
    while (Q.size() > 0) {
        aiNode* node = Q.front(); Q.pop();
        print("Node: {}, #{} children, child of {}, #{} meshes\n", 
            node->mName.C_Str(),
            node->mNumChildren,
            node->mParent ? node->mParent->mName.C_Str() : "--", 
            node->mNumMeshes
        );
        print("{}\n", glm::to_string(aiMatrix4x4toGLM(node->mTransformation)));
        for (int idx = 0; idx < node->mNumChildren; ++idx) Q.push(node->mChildren[idx]);
    }


    return 0;
}