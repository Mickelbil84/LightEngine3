#include "le3_light_manager.h"

#include <fmt/core.h>

std::shared_ptr<LE3AmbientLight> LE3LightManager::GetAmbientLight() const
{
    return this->m_pAmbientLight;
}
void LE3LightManager::SetAmbientLight(std::shared_ptr<LE3AmbientLight> ambientLight)
{
    this->m_pAmbientLight = ambientLight;
}
void LE3LightManager::AddDirectionalLight(std::shared_ptr<LE3DirectionalLight> directionalLight)
{
    this->m_directionalLights.push_back(directionalLight);
}

void LE3LightManager::RenderLights(LE3Shader* shader)
{
    RenderAmbientLight(shader);
    RenderDirectionalLights(shader);
}

void LE3LightManager::RenderAmbientLight(LE3Shader* shader)
{
    shader->Uniform("ambientLight.color", m_pAmbientLight->GetColor());
    shader->Uniform("ambientLight.intensity", m_pAmbientLight->GetIntensity());
}

void LE3LightManager::RenderDirectionalLights(LE3Shader* shader)
{
    for (int i = 0; i < m_directionalLights.size(); i++)
    {
        shader->Uniform(fmt::format("directionalLights[{}].color", i), m_directionalLights[i]->GetColor());
        shader->Uniform(fmt::format("directionalLights[{}].intensity", i), m_directionalLights[i]->GetIntensity());
        shader->Uniform(fmt::format("directionalLights[{}].direction", i), m_directionalLights[i]->GetDirection());
    }
}