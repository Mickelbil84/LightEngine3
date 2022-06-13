#version 410 core

struct Material
{
    vec4 diffuseColor;
    sampler2D diffuseTexture;
    bool bUseDiffuseTexture;
};
uniform Material material;

out vec4 fColor;

in vec2 texCoord;
in vec4 normalColor;

void main()
{
    // Diffuse color
    vec4 diffuseColor = material.diffuseColor;
    if (material.bUseDiffuseTexture)
        diffuseColor = texture(material.diffuseTexture, texCoord);

    fColor = diffuseColor;
    fColor = normalColor;
}