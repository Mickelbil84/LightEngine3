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
    LE3Object(name), color(color), intensity(intensity), bEnableShadows(false)
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
glm::mat4 LE3DirectionalLight::GetViewMatrix() const
{
    return glm::lookAt(-10.f * GetDirection(), glm::vec3(0.f), glm::vec3(0.f, 1.f, 0.f));
}
bool LE3DirectionalLight::IsShadowsEnabled() const
{
    return bEnableShadows;
}
void LE3DirectionalLight::SetShadowsEnabled(bool enabled)
{
    bEnableShadows = enabled;
}
LE3ShadowMap& LE3DirectionalLight::GetShadowMap()
{
    return shadowMap;
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

LE3SpotLight::LE3SpotLight(std::string name, glm::vec3 color, float intensity, 
        float cutoff, float outer_cutoff) :
    LE3Object(name), color(color), intensity(intensity), cutoff(cutoff), outer_cutoff(outer_cutoff), bEnableShadows(false)
{
}

void LE3SpotLight::Update(double deltaTime)
{
}
void LE3SpotLight::Draw()
{
}
glm::vec3 LE3SpotLight::GetColor() const
{
    return this->color;
}
void LE3SpotLight::SetColor(glm::vec3 color)
{
    this->color = color;
}

float LE3SpotLight::GetIntensity() const
{
    return this->intensity;
}
void LE3SpotLight::SetIntensity(float intensity)
{
    this->intensity = intensity;
}

float LE3SpotLight::GetCutoff() const
{
    return this->cutoff;
}
float LE3SpotLight::GetOuterCutoff() const
{
    return this->outer_cutoff;
}
void LE3SpotLight::SetCutoff(float cutoff)
{
    this->cutoff = cutoff;
}
void LE3SpotLight::SetOuterCutoff(float outer_cutoff)
{
    this->outer_cutoff = cutoff;
}

glm::vec3 LE3SpotLight::GetDirection() const
{
    glm::vec3 dir = this->GetModelMatrix() * glm::vec4(g_DefaultLightDirection, 0.f);
    return dir;
}
bool LE3SpotLight::IsShadowsEnabled() const
{
    return bEnableShadows;
}
void LE3SpotLight::SetShadowsEnabled(bool enabled)
{
    bEnableShadows = enabled;
}
LE3ShadowMap& LE3SpotLight::GetShadowMap()
{
    return shadowMap;
}