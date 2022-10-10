#include "le3_material.h"

LE3Material::LE3Material()
{
    this->pShader = nullptr;
}

LE3Material::LE3Material(LE3Shader* shader)
{
    this->pShader = nullptr;
    SetShader(shader);
}

void LE3Material::SetShader(LE3Shader* shader)
{
    this->pShader = shader;
}

void LE3Material::Apply(glm::mat4 modelMatrix)
{
    pShader->Use();
    pShader->Uniform("model", modelMatrix);
    pShader->Uniform("material.diffuseColor", diffuseColor);
    pShader->Uniform("material.bUseDiffuseTexture", bUseDiffuseTexture);
    if (bUseDiffuseTexture)
    {
        pShader->Uniform("material.diffuseTexture", DIFFUSE_TEXTURE_INDEX);
        diffuseTexture->Use(DIFFUSE_TEXTURE_INDEX);
    }
}

LE3Shader* LE3Material::GetShader() const
{
    return pShader;
}