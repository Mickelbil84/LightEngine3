#include "commands/le3ed_com_delete_texture.h"
using namespace le3;

LE3EditorComDeleteTexture::LE3EditorComDeleteTexture(std::string name, std::string path, bool interpolate) :
    m_name(name), m_path(path), m_bInterpolate(interpolate) {
    for (auto& [name, material] : LE3GetAssetManager().getMaterials()) {
        if (material->diffuseTexture.lock() && material->diffuseTexture.lock()->getName() == m_name)
            m_depMatsDiff.push_back(name);
        if (material->specularTexture.lock() && material->specularTexture.lock()->getName() == m_name)
            m_depMatsSpec.push_back(name);
        if (material->normalTexture.lock() && material->normalTexture.lock()->getName() == m_name)
            m_depMatsNorm.push_back(name);
        if (material->cubemap.lock() && material->cubemap.lock()->getName() == m_name)
            m_depMatsCube.push_back(name);
    }
}

void LE3EditorComDeleteTexture::execute() {
    LE3GetAssetManager().deleteTexture(m_name);
}
void LE3EditorComDeleteTexture::undo() {
    LE3GetAssetManager().addTexture(m_name, m_path, m_bInterpolate);
    for (std::string materialName : m_depMatsDiff)
        LE3GetAssetManager().getMaterial(materialName).lock()->diffuseTexture = LE3GetAssetManager().getTexture(m_name);
    for (std::string materialName : m_depMatsSpec)
        LE3GetAssetManager().getMaterial(materialName).lock()->specularTexture = LE3GetAssetManager().getTexture(m_name);
    for (std::string materialName : m_depMatsNorm)
        LE3GetAssetManager().getMaterial(materialName).lock()->normalTexture = LE3GetAssetManager().getTexture(m_name);
    for (std::string materialName : m_depMatsCube)
        LE3GetAssetManager().getMaterial(materialName).lock()->cubemap = LE3GetAssetManager().getTexture(m_name);
}