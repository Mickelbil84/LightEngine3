#pragma once

#include <memory>

#include <cereal/types/memory.hpp>
#include <cereal/cereal.hpp>
#include <cereal/archives/json.hpp>
#include <cereal/archives/binary.hpp>

#include "le3_light.h"

class LE3LightManager
{
public:
    template <class Archive>
    void serialize( Archive & ar )
    {
        ar(CEREAL_NVP(m_pAmbientLight));
    }

private:
    std::shared_ptr<LE3AmbientLight> m_pAmbientLight;
};