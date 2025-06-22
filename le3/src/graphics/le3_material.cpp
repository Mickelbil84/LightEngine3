#include "graphics/le3_material.h"
using namespace le3;

void LE3Material::apply() {
    auto shader = this->shader.lock();
    if (!shader) return;
    shader->uniform("material.diffuseColor", diffuseColor);
    shader->uniform("material.bUseDiffuseTexture", (uint32_t)bUseDiffuseTexture);

    shader->uniform("material.specularColor", specularColor);
    shader->uniform("material.specularIntensity", specularIntensity);
    shader->uniform("material.shininess", shininess);
    shader->uniform("material.bUseSpecularTexture", (uint32_t)bUseSpecularTexture);

    shader->uniform("material.bUseNormalTexture", (uint32_t)bUseNormalTexture);

    shader->uniform("material.reflectionIntensity", reflectionIntensity);

    shader->uniform("material.tilingX", tilingX);
    shader->uniform("material.tilingY", tilingY);
    std::shared_ptr<LE3Texture> diffuseTexture = this->diffuseTexture.lock();
    if (bUseDiffuseTexture && diffuseTexture)
    {
        shader->uniform("material.diffuseTexture", (uint32_t)DIFFUSE_TEXTURE_INDEX);
        diffuseTexture->use(DIFFUSE_TEXTURE_INDEX);
    }
    std::shared_ptr<LE3Texture> specularTexture = this->specularTexture.lock();
    if (bUseSpecularTexture && specularTexture)
    {
        shader->uniform("material.specularTexture", (uint32_t)SPECULAR_TEXTURE_INDEX);
        specularTexture->use(SPECULAR_TEXTURE_INDEX);
    }
    std::shared_ptr<LE3Texture> normalTexture = this->normalTexture.lock();
    if (bUseNormalTexture && normalTexture)
    {
        shader->uniform("material.normalTexture", (uint32_t)NORMAL_TEXTURE_INDEX);
        normalTexture->use(NORMAL_TEXTURE_INDEX);
    }
    std::shared_ptr<LE3Texture> cubemap = this->cubemap.lock();
    if (reflectionIntensity > 0.f && cubemap)
    {
        shader->uniform("material.cubemapTexture", (uint32_t)CUBEMAP_TEXTURE_INDEX);
        cubemap->use(CUBEMAP_TEXTURE_INDEX);
    }
}