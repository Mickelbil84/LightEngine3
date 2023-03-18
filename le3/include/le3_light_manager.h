#pragma once

#include <memory>

#include <cereal/types/memory.hpp>
#include <cereal/types/vector.hpp>
#include <cereal/cereal.hpp>
#include <cereal/archives/json.hpp>
#include <cereal/archives/binary.hpp>

#include "le3_light.h"
#include "le3_shader.h"

class LE3LightManager
{
public:
    template <class Archive>
    void serialize( Archive & ar )
    {
        ar(CEREAL_NVP(m_pAmbientLight));
        ar(CEREAL_NVP(m_directionalLights));
        ar(CEREAL_NVP(m_pointLights));
        ar(CEREAL_NVP(m_spotLights));
    }

    std::shared_ptr<LE3AmbientLight> GetAmbientLight() const;
    void SetAmbientLight(std::shared_ptr<LE3AmbientLight> ambientLight);

    void AddDirectionalLight(std::shared_ptr<LE3DirectionalLight> directionalLight);
    void AddPointLight(std::shared_ptr<LE3PointLight> pointLight);
    void AddSpotLight(std::shared_ptr<LE3SpotLight> spotLight);

    void RenderLights(LE3Shader* shader);


private:
    void RenderAmbientLight(LE3Shader* shader);
    void RenderDirectionalLights(LE3Shader* shader);
    void RenderPointLights(LE3Shader* shader);
    void RenderSpotLights(LE3Shader* shader);

    std::shared_ptr<LE3AmbientLight> m_pAmbientLight;
    std::vector<std::shared_ptr<LE3DirectionalLight>> m_directionalLights;
    std::vector<std::shared_ptr<LE3PointLight>> m_pointLights;
    std::vector<std::shared_ptr<LE3SpotLight>> m_spotLights;
};