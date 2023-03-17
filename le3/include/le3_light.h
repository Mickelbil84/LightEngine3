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
    LE3AmbientLight(glm::vec3 color = glm::vec3(1.f), float intensity=0.1f);

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
    LE3DirectionalLight(std::string name = "", glm::vec3 color = glm::vec3(1.f), float intensity=0.1f);

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

CEREAL_REGISTER_TYPE(LE3AmbientLight);
CEREAL_REGISTER_POLYMORPHIC_RELATION(LE3Object, LE3AmbientLight);
CEREAL_REGISTER_TYPE(LE3DirectionalLight);
CEREAL_REGISTER_POLYMORPHIC_RELATION(LE3Object, LE3DirectionalLight);
