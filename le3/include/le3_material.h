#pragma once

#include <memory>

#include <glm/glm.hpp>

#include "le3_texture.h"
#include "le3_shader.h"


namespace le3 {
    enum TEXTURE_INDEX {
        DIFFUSE_TEXTURE_INDEX = 1,
        SPECULAR_TEXTURE_INDEX = 2,
        NORMAL_TEXTURE_INDEX = 3,
        CUBEMAP_TEXTURE_INDEX = 4,
        SHADOW_MAP_INDEX = 6
    };

    struct LE3Material {
    public:
        LE3Material(LE3ShaderPtr shader) : shader(shader) {}

        void apply();

        ///////////////
        // Members
        ///////////////
        LE3ShaderPtr shader;

        // Diffuse
        glm::vec4 diffuseColor = glm::vec4(.8f, .8f, .8f, 1.f);
        LE3TexturePtr diffuseTexture = nullptr;
        bool bUseDiffuseTexture = false;

        // Specular
        glm::vec3 specularColor = glm::vec3(1.f, 1.f, 1.f);
        float specularIntensity = 1.f;
        float shininess = 16.f;
        LE3TexturePtr specularTexture = nullptr;
        bool bUseSpecularTexture = false;

        // Normal
        LE3TexturePtr normalTexture = nullptr;
        bool bUseNormalTexture = false;

        // Cubemap
        LE3TexturePtr cubemap = nullptr;
        float reflectionIntensity = 0.f;

        // General settings
        float tilingX=1.f, tilingY=1.f;
    };

    using LE3MaterialPtr = std::shared_ptr<LE3Material>;
}