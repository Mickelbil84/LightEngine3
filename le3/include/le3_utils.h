#pragma once

#include <cereal/cereal.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace glm
{
    template <class Archive>
    void serialize(Archive & ar, vec2 & v)
    {
        ar(CEREAL_NVP(v.x), CEREAL_NVP(v.y));
    }

    template <class Archive>
    void serialize(Archive & ar, vec3 & v)
    {
        ar(CEREAL_NVP(v.x), CEREAL_NVP(v.y), CEREAL_NVP(v.z));
    }

    template <class Archive>
    void serialize(Archive & ar, vec4 & v)
    {
        ar(CEREAL_NVP(v.x), CEREAL_NVP(v.y), CEREAL_NVP(v.z), CEREAL_NVP(v.w));
    }

    template <class Archive>
    void serialize(Archive & ar, mat4 & m)
    {
        ar(CEREAL_NVP(m[0][0]), CEREAL_NVP(m[0][1]), CEREAL_NVP(m[0][2]), CEREAL_NVP(m[0][3]));
        ar(CEREAL_NVP(m[1][0]), CEREAL_NVP(m[1][1]), CEREAL_NVP(m[1][2]), CEREAL_NVP(m[1][3]));
        ar(CEREAL_NVP(m[2][0]), CEREAL_NVP(m[2][1]), CEREAL_NVP(m[2][2]), CEREAL_NVP(m[2][3]));
        ar(CEREAL_NVP(m[3][0]), CEREAL_NVP(m[3][1]), CEREAL_NVP(m[3][2]), CEREAL_NVP(m[3][3]));
    }
};


inline glm::mat4 aiMatrix4x4toGLM(aiMatrix4x4& mtx)
{
    glm::mat4 glmMtx;
    glmMtx[0][0] = mtx.a1; glmMtx[1][0] = mtx.a2; glmMtx[2][0] = mtx.a3; glmMtx[3][0] = mtx.a4;
    glmMtx[0][1] = mtx.b1; glmMtx[1][1] = mtx.b2; glmMtx[2][1] = mtx.b3; glmMtx[3][1] = mtx.b4;
    glmMtx[0][2] = mtx.c1; glmMtx[1][2] = mtx.c2; glmMtx[2][2] = mtx.c3; glmMtx[3][2] = mtx.c4;
    glmMtx[0][3] = mtx.d1; glmMtx[1][3] = mtx.d2; glmMtx[2][3] = mtx.d3; glmMtx[3][3] = mtx.d4;
    return glmMtx;  
};