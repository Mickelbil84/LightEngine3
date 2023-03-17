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