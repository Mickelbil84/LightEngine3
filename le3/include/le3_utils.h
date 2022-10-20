#pragma once

#include <cereal/cereal.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

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
