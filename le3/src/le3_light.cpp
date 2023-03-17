#include "le3_light.h"

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