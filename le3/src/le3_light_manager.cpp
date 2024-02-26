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

void LE3LightManager::renderAmbientLight(LE3ShaderPtr pShader) {
    if (m_pAmbientLight == nullptr) {
        pShader->uniform("ambientLight.color", glm::vec3(0.f)); return;
    }
    pShader->uniform("ambientLight.color", m_pAmbientLight->getColor());
    pShader->uniform("ambientLight.intensity", m_pAmbientLight->getIntensity());
}
void LE3LightManager::renderDirectionalLights(LE3ShaderPtr pShader, glm::vec3 cameraPos) {
    for (int i = 0; i < MAX_DIRECTIONAL_LIGHTS; i++)
    {
        pShader->uniform(fmt::format("directionalLights[{}].intensity", i), 0.f);
        pShader->uniform(fmt::format("directionalLights[{}].bEnableShadows", i), (GLuint)false);
    }
    for (int i = 0; i < m_pDirectionalLights.size(); i++)
    {
        if (i >= MAX_DIRECTIONAL_LIGHTS) break;
        LE3FramebufferPtr shadowMap = m_pDirectionalLights[i]->getShadowMap();
        if (shadowMap) shadowMap->useDepthTexture(shadowMap->getBindIdx());
        pShader->uniform(fmt::format("directionalLights[{}].color", i), m_pDirectionalLights[i]->getColor());
        pShader->uniform(fmt::format("directionalLights[{}].intensity", i), m_pDirectionalLights[i]->getIntensity());
        pShader->uniform(fmt::format("directionalLights[{}].direction", i), m_pDirectionalLights[i]->getDirection());
        pShader->uniform(fmt::format("directionalLights[{}].bEnableShadows", i), (GLuint)(shadowMap != nullptr));
        if (shadowMap) pShader->uniform(fmt::format("directionalLights[{}].shadowMap", i), shadowMap->getBindIdx());
        pShader->uniform(fmt::format("dirLightViewMatrix[{}]", i), m_pDirectionalLights[i]->getViewMatrix(cameraPos));
    }
}
void LE3LightManager::renderPointLights(LE3ShaderPtr pShader) {
    for (int i = 0; i < MAX_POINT_LIGHTS; i++)
    {
        pShader->uniform(fmt::format("pointLights[{}].intensity", i), 0.f);
    }
    for (int i = 0; i < m_pPointLights.size(); i++)
    {
        if (i >= MAX_POINT_LIGHTS) break;
        pShader->uniform(fmt::format("pointLights[{}].color", i), m_pPointLights[i]->getColor());
        pShader->uniform(fmt::format("pointLights[{}].intensity", i), m_pPointLights[i]->getIntensity());
        pShader->uniform(fmt::format("pointLights[{}].position", i), m_pPointLights[i]->getPosition());
        pShader->uniform(fmt::format("pointLights[{}].attn_const", i), m_pPointLights[i]->getAttnConst());
        pShader->uniform(fmt::format("pointLights[{}].attn_linear", i), m_pPointLights[i]->getAttnLinear());
        pShader->uniform(fmt::format("pointLights[{}].attn_exp", i), m_pPointLights[i]->getAttnExp());
    }
}
void LE3LightManager::renderSpotLights(LE3ShaderPtr pShader) {
    for (int i = 0; i < MAX_SPOT_LIGHTS; i++)
    {
        pShader->uniform(fmt::format("spotLights[{}].intensity", i), 0.f);
        pShader->uniform(fmt::format("spotLights[{}].bEnableShadows", i), (GLuint)false);
    }
    for (int i = 0; i < m_pSpotLights.size(); i++)
    {
        if (i >= MAX_SPOT_LIGHTS) break;
        LE3FramebufferPtr shadowMap = m_pSpotLights[i]->getShadowMap();
        if (shadowMap) shadowMap->useDepthTexture(shadowMap->getBindIdx());
        pShader->uniform(fmt::format("spotLights[{}].color", i), m_pSpotLights[i]->getColor());
        pShader->uniform(fmt::format("spotLights[{}].intensity", i), m_pSpotLights[i]->getIntensity());
        pShader->uniform(fmt::format("spotLights[{}].position", i), m_pSpotLights[i]->getPosition());
        pShader->uniform(fmt::format("spotLights[{}].direction", i), m_pSpotLights[i]->getDirection());
        pShader->uniform(fmt::format("spotLights[{}].cutoff", i), m_pSpotLights[i]->getCutoff());
        pShader->uniform(fmt::format("spotLights[{}].outer_cutoff", i), m_pSpotLights[i]->getOuterCutoff());
        pShader->uniform(fmt::format("spotLights[{}].bEnableShadows", i), (GLuint)(shadowMap != nullptr));
        if (shadowMap)  pShader->uniform(fmt::format("spotLights[{}].shadowMap", i), shadowMap->getBindIdx());
        if (shadowMap)  pShader->uniform(fmt::format("spotLightViewMatrix[{}]", i), m_pSpotLights[i]->getViewMatrix());
    }
}