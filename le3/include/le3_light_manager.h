#pragma once

#include <vector>
#include <memory>

#include "le3_light.h"
#include "le3_shader.h"

namespace le3 {
    class LE3LightManager {
    public:
        inline void setAmbientLight(LE3AmbientLightPtr ambientLight) { m_pAmbientLight = ambientLight; }
        inline LE3AmbientLightWeakPtr getAmbientLight() { return m_pAmbientLight; }
        inline std::vector<LE3DirectionalLightWeakPtr>& getDirectionalLights() { return m_pDirectionalLights; }
        inline std::vector<LE3SpotLightWeakPtr>& getSpotLights() { return m_pSpotLights; }

        inline void addDirectionalLight(LE3DirectionalLightPtr directionalLight) { m_pDirectionalLights.push_back(directionalLight); }
        inline void addPointLight(LE3PointLightPtr pointLight) { m_pPointLights.push_back(pointLight); }
        inline void addSpotLight(LE3SpotLightPtr spotLight) { m_pSpotLights.push_back(spotLight); }

        void deleteLight(std::string name); // Hotfix for deleting lights (when drawing shadows)

        void renderLights(LE3ShaderPtr pShader, glm::vec3 cameraPos);

        void setLightSpriteVisibility(bool bVisible);

    private:
        LE3AmbientLightWeakPtr m_pAmbientLight;
        std::vector<LE3DirectionalLightWeakPtr> m_pDirectionalLights;
        std::vector<LE3PointLightWeakPtr> m_pPointLights;
        std::vector<LE3SpotLightWeakPtr> m_pSpotLights;


        void renderAmbientLight(LE3ShaderPtr pShader);
        void renderDirectionalLights(LE3ShaderPtr pShader, glm::vec3 cameraPos);
        void renderPointLights(LE3ShaderPtr pShader);
        void renderSpotLights(LE3ShaderPtr pShader);
    };
}