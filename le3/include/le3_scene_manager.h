#pragma once

#include <fstream>

#include <cereal/cereal.hpp>
#include <cereal/archives/json.hpp>
#include <cereal/archives/binary.hpp>

#include "le3_asset_manager.h"

class LE3SceneManager
{
public:
    LE3AssetManager assets;

    void SaveAssets(std::string serializationPath) const;
    void LoadAssets(std::string serializationPath);

    template <class Archive>
    void serialize( Archive & ar )
    {
        ar(CEREAL_NVP(assets));
    }
};