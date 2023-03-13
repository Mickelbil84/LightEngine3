#version 410 core

#define MAX_DIRECTIONAL_LIGHTS

struct Material
{
    vec4 diffuseColor;
    sampler2D diffuseTexture;
    bool bUseDiffuseTexture;

    vec3 specularColor;
    float specularIntensity, shininess;
    sampler2D specularTexture;
    bool bUseSpecularTexture;

    float tilingX, tilingY;
};
uniform Material material;

struct AmbientLight
{
    vec3 color;
    float intensity;
};
uniform AmbientLight ambientLight;

struct DirectionalLight
{
    vec3 color;
    float intensity;
    vec3 direction;
};

out vec4 fColor;

in vec2 texCoord;
in vec3 posCoord;
in vec3 normalCoord;

float calc_lambertian(vec3 normal, vec3 direction)
{
    return max(dot(-direction, normal), 0.0);
}

float calc_blinn_phong(vec3 normal, vec3 direction, vec3 pos, float shininess)
{
    vec3 V = normalize(-pos);
    vec3 H = normalize(-direction + V);
    float N_dot_H = max(dot(normal, H), 0.0);

    return pow(N_dot_H, shininess);
}

void main()
{
    // Diffuse color
    vec4 diffuseColor = material.diffuseColor;
    if (material.bUseDiffuseTexture)
        diffuseColor = texture(
            material.diffuseTexture, vec2(texCoord.x * material.tilingX, texCoord.y * material.tilingY));
    
    // Specular color
    vec4 specularColor = vec4(material.specularColor, 1.0);
    if (material.bUseSpecularTexture)
        specularColor *= texture(
            material.specularTexture, vec2(texCoord.x * material.tilingX, texCoord.y * material.tilingY)).r;

    vec3 light = vec3(0.0);

    // Directional lights
    vec3 dir = normalize(vec3(0.01, -0.5, -0.5));

    light += 0.4 * calc_lambertian(normalCoord, dir) * vec3(1.0);
    light += material.specularIntensity * calc_blinn_phong(normalCoord, dir, posCoord, material.shininess) * vec3(specularColor);

    fColor = vec4(light, 1.0) * diffuseColor;
}