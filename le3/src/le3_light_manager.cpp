#include "le3_light_manager.h"

std::shared_ptr<LE3AmbientLight> LE3LightManager::GetAmbientLight() const
{
    return this->m_pAmbientLight;
}
void LE3LightManager::SetAmbientLight(std::shared_ptr<LE3AmbientLight> ambientLight)
{
    this->m_pAmbientLight = ambientLight;
}

void LE3LightManager::RenderLights(LE3Shader* shader)
{
    RenderAmbientLight(shader);
}

void LE3LightManager::RenderAmbientLight(LE3Shader* shader)
{
    shader->Uniform("ambientLight.color", m_pAmbientLight->GetColor());
    shader->Uniform("ambientLight.intensity", m_pAmbientLight->GetIntensity());
}