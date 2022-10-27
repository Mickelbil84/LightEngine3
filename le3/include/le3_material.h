#pragma once

#include <glm/glm.hpp>

#include <cereal/cereal.hpp>
#include <cereal/types/string.hpp>

#include "le3_shader.h"
#include "le3_texture.h"
#include "le3_utils.h"

#define DIFFUSE_TEXTURE_INDEX 0

struct LE3Material
{
public:
    LE3Material();
    LE3Material(LE3Shader* shader);

    void SetShader(LE3Shader* shader);
    void SetDiffuseTexture(LE3Texture* texture);

    std::string shaderName;

    glm::vec4 diffuseColor = glm::vec4(0.8f, 0.8f, 0.8f, 1.f);
    std::string diffuseTextureName;
    bool bUseDiffuseTexture = false;

    LE3Texture* diffuseTexture;

    // Sends material information to a given shader, and binds all relevant textures
    void Apply(glm::mat4 modelMatrix);
    LE3Shader* GetShader() const;

    template <class Archive>
    void serialize( Archive & ar )
    {
        ar(CEREAL_NVP(shaderName));

        ar(CEREAL_NVP(diffuseColor));

        ar(CEREAL_NVP(diffuseTextureName));
        ar(CEREAL_NVP(bUseDiffuseTexture));
    }

protected:
    LE3Shader* pShader;
};