#include "le3_light.h"

#include <fmt/core.h>

LE3AmbientLight::LE3AmbientLight(glm::vec3 color, float intensity) : LE3Object("ambient_light"), color(color), intensity(intensity)
{
}
void LE3AmbientLight::Update(double deltaTime)
{
}
void LE3AmbientLight::Draw()
{
}
glm::vec3 LE3AmbientLight::GetColor() const
{
    return this->color;
}
void LE3AmbientLight::SetColor(glm::vec3 color)
{
    this->color = color;
}

float LE3AmbientLight::GetIntensity() const
{
    return this->intensity;
}
void LE3AmbientLight::SetIntensity(float intensity)
{
    this->intensity = intensity;
}


LE3DirectionalLight::LE3DirectionalLight(std::string name, glm::vec3 color, float intensity) : 
    LE3Object(name), color(color), intensity(intensity)
{
}
void LE3DirectionalLight::Update(double deltaTime)
{
}
void LE3DirectionalLight::Draw()
{
}
glm::vec3 LE3DirectionalLight::GetColor() const
{
    return this->color;
}
void LE3DirectionalLight::SetColor(glm::vec3 color)
{
    this->color = color;
}

float LE3DirectionalLight::GetIntensity() const
{
    return this->intensity;
}
void LE3DirectionalLight::SetIntensity(float intensity)
{
    this->intensity = intensity;
}
glm::vec3 LE3DirectionalLight::GetDirection() const
{
    glm::vec3 dir = this->GetModelMatrix() * glm::vec4(g_DefaultLightDirection, 0.f);
    return dir;
}


LE3PointLight::LE3PointLight(std::string name, glm::vec3 color, float intensity, float attn_const, float attn_linear, float attn_exp) : 
    LE3Object(name), color(color), intensity(intensity), attn_const(attn_const), attn_linear(attn_linear), attn_exp(attn_exp)
{
}
void LE3PointLight::Update(double deltaTime)
{
}
void LE3PointLight::Draw()
{
}
glm::vec3 LE3PointLight::GetColor() const
{
    return this->color;
}
void LE3PointLight::SetColor(glm::vec3 color)
{
    this->color = color;
}

float LE3PointLight::GetIntensity() const
{
    return this->intensity;
}
void LE3PointLight::SetIntensity(float intensity)
{
    this->intensity = intensity;
}
float LE3PointLight::GetAttenuationConst() const
{
    return this->attn_const;
}
float LE3PointLight::GetAttenuationLinear() const
{
    return this->attn_linear;
}
float LE3PointLight::GetAttenuationExp() const
{
    return this->attn_exp;
}
void LE3PointLight::SetAttenuationConst(float attn_const)
{
    this->attn_const = attn_const;
}
void LE3PointLight::SetAttenuationLinear(float attn_linear)
{
    this->attn_linear = attn_linear;
}
void LE3PointLight::SetAttenuationExp(float attn_exp)
{
    this->attn_exp = attn_exp;
}