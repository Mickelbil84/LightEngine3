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
void LE3LightManager::AddPointLight(std::shared_ptr<LE3PointLight> pointLight)
{
    this->m_pointLights.push_back(pointLight);
}
void LE3LightManager::AddSpotLight(std::shared_ptr<LE3SpotLight> spotLight)
{
    this->m_spotLights.push_back(spotLight);
}

void LE3LightManager::RenderLights(LE3Shader* shader)
{
    RenderAmbientLight(shader);
    RenderDirectionalLights(shader);
    RenderPointLights(shader);
    RenderSpotLights(shader);
}

void LE3LightManager::RenderAmbientLight(LE3Shader* shader)
{
    if (!m_pAmbientLight) return;
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

void LE3LightManager::RenderPointLights(LE3Shader* shader)
{
    for (int i = 0; i < m_pointLights.size(); i++)
    {
        shader->Uniform(fmt::format("pointLights[{}].color", i), m_pointLights[i]->GetColor());
        shader->Uniform(fmt::format("pointLights[{}].intensity", i), m_pointLights[i]->GetIntensity());
        shader->Uniform(fmt::format("pointLights[{}].position", i), m_pointLights[i]->GetGlobalPosition());
        shader->Uniform(fmt::format("pointLights[{}].attn_const", i), m_pointLights[i]->GetAttenuationConst());
        shader->Uniform(fmt::format("pointLights[{}].attn_linear", i), m_pointLights[i]->GetAttenuationLinear());
        shader->Uniform(fmt::format("pointLights[{}].attn_exp", i), m_pointLights[i]->GetAttenuationExp());
    }
}

void LE3LightManager::RenderSpotLights(LE3Shader* shader)
{
    for (int i = 0; i < m_spotLights.size(); i++)
    {
        shader->Uniform(fmt::format("spotLights[{}].color", i), m_spotLights[i]->GetColor());
        shader->Uniform(fmt::format("spotLights[{}].intensity", i), m_spotLights[i]->GetIntensity());
        shader->Uniform(fmt::format("spotLights[{}].position", i), m_spotLights[i]->GetGlobalPosition());
        shader->Uniform(fmt::format("spotLights[{}].direction", i), m_spotLights[i]->GetDirection());
        shader->Uniform(fmt::format("spotLights[{}].cutoff", i), m_spotLights[i]->GetCutoff());
        shader->Uniform(fmt::format("spotLights[{}].outer_cutoff", i), m_spotLights[i]->GetOuterCutoff());
    }
}