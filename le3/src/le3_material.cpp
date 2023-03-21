#include "le3_material.h"

LE3Material::LE3Material()
{
    this->pShader = nullptr;
    this->diffuseTexture = nullptr;
}

LE3Material::LE3Material(LE3Shader* shader)
{
    this->pShader = nullptr;
    this->diffuseTexture = nullptr;
    SetShader(shader);
}

void LE3Material::SetShader(LE3Shader* shader)
{
    this->pShader = shader;
    if (shader)
        this->shaderName = shader->GetName();
}

void LE3Material::SetDiffuseTexture(LE3Texture* texture)
{
    if (texture)
    {
        this->diffuseTexture = texture;
        this->diffuseTextureName = texture->GetName();
    }
    else
    {
        this->diffuseTexture = nullptr;
        this->diffuseTextureName = std::string("");
    }
}

void LE3Material::SetSpecularTexture(LE3Texture* texture)
{
    if (texture)
    {
        this->specularTexture = texture;
        this->specularTextureName = texture->GetName();
    }
    else
    {
        this->specularTexture = nullptr;
        this->specularTextureName = std::string("");
    }
}

void LE3Material::SetNormalTexture(LE3Texture* texture)
{
    if (texture)
    {
        this->normalTexture = texture;
        this->normalTextureName = texture->GetName();
    }
    else
    {
        this->normalTexture = nullptr;
        this->normalTextureName = std::string("");
    }
}
void LE3Material::SetCubemap(LE3Texture* cubemap)
{
    if (cubemap)
    {
        this->cubemap = cubemap;
        this->cubemapName = cubemap->GetName();
    }
    else
    {
        this->cubemap = nullptr;
        this->cubemapName = std::string("");
    }
}

void LE3Material::Apply()
{
    if (!pShader)
        return;
    pShader->Use();
    pShader->Uniform("material.diffuseColor", diffuseColor);
    pShader->Uniform("material.bUseDiffuseTexture", (GLuint)bUseDiffuseTexture);

    pShader->Uniform("material.specularColor", specularColor);
    pShader->Uniform("material.specularIntensity", specularIntensity);
    pShader->Uniform("material.shininess", shininess);
    pShader->Uniform("material.bUseSpecularTexture", (GLuint)bUseSpecularTexture);

    pShader->Uniform("material.bUseNormalTexture", (GLuint)bUseNormalTexture);

    pShader->Uniform("material.reflectionIntensity", reflectionIntensity);

    pShader->Uniform("material.tilingX", tilingX);
    pShader->Uniform("material.tilingY", tilingY);
    if (bUseDiffuseTexture && diffuseTexture)
    {
        pShader->Uniform("material.diffuseTexture", (GLuint)DIFFUSE_TEXTURE_INDEX);
        diffuseTexture->Use(DIFFUSE_TEXTURE_INDEX);
    }
    if (bUseSpecularTexture && specularTexture)
    {
        pShader->Uniform("material.specularTexture", (GLuint)SPECULAR_TEXTURE_INDEX);
        specularTexture->Use(SPECULAR_TEXTURE_INDEX);
    }
    if (bUseNormalTexture && normalTexture)
    {
        pShader->Uniform("material.normalTexture", (GLuint)NORMAL_TEXTURE_INDEX);
        normalTexture->Use(NORMAL_TEXTURE_INDEX);
    }
    if (reflectionIntensity > 0.f && cubemap)
    {
        pShader->Uniform("material.cubemapTexture", (GLuint)CUBEMAP_TEXTURE_INDEX);
        cubemap->Use(CUBEMAP_TEXTURE_INDEX);
    }
}

LE3Shader* LE3Material::GetShader() const
{
    return pShader;
}