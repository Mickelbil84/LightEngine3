#pragma once

#include <glm/glm.hpp>

#include "le3_shader.h"
#include "le3_texture.h"

#define DIFFUSE_TEXTURE_INDEX 0

struct LE3Material
{
public:
    LE3Material();
    LE3Material(LE3Shader* shader);

    void SetShader(LE3Shader* shader);

    glm::vec4 diffuseColor = glm::vec4(0.8f, 0.8f, 0.8f, 1.f);
    LE3Texture* diffuseTexture;
    bool bUseDiffuseTexture = false;

    // Sends material information to a given shader, and binds all relevant textures
    void Apply(glm::mat4 modelMatrix);
    LE3Shader* GetShader() const;

protected:
    LE3Shader* pShader;
};