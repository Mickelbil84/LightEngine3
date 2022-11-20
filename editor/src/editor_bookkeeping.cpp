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

void UpdateMeshBookkeeping(LE3SceneManager& scene, std::string oldMesh, std::string newMesh)
{
    for (auto [key, pObject] : scene.objectPool)
    {
        std::shared_ptr<LE3StaticMesh> pStaticMesh = std::dynamic_pointer_cast<LE3StaticMesh>(pObject);
        if (!pStaticMesh)
            continue;
        
        if (pStaticMesh->meshName != oldMesh)
            continue;
        pStaticMesh->meshName = newMesh;
        pStaticMesh->UpdateAssets(scene.assets);
    }
}

void UpdateMaterialBookkeeping(LE3SceneManager& scene, std::string oldMaterial, std::string newMaterial)
{
    for (auto [key, pObject] : scene.objectPool)
    {
        std::shared_ptr<LE3StaticMesh> pStaticMesh = std::dynamic_pointer_cast<LE3StaticMesh>(pObject);
        if (!pStaticMesh)
            continue;
        
        if (pStaticMesh->materialName != oldMaterial)
            continue;
        pStaticMesh->materialName = newMaterial;
        pStaticMesh->UpdateAssets(scene.assets);
    }
}