#include "le3_light_manager.h"

#include <fmt/core.h>

LE3LightManager::LE3LightManager()
{
    m_shadowMapWidth = m_shadowMapHeight = 4096;
}

void LE3LightManager::Init()
{
    std::string shadowShaderVS = "#version 410 core\n"
        "layout (location = 0) in vec4 vPosition;\n"
        "\n"
        "uniform mat4 model;\n"
        "uniform mat4 lightMatrix;\n"
        "\n"
        "void main()\n"
        "{\n"
        "\tgl_Position = lightMatrix * model * vPosition;\n"
        "}";
    std::string shadowShaderFS = "#version 410 core\n"
        "\n"
        "void main()\n"
        "{\n"
        "}";
    m_shadowShader.CompileShaderFromSource(shadowShaderVS, shadowShaderFS);
}

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

void LE3LightManager::RenderLights(LE3Shader* shader, glm::vec3 camPos)
{
    RenderAmbientLight(shader);
    RenderDirectionalLights(shader, camPos);
    RenderPointLights(shader);
    RenderSpotLights(shader);
}

void LE3LightManager::RenderAmbientLight(LE3Shader* shader)
{
    if (!m_pAmbientLight) return;
    shader->Uniform("ambientLight.color", m_pAmbientLight->GetColor());
    shader->Uniform("ambientLight.intensity", m_pAmbientLight->GetIntensity());
}

void LE3LightManager::RenderDirectionalLights(LE3Shader* shader, glm::vec3 camPos)
{
    for (int i = 0; i < m_directionalLights.size(); i++)
    {
        if (m_directionalLights[i]->IsShadowsEnabled())
        {   
            glActiveTexture(GL_TEXTURE0 + m_directionalLights[i]->GetShadowMap().bindIdx);
            glBindTexture(GL_TEXTURE_2D, m_directionalLights[i]->GetShadowMap().texId);
        }
        shader->Uniform(fmt::format("directionalLights[{}].color", i), m_directionalLights[i]->GetColor());
        shader->Uniform(fmt::format("directionalLights[{}].intensity", i), m_directionalLights[i]->GetIntensity());
        shader->Uniform(fmt::format("directionalLights[{}].direction", i), m_directionalLights[i]->GetDirection());
        shader->Uniform(fmt::format("directionalLights[{}].bEnableShadows", i), (GLuint)m_directionalLights[i]->IsShadowsEnabled());
        shader->Uniform(fmt::format("directionalLights[{}].shadowMap", i), m_directionalLights[i]->GetShadowMap().bindIdx);
        shader->Uniform(fmt::format("dirLightViewMatrix[{}]", i), m_directionalLights[i]->GetViewMatrix(camPos));
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
        if (m_spotLights[i]->IsShadowsEnabled())
        {   
            glActiveTexture(GL_TEXTURE0 + m_spotLights[i]->GetShadowMap().bindIdx);
            glBindTexture(GL_TEXTURE_2D, m_spotLights[i]->GetShadowMap().texId);
        }
        shader->Uniform(fmt::format("spotLights[{}].color", i), m_spotLights[i]->GetColor());
        shader->Uniform(fmt::format("spotLights[{}].intensity", i), m_spotLights[i]->GetIntensity());
        shader->Uniform(fmt::format("spotLights[{}].position", i), m_spotLights[i]->GetGlobalPosition());
        shader->Uniform(fmt::format("spotLights[{}].direction", i), m_spotLights[i]->GetDirection());
        shader->Uniform(fmt::format("spotLights[{}].cutoff", i), m_spotLights[i]->GetCutoff());
        shader->Uniform(fmt::format("spotLights[{}].outer_cutoff", i), m_spotLights[i]->GetOuterCutoff());
        shader->Uniform(fmt::format("spotLights[{}].bEnableShadows", i), (GLuint)m_spotLights[i]->IsShadowsEnabled());
        shader->Uniform(fmt::format("spotLights[{}].shadowMap", i), m_spotLights[i]->GetShadowMap().bindIdx);
    }
}

void LE3LightManager::EnableShadows(std::shared_ptr<LE3DirectionalLight> directionalLight)
{
    directionalLight->SetShadowsEnabled(true);
    directionalLight->GetShadowMap().Init(m_shadowMapWidth, m_shadowMapHeight);
}
void LE3LightManager::EnableShadows(std::shared_ptr<LE3SpotLight> spotLight)
{
    spotLight->SetShadowsEnabled(true);
    spotLight->GetShadowMap().Init(m_shadowMapWidth, m_shadowMapHeight);
}

void LE3LightManager::DisableShadows(std::shared_ptr<LE3DirectionalLight> directionalLight)
{
    directionalLight->SetShadowsEnabled(true);
    directionalLight->GetShadowMap().Clear();
}
void LE3LightManager::DisableShadows(std::shared_ptr<LE3SpotLight> spotLight)
{
    spotLight->SetShadowsEnabled(true);
    spotLight->GetShadowMap().Clear();
}
void LE3LightManager::UpdateLightShadowMaps()
{
    for (auto light : m_directionalLights)
        if (light->IsShadowsEnabled())
            EnableShadows(light);
    for (auto light : m_spotLights)
        if (light->IsShadowsEnabled())
            EnableShadows(light);
}
std::vector<std::shared_ptr<LE3DirectionalLight>>& LE3LightManager::GetDirectionalLights()
{
    return m_directionalLights;
}
std::vector<std::shared_ptr<LE3SpotLight>>& LE3LightManager::GetSpotLights()
{
    return m_spotLights;
}
LE3Shader* LE3LightManager::GetShadowShader()
{
    return &m_shadowShader;
}