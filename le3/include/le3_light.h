#pragma once

#include "le3_object.h"

namespace le3{
    constexpr int MAX_DIRECTIONAL_LIGHTS = 4;
    constexpr int MAX_POINT_LIGHTS = 8;
    constexpr int MAX_SPOT_LIGHTS = 2;

    const glm::vec3 DEFAULT_LIGHT_DIRECTION = glm::vec3(0.f, -1.f, 0.f);


    class LE3Light : public LE3Object {
    public:
        LE3Light(glm::vec3 color, float intensity) : color(color), intensity(intensity) {}

        inline glm::vec3 getColor() const { return color; }
        inline void setColor(glm::vec3 color) { this->color = color; }

        inline float getIntensity() const { return intensity; }
        inline void setIntensity(float intensity) { this->intensity = intensity; } 

    protected:
        glm::vec3 color;
        float intensity;
    };
    using LE3LightPtr = std::shared_ptr<LE3Light>;

    class LE3AmbientLight : public LE3Light {
    public:
        LE3AmbientLight(glm::vec3 color = glm::vec3(1.f), float intensity=0.1f) : LE3Light(color, intensity) {}
    };
    using LE3AmbientLightPtr = std::shared_ptr<LE3AmbientLight>;

    class LE3DirectionalLight : public LE3Light {
    public:
        LE3DirectionalLight(glm::vec3 color = glm::vec3(1.f), float intensity=0.8f) : LE3Light(color, intensity) {}
        glm::vec3 getDirection() const { return getWorldMatrix() * glm::vec4(DEFAULT_LIGHT_DIRECTION, 0.f); }
    };
    using LE3DirectionalLightPtr = std::shared_ptr<LE3DirectionalLight>;

    class LE3PointLight : public LE3Light {
    public:
        LE3PointLight(glm::vec3 color=glm::vec3(1.f), float intensity=0.8f, 
            float attn_const=1.f, float attn_linear=0.09f, float attn_exp=0.032f) :
            LE3Light(color, intensity), 
            attn_const(attn_const), attn_linear(attn_linear), attn_exp(attn_exp)
        {}

        glm::vec3 getPosition() const { return glm::vec3(getWorldMatrix()[3]); }

        inline float getAttnConst() const { return attn_const; }
        inline float getAttnLinear() const { return attn_linear; }
        inline float getAttnExp() const { return attn_exp; }
        inline void setAttnConst(float attn_const) { this->attn_const = attn_const; }
        inline void setAttnLinear(float attn_linear) { this->attn_linear = attn_linear; }
        inline void setAttnExp(float attn_exp) { this->attn_exp = attn_exp; }

    protected:
        float attn_const, attn_linear, attn_exp;
    };
    using LE3PointLightPtr = std::shared_ptr<LE3PointLight>;

    class LE3SpotLight : public LE3Light {
    public:
        LE3SpotLight(glm::vec3 color=glm::vec3(1.f), float intensity=0.8f, float cutoff=0.91f, float outer_cutoff=0.82f) :
            LE3Light(color, intensity), 
            cutoff(cutoff), outer_cutoff(outer_cutoff)
        {}

        glm::vec3 getDirection() const { return getWorldMatrix() * glm::vec4(DEFAULT_LIGHT_DIRECTION, 0.f); }
        glm::vec3 getPosition() const { return glm::vec3(getWorldMatrix()[3]); }

        inline float getCutoff() const { return cutoff; }
        inline float getOuterCutoff() const { return outer_cutoff; }
        inline void setCutoff(float cutoff) { this->cutoff = cutoff; }
        inline void setOuterCutoff(float outer_cutoff) {this->outer_cutoff = outer_cutoff; }

    protected:
        float cutoff, outer_cutoff;
    };
    using LE3SpotLightPtr = std::shared_ptr<LE3SpotLight>;

}