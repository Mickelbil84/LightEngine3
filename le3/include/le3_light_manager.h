#pragma once

#include <memory>

#include <cereal/types/memory.hpp>
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
    }

    std::shared_ptr<LE3AmbientLight> GetAmbientLight() const;
    void SetAmbientLight(std::shared_ptr<LE3AmbientLight> ambientLight);

    void RenderLights(LE3Shader* shader);


private:
    void RenderAmbientLight(LE3Shader* shader);

    std::shared_ptr<LE3AmbientLight> m_pAmbientLight;
};