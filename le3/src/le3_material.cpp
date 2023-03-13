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

void LE3Material::Apply(glm::mat4 modelMatrix)
{
    if (!pShader)
        return;
    pShader->Use();
    pShader->Uniform("model", modelMatrix);
    pShader->Uniform("material.diffuseColor", diffuseColor);
    pShader->Uniform("material.bUseDiffuseTexture", (GLuint)bUseDiffuseTexture);

    pShader->Uniform("material.specularColor", specularColor);
    pShader->Uniform("material.specularIntensity", specularIntensity);
    pShader->Uniform("material.shininess", shininess);
    pShader->Uniform("material.bUseSpecularTexture", (GLuint)bUseSpecularTexture);

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
        diffuseTexture->Use(SPECULAR_TEXTURE_INDEX);
    }
}

LE3Shader* LE3Material::GetShader() const
{
    return pShader;
}