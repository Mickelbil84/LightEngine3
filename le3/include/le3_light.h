#pragma once
#include "le3_object.h"

#include <cereal/cereal.hpp>

#define MAX_DIRECTIONAL_LIGHTS 4
#define MAX_POINT_LIGHTS 16
#define MAX_SPOT_LIGHTS 16

const glm::vec3 g_DefaultLightDirection = glm::vec3(0.f, -1.f, 0.f);

class LE3AmbientLight : public LE3Object
{
public:
    LE3AmbientLight(glm::vec3 color = glm::vec3(1.f), float intensity = 0.1f);

    virtual void Update(double deltaTime);
    virtual void Draw();

    template <typename Archive>
    void serialize( Archive & ar )
    {
        LE3Object::serialize(ar);
        ar(CEREAL_NVP(color), CEREAL_NVP(intensity));
    }

    glm::vec3 GetColor() const;
    void SetColor(glm::vec3 color);
    
    float GetIntensity() const;
    void SetIntensity(float intensity);

protected:
    glm::vec3 color;
    float intensity;
};

class LE3DirectionalLight : public LE3Object
{
public:
    LE3DirectionalLight(std::string name = "", glm::vec3 color = glm::vec3(1.f), float intensity = 0.1f);

    virtual void Update(double deltaTime);
    virtual void Draw();

    template <typename Archive>
    void serialize( Archive & ar )
    {
        LE3Object::serialize(ar);
        ar(CEREAL_NVP(color), CEREAL_NVP(intensity));
    }

    glm::vec3 GetColor() const;
    void SetColor(glm::vec3 color);
    
    float GetIntensity() const;
    void SetIntensity(float intensity);

    glm::vec3 GetDirection() const;

protected:
    glm::vec3 color;
    float intensity;
};

class LE3PointLight : public LE3Object
{
public:
    LE3PointLight(std::string name = "", glm::vec3 color = glm::vec3(1.f), float intensity = 0.1f, 
        float attn_const = 1.f, float attn_linear = 0.09f, float attn_exp = 0.032f);

    virtual void Update(double deltaTime);
    virtual void Draw();

    template <typename Archive>
    void serialize( Archive & ar )
    {
        LE3Object::serialize(ar);
        ar(CEREAL_NVP(color), CEREAL_NVP(intensity));
        ar(CEREAL_NVP(attn_const), CEREAL_NVP(attn_linear), CEREAL_NVP(attn_exp));
    }

    glm::vec3 GetColor() const;
    void SetColor(glm::vec3 color);
    
    float GetIntensity() const;
    void SetIntensity(float intensity);

    float GetAttenuationConst() const;
    float GetAttenuationLinear() const;
    float GetAttenuationExp() const;
    void SetAttenuationConst(float attn_const);
    void SetAttenuationLinear(float attn_linear);
    void SetAttenuationExp(float attn_exp);

protected:
    glm::vec3 color;
    float intensity;
    float attn_const, attn_linear, attn_exp;
};

CEREAL_REGISTER_TYPE(LE3AmbientLight);
CEREAL_REGISTER_POLYMORPHIC_RELATION(LE3Object, LE3AmbientLight);
CEREAL_REGISTER_TYPE(LE3DirectionalLight);
CEREAL_REGISTER_POLYMORPHIC_RELATION(LE3Object, LE3DirectionalLight);
CEREAL_REGISTER_TYPE(LE3PointLight);
CEREAL_REGISTER_POLYMORPHIC_RELATION(LE3Object, LE3PointLight);