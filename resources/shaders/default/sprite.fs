#version 410 core

struct Material
{
    vec4 diffuseColor;
    sampler2D diffuseTexture;
    bool bUseDiffuseTexture;
    float tilingX, tilingY;
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
        diffuseColor = texture(
            material.diffuseTexture, vec2(texCoord.x * material.tilingX, texCoord.y * material.tilingY));
    if (diffuseColor.a < 0.5)
        discard;

    // Lambert light
    vec3 dir = normalize(vec3(1, 0.5, 1));
    float light = max(0, dot(dir, normalize(vec3(normalColor)))) + 0.5f;

    fColor = light * diffuseColor;
}