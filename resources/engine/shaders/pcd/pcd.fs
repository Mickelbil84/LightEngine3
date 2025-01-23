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

uniform float opacity;

out vec4 fColor;

in vec3 pos;
in vec3 normal;
in vec3 color;

float rand(vec2 co){
    return fract(sin(dot(co, vec2(12.9898, 78.233))) * 43758.5453);
}

float calc_lambertian(vec3 normal, vec3 direction)
{
    return max(dot(-direction, normal), 0.0);
}

vec3 calc_ambient_light(AmbientLight ambientLight)
{
    return ambientLight.intensity * ambientLight.color;
}

vec3 calc_directional_light(DirectionalLight directionalLight, vec3 normal, vec3 pos, Material material, vec3 specularColor)
{
    float l = calc_lambertian(normal, directionalLight.direction);

    return directionalLight.intensity * (1.0) *
        (l * vec3(1.0)) * directionalLight.color;
}

vec3 calc_point_light(PointLight pointLight, vec3 normal, vec3 pos, Material material, vec3 specularColor)
{
    vec3 direction = pos - pointLight.position;
    float dir_len = length(direction);
    direction = direction / dir_len;

    float attn = 1 / (pointLight.attn_const + pointLight.attn_linear * dir_len + pointLight.attn_exp * dir_len * dir_len + 0.0000001);
    float l = calc_lambertian(normal, direction);

    return pointLight.intensity * attn *
        (l * vec3(1.0)) * pointLight.color;
}

vec3 calc_spot_light(SpotLight spotLight, vec3 normal, vec3 pos, Material material, vec3 specularColor)
{
    vec3 direction = pos - spotLight.position;
    direction = normalize(direction);

    float l = calc_lambertian(normal, direction);

    float theta = dot(direction, normalize(spotLight.direction));
    float epsilon = spotLight.cutoff - spotLight.outer_cutoff + 0.00000001;
    float spotIntensity = clamp((theta - spotLight.outer_cutoff) / epsilon, 0.0, 1.0);
    
    return spotLight.intensity * spotIntensity * (1.0) *
        (l * vec3(1.0)) * spotLight.color;
}

void main()
{
    vec4 diffuseColor = material.diffuseColor * vec4(color, 1.0);
    vec4 specularColor = vec4(material.specularColor, 1.0);        

    vec3 light = vec3(0.0);
    light += calc_ambient_light(ambientLight);
    for (int i = 0; i < MAX_DIRECTIONAL_LIGHTS; i++)
        light += calc_directional_light(directionalLights[i], normal, pos, material, vec3(specularColor));
    for (int i = 0; i < MAX_POINT_LIGHTS; i++)
        light += calc_point_light(pointLights[i], normal, pos, material, vec3(specularColor));
    for (int i = 0; i < MAX_SPOT_LIGHTS; i++)
        light += calc_spot_light(spotLights[i], normal, pos, material, vec3(specularColor));

    fColor = vec4(light, opacity) * diffuseColor;
}