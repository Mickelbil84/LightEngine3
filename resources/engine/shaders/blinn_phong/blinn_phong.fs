#version 400 core

#define MAX_DIRECTIONAL_LIGHTS 4
#define MAX_POINT_LIGHTS 8
#define MAX_SPOT_LIGHTS 2

#define M_PI 3.1415926535897932384626433832795

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

    sampler2D cubemapTexture;
    float reflectionIntensity;

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

    bool bEnableShadows;
    sampler2D shadowMap;
};
uniform SpotLight spotLights[MAX_SPOT_LIGHTS];

uniform vec3 cameraPos;

out vec4 fColor;

in vec2 texCoord;
in vec3 posCoord;
in vec4 dirLightPosCoord[MAX_DIRECTIONAL_LIGHTS];
in vec4 spotLightPosCoord[MAX_SPOT_LIGHTS];
in vec3 normalCoord;
in mat3 tbn;

float rand(vec2 co){
    return fract(sin(dot(co, vec2(12.9898, 78.233))) * 43758.5453);
}

float calc_lambertian(vec3 normal, vec3 direction)
{
    return max(dot(-direction, normal), 0.0);
}

float calc_blinn_phong(vec3 normal, vec3 direction, vec3 pos, float shininess)
{
    vec3 V = normalize(cameraPos - pos);
    vec3 H = normalize(-direction + V);
    float N_dot_H = max(dot(normal, H), 0.0);

    return pow(N_dot_H, shininess);
}

float calc_shadow(vec4 posLightSpace, sampler2D shadowMap, vec3 normal, vec3 lightDir)
{
    vec3 projCoords = posLightSpace.xyz / posLightSpace.w;
    projCoords = projCoords * 0.5 + 0.5;
    float currentDepth = projCoords.z;
    if (currentDepth > 1.0)
        return 0.0;
    
    float bias = max(0.001 * (1.0 - dot(normal, -lightDir)), 0.0001);
    float shadow = 0.0; //currentDepth - bias > closestDepth  ? 1.0 : 0.0;
    vec2 texelSize = 1.0 / textureSize(shadowMap, 0);
    for (int x = -2; x <= 2; x++)
    for (int y = -2; y <= 2; y++)
    {
        float depth = texture(shadowMap, projCoords.xy + vec2(x, y) * texelSize).r;
        shadow += (currentDepth - bias > depth ? 1.0 : 0.0);
    }
    shadow /= 25.0;

    return shadow;
}

vec3 calc_reflection(vec3 normal)
{
    vec3 dir = reflect(normalize(posCoord - cameraPos), normal);
    vec2 uv = vec2(
        // atan(-dir.z / -dir.x) * 2.0 / M_PI + 0.5,
        // asin(dir.y) / M_PI + 0.5
        acos(dir.x) + 1.0,
        acos(dir.y / length(dir.zy)) + 1.0
    ) * 0.2;
    return texture(material.cubemapTexture, uv).rgb;
}

vec3 calc_ambient_light(AmbientLight ambientLight)
{
    return ambientLight.intensity * ambientLight.color;
}

vec3 calc_directional_light(DirectionalLight directionalLight, vec3 normal, vec3 pos, vec4 posLightSpace, Material material, vec3 specularColor)
{
    float l = calc_lambertian(normal, directionalLight.direction);
    float bp = calc_blinn_phong(normal, directionalLight.direction, pos, material.shininess);

    float shadow = 0.0;
    if (directionalLight.bEnableShadows)
        shadow = calc_shadow(posLightSpace, directionalLight.shadowMap, normal, directionalLight.direction);

    return directionalLight.intensity * (1.0 - shadow) *
        (bp * material.specularIntensity * specularColor + l * vec3(1.0)) * directionalLight.color;
}

vec3 calc_point_light(PointLight pointLight, vec3 normal, vec3 pos, Material material, vec3 specularColor)
{
    vec3 direction = pos - pointLight.position;
    float dir_len = length(direction);
    direction = direction / dir_len;

    float attn = 1 / (pointLight.attn_const + pointLight.attn_linear * dir_len + pointLight.attn_exp * dir_len * dir_len + 0.0000001);
    float l = calc_lambertian(normal, direction);
    float bp = calc_blinn_phong(normal, direction, pos, material.shininess);

    return pointLight.intensity * attn *
        (bp * material.specularIntensity * specularColor + l * vec3(1.0)) * pointLight.color;
}

vec3 calc_spot_light(SpotLight spotLight, vec3 normal, vec3 pos, vec4 posLightSpace, Material material, vec3 specularColor)
{
    vec3 direction = pos - spotLight.position;
    direction = normalize(direction);

    float l = calc_lambertian(normal, direction);
    float bp = calc_blinn_phong(normal, direction, pos, material.shininess);

    float theta = dot(direction, normalize(spotLight.direction));
    float epsilon = spotLight.cutoff - spotLight.outer_cutoff + 0.00000001;
    float spotIntensity = clamp((theta - spotLight.outer_cutoff) / epsilon, 0.0, 1.0);

    float shadow = 0.0;
    if (spotLight.bEnableShadows)
        shadow = calc_shadow(posLightSpace, spotLight.shadowMap, normal, direction);
    
    return spotLight.intensity * spotIntensity * (1.0 - shadow) *
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
        
    // Reflections
    if (material.reflectionIntensity > 0.0)
    {
        float specReflection = 0.333 * (specularColor.r + specularColor.g + specularColor.b);
        float alpha = clamp(material.reflectionIntensity * specReflection, 0.0, 1.0);
        diffuseColor = alpha * vec4(calc_reflection(normal), 1.0) + (1.0 - alpha) * diffuseColor; 
    }

    vec3 light = vec3(0.0);
    light += calc_ambient_light(ambientLight);
    for (int i = 0; i < MAX_DIRECTIONAL_LIGHTS; i++)
        light += calc_directional_light(directionalLights[i], normal, posCoord, dirLightPosCoord[i], material, vec3(specularColor));
    for (int i = 0; i < MAX_POINT_LIGHTS; i++)
        light += calc_point_light(pointLights[i], normal, posCoord, material, vec3(specularColor));
    for (int i = 0; i < MAX_SPOT_LIGHTS; i++)
        light += calc_spot_light(spotLights[i], normal, posCoord, spotLightPosCoord[i], material, vec3(specularColor));

    fColor = vec4(light, 1.0) * diffuseColor;
    // fColor = diffuseColor;
}