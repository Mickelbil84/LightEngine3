#version 410 core

struct Material
{
    vec4 diffuseColor;
    sampler2D diffuseTexture;
    bool bUseDiffuseTexture;
};
uniform Material material;
uniform bool hovered;

out vec4 fColor;

in vec2 texCoord;
in vec4 normalColor;

void main()
{
    // Diffuse color
    vec4 diffuseColor = material.diffuseColor;
    if (hovered)
        diffuseColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);

    // Lambert light
    vec3 dir = normalize(vec3(1, 0.5, 1));
    float light = max(0, dot(dir, normalize(vec3(normalColor)))) + 0.5f;

    fColor = light * diffuseColor;
}