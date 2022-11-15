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
    if (shader)
        this->shaderName = shader->GetName();
}

void LE3Material::SetDiffuseTexture(LE3Texture* texture)
{
    this->diffuseTexture = texture;
    this->diffuseTextureName = texture->GetName();
}

void LE3Material::Apply(glm::mat4 modelMatrix)
{
    if (!pShader)
        return;
    pShader->Use();
    pShader->Uniform("model", modelMatrix);
    pShader->Uniform("material.diffuseColor", diffuseColor);
    pShader->Uniform("material.bUseDiffuseTexture", (GLuint)bUseDiffuseTexture);
    pShader->Uniform("material.tilingX", tilingX);
    pShader->Uniform("material.tilingY", tilingY);
    if (bUseDiffuseTexture)
    {
        pShader->Uniform("material.diffuseTexture", (GLuint)DIFFUSE_TEXTURE_INDEX);
        diffuseTexture->Use(DIFFUSE_TEXTURE_INDEX);
    }
}

LE3Shader* LE3Material::GetShader() const
{
    return pShader;
}