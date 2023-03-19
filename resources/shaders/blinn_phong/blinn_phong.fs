#version 410 core

#define MAX_DIRECTIONAL_LIGHTS 2
#define MAX_POINT_LIGHTS 8
#define MAX_SPOT_LIGHTS 2

struct Material
{
    vec4 diffuseColor;
    sampler2D diffuseTexture;
    bool bUseDiffuseTexture;

    vec3 specularColor;
    float specularIntensity, shininess;
    sampler2D specularTexture;
    bool bUseSpecularTexture;

    sampler2D normalTexture;
    bool bUseNormalTexture;

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

    bool bEnableShadows;
    mat4 lightViewMatrix;
    sampler2D shadowMap;
};
uniform DirectionalLight directionalLights[MAX_DIRECTIONAL_LIGHTS];

struct PointLight
{
    vec3 color;
    float intensity;
    vec3 position;

    float attn_const, attn_linear, attn_exp;
};
uniform PointLight pointLights[MAX_POINT_LIGHTS];

struct SpotLight
{
    vec3 color;
    float intensity;
    vec3 position, direction;

    float cutoff, outer_cutoff;

    // bool bEnableShadows;
    // sampler2D shadowMap;
    // mat4 viewMatrix;
};
uniform SpotLight spotLights[MAX_SPOT_LIGHTS];

out vec4 fColor;

in vec2 texCoord;
in vec3 posCoord;
// in vec4 worldPosCoord;
in vec3 normalCoord;
in mat4 viewMat;
in mat3 tbn;

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

// float calc_shadow(vec4 posLightSpace)
// {
//     return 0.0;
// }

vec3 calc_ambient_light(AmbientLight ambientLight)
{
    return ambientLight.intensity * ambientLight.color;
}

vec3 calc_directional_light(DirectionalLight directionalLight, vec3 normal, vec3 pos, Material material, vec3 specularColor)
{
    vec3 direction = vec3(viewMat * vec4(directionalLight.direction, 0.0));
    float l = calc_lambertian(normal, direction);
    float bp = calc_blinn_phong(normal, direction, pos, material.shininess);

    float shadow = 0.0;
    // if (directionalLight.bEnableShadows)
    //     shadow = calc_shadow(directionalLight.viewMatrix * worldPosCoord);

    return directionalLight.intensity * (1.0 - shadow) *
        (bp * material.specularIntensity * specularColor + l * vec3(1.0)) * directionalLight.color;
}

vec3 calc_point_light(PointLight pointLight, vec3 normal, vec3 pos, Material material, vec3 specularColor)
{
    vec3 direction = pos - vec3(viewMat * vec4(pointLight.position, 1.0));
    float dir_len = length(direction);
    direction = direction / dir_len;

    float attn = 1 / (pointLight.attn_const + pointLight.attn_linear * dir_len + pointLight.attn_exp * dir_len * dir_len + 0.0000001);
    float l = calc_lambertian(normal, direction);
    float bp = calc_blinn_phong(normal, direction, pos, material.shininess);

    return pointLight.intensity * attn *
        (bp * material.specularIntensity * specularColor + l * vec3(1.0)) * pointLight.color;
}

vec3 calc_spot_light(SpotLight spotLight, vec3 normal, vec3 pos, Material material, vec3 specularColor)
{
    vec3 direction = pos - vec3(viewMat * vec4(spotLight.position, 1.0));
    direction = normalize(direction);

    float l = calc_lambertian(normal, direction);
    float bp = calc_blinn_phong(normal, direction, pos, material.shininess);

    vec3 spotDirection = vec3(viewMat * vec4(spotLight.direction, 0.0));
    float theta = dot(direction, normalize(spotDirection));
    float epsilon = spotLight.cutoff - spotLight.outer_cutoff + 0.00000001;
    float spotIntensity = clamp((theta - spotLight.outer_cutoff) / epsilon, 0.0, 1.0);
    
    return spotLight.intensity * spotIntensity *
        (bp * material.specularIntensity * specularColor + l * vec3(1.0)) * spotLight.color;
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

    // Normal color
    vec3 normal = normalCoord;
    if (material.bUseNormalTexture)
    {
        normal = texture(
            material.normalTexture, vec2(texCoord.x * material.tilingX, texCoord.y * material.tilingY)).rgb;
        normal = normalize(normal * 2.0 - 1.0);
        normal = normalize(tbn * normal);
    }
        

    vec3 light = vec3(0.0);
    light += calc_ambient_light(ambientLight);
    for (int i = 0; i < MAX_DIRECTIONAL_LIGHTS; i++)
        light += calc_directional_light(directionalLights[i], normal, posCoord, material, vec3(specularColor));
    for (int i = 0; i < MAX_POINT_LIGHTS; i++)
        light += calc_point_light(pointLights[i], normal, posCoord, material, vec3(specularColor));
    for (int i = 0; i < MAX_SPOT_LIGHTS; i++)
        light += calc_spot_light(spotLights[i], normal, posCoord, material, vec3(specularColor));

    fColor = vec4(light, 1.0) * diffuseColor;
}