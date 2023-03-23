#pragma once

#include <memory>

#include <cereal/types/memory.hpp>
#include <cereal/types/vector.hpp>
#include <cereal/cereal.hpp>
#include <cereal/archives/json.hpp>
#include <cereal/archives/binary.hpp>

#include "le3_light.h"
#include "le3_shader.h"
#include "le3_physics.h"

const float gEngineLightSpriteSize = 0.1f;

class LE3LightManager
{
public:
    LE3LightManager();
    void Init();

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

    void RenderLights(LE3Shader* shader, glm::vec3 camPos);

    void EnableShadows(std::shared_ptr<LE3DirectionalLight> directionalLight);
    void DisableShadows(std::shared_ptr<LE3DirectionalLight> directionalLight);
    void EnableShadows(LE3DirectionalLight* directionalLight);
    void DisableShadows(LE3DirectionalLight* directionalLight);
    void EnableShadows(std::shared_ptr<LE3SpotLight> spotLight);
    void DisableShadows(std::shared_ptr<LE3SpotLight> spotLight);
    void EnableShadows(LE3SpotLight* spotLight);
    void DisableShadows(LE3SpotLight* spotLight);
    void UpdateLightShadowMaps();

    std::vector<std::shared_ptr<LE3DirectionalLight>>& GetDirectionalLights();
    std::vector<std::shared_ptr<LE3SpotLight>>& GetSpotLights();
    LE3Shader* GetShadowShader();

    void RegisterLightCollisions(LE3PhysicsComponent* physics);

private:
    void RenderAmbientLight(LE3Shader* shader);
    void RenderDirectionalLights(LE3Shader* shader, glm::vec3 camPos);
    void RenderPointLights(LE3Shader* shader);
    void RenderSpotLights(LE3Shader* shader);

    btRigidBody* RegisterLightCollisionsImpl(LE3Object* obj, LE3PhysicsComponent* physics);

    std::shared_ptr<LE3AmbientLight> m_pAmbientLight;
    std::vector<std::shared_ptr<LE3DirectionalLight>> m_directionalLights;
    std::vector<std::shared_ptr<LE3PointLight>> m_pointLights;
    std::vector<std::shared_ptr<LE3SpotLight>> m_spotLights;

    GLuint m_shadowMapWidth, m_shadowMapHeight;
    LE3Shader m_shadowShader;
};