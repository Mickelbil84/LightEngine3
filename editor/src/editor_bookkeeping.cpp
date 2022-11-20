#include "editor_bookkeeping.h"

void UpdateShaderBookkeeping(LE3AssetManager& assets, std::string oldShader, std::string newShader)
{
    for (auto [key, material] : assets.m_materials)
    {
        if (material.GetShader()->GetName() != oldShader)
            continue;
        assets.m_materials[key].shaderName = newShader;
        if (newShader != std::string(""))
            assets.m_materials[key].SetShader(assets.GetShader(newShader));
        else
            assets.m_materials[key].SetShader(nullptr);
    }
}

void UpdateTextureBookkeeping(LE3AssetManager& assets, std::string oldTexture, std::string newTexture)
{
    for (auto [key, material] : assets.m_materials)
    {
        if (material.diffuseTextureName == oldTexture)
        {
            assets.m_materials[key].diffuseTextureName = newTexture;
            if (newTexture != std::string(""))
                assets.m_materials[key].SetDiffuseTexture(assets.GetTexture(newTexture));
            else
                assets.m_materials[key].SetDiffuseTexture(nullptr);
        }
    }
}