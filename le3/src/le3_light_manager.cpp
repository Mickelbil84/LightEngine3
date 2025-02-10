#include "le3_light_manager.h"
using namespace le3;

#ifdef __linux__
#include <GL/glew.h>
#else
#include <gl/glew.h>
#endif
#include <fmt/core.h>


void LE3LightManager::renderLights(LE3ShaderPtr pShader, glm::vec3 cameraPos) {
    renderAmbientLight(pShader);
    renderDirectionalLights(pShader, cameraPos);
    renderPointLights(pShader);
    renderSpotLights(pShader);
}

void LE3LightManager::renderAmbientLight(LE3ShaderPtr pShaderWeak) {
    auto pShader = pShaderWeak.lock();
    if (!pShader) return; 
    LE3AmbientLightPtr pAmbientLight = m_pAmbientLight.lock();
    if (!pAmbientLight) {
        pShader->uniform("ambientLight.color", glm::vec3(0.f)); return;
    }
    pShader->uniform("ambientLight.color", pAmbientLight->getColor());
    pShader->uniform("ambientLight.intensity", pAmbientLight->getIntensity());
}
void LE3LightManager::renderDirectionalLights(LE3ShaderPtr pShaderWeak, glm::vec3 cameraPos) {
    auto pShader = pShaderWeak.lock();
    if (!pShader) return; 
    for (int i = 0; i < MAX_DIRECTIONAL_LIGHTS; i++)
    {
        pShader->uniform(fmt::format("directionalLights[{}].intensity", i), 0.f);
        pShader->uniform(fmt::format("directionalLights[{}].bEnableShadows", i), (GLuint)false);
    }
    for (int i = 0; i < m_pDirectionalLights.size(); i++)
    {
        if (i >= MAX_DIRECTIONAL_LIGHTS) break;
        LE3DirectionalLightPtr pDirectionalLight = m_pDirectionalLights[i].lock();
        if (!pDirectionalLight) continue;
        LE3FramebufferPtr shadowMap = pDirectionalLight->getShadowMap();
        if (shadowMap) shadowMap->useDepthTexture(shadowMap->getBindIdx());
        pShader->uniform(fmt::format("directionalLights[{}].color", i), pDirectionalLight->getColor());
        pShader->uniform(fmt::format("directionalLights[{}].intensity", i), pDirectionalLight->getIntensity());
        pShader->uniform(fmt::format("directionalLights[{}].direction", i), pDirectionalLight->getDirection());
        pShader->uniform(fmt::format("directionalLights[{}].bEnableShadows", i), (GLuint)(shadowMap != nullptr));
        if (shadowMap) pShader->uniform(fmt::format("directionalLights[{}].shadowMap", i), shadowMap->getBindIdx());
        pShader->uniform(fmt::format("dirLightViewMatrix[{}]", i), pDirectionalLight->getViewMatrix(cameraPos));
    }

    // Remove lights that are no longer valid
    m_pDirectionalLights.erase(std::remove_if(m_pDirectionalLights.begin(), m_pDirectionalLights.end(), [](std::weak_ptr<LE3DirectionalLight> pLight) { return pLight.expired(); }), m_pDirectionalLights.end());
}
void LE3LightManager::renderPointLights(LE3ShaderPtr pShaderWeak) {
    auto pShader = pShaderWeak.lock();
    if (!pShader) return; 
    for (int i = 0; i < MAX_POINT_LIGHTS; i++)
    {
        pShader->uniform(fmt::format("pointLights[{}].intensity", i), 0.f);
    }
    for (int i = 0; i < m_pPointLights.size(); i++)
    {
        if (i >= MAX_POINT_LIGHTS) break;
        LE3PointLightPtr pPointLight = m_pPointLights[i].lock();
        if (!pPointLight) continue;
        pShader->uniform(fmt::format("pointLights[{}].color", i), pPointLight->getColor());
        pShader->uniform(fmt::format("pointLights[{}].intensity", i), pPointLight->getIntensity());
        pShader->uniform(fmt::format("pointLights[{}].position", i), pPointLight->getPosition());
        pShader->uniform(fmt::format("pointLights[{}].attn_const", i), pPointLight->getAttnConst());
        pShader->uniform(fmt::format("pointLights[{}].attn_linear", i), pPointLight->getAttnLinear());
        pShader->uniform(fmt::format("pointLights[{}].attn_exp", i), pPointLight->getAttnExp());
    }

    // Remove lights that are no longer valid
    m_pPointLights.erase(std::remove_if(m_pPointLights.begin(), m_pPointLights.end(), [](std::weak_ptr<LE3PointLight> pLight) { return pLight.expired(); }), m_pPointLights.end());
}
void LE3LightManager::renderSpotLights(LE3ShaderPtr pShaderWeak) {
    auto pShader = pShaderWeak.lock();
    if (!pShader) return; 
    for (int i = 0; i < MAX_SPOT_LIGHTS; i++)
    {
        pShader->uniform(fmt::format("spotLights[{}].intensity", i), 0.f);
        pShader->uniform(fmt::format("spotLights[{}].bEnableShadows", i), (GLuint)false);
    }
    for (int i = 0; i < m_pSpotLights.size(); i++)
    {
        if (i >= MAX_SPOT_LIGHTS) break;
        LE3SpotLightPtr pSpotLight = m_pSpotLights[i].lock();
        if (!pSpotLight) continue;
        LE3FramebufferPtr shadowMap = pSpotLight->getShadowMap();
        if (shadowMap) shadowMap->useDepthTexture(shadowMap->getBindIdx());
        pShader->uniform(fmt::format("spotLights[{}].color", i), pSpotLight->getColor());
        pShader->uniform(fmt::format("spotLights[{}].intensity", i), pSpotLight->getIntensity());
        pShader->uniform(fmt::format("spotLights[{}].position", i), pSpotLight->getPosition());
        pShader->uniform(fmt::format("spotLights[{}].direction", i), pSpotLight->getDirection());
        pShader->uniform(fmt::format("spotLights[{}].cutoff", i), pSpotLight->getCutoff());
        pShader->uniform(fmt::format("spotLights[{}].outer_cutoff", i), pSpotLight->getOuterCutoff());
        pShader->uniform(fmt::format("spotLights[{}].bEnableShadows", i), (GLuint)(shadowMap != nullptr));
        if (shadowMap)  pShader->uniform(fmt::format("spotLights[{}].shadowMap", i), shadowMap->getBindIdx());
        if (shadowMap)  pShader->uniform(fmt::format("spotLightViewMatrix[{}]", i), pSpotLight->getViewMatrix());
    }

    // Remove lights that are no longer valid
    m_pSpotLights.erase(std::remove_if(m_pSpotLights.begin(), m_pSpotLights.end(), [](std::weak_ptr<LE3SpotLight> pLight) { return pLight.expired(); }), m_pSpotLights.end());
}