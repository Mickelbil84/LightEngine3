#version 410 core

#define MAX_DIRECTIONAL_LIGHTS 4
#define MAX_SPOT_LIGHTS 2

layout(location = 0) in vec4 vPosition;
layout(location = 1) in vec2 vTexCoord;
layout(location = 2) in vec3 vNormal;
layout(location = 4) in vec3 vTangent;
layout(location = 5) in vec3 vBitangent;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 dirLightViewMatrix[MAX_DIRECTIONAL_LIGHTS];

out vec2 texCoord;
out vec3 posCoord;
out vec4 dirLightPosCoord[MAX_DIRECTIONAL_LIGHTS];
out vec3 normalCoord;
out mat4 viewMat;
out mat3 tbn;

void main()
{
    mat4 view_model = view * model;
    gl_Position = projection * view_model * vPosition;
    texCoord = vTexCoord;
    vec4 posCoordTmp = view_model * vPosition;
    posCoord = vec3(posCoordTmp);
    
    vec3 fragPos = vec3(model * vPosition);
    for (int i = 0; i < MAX_DIRECTIONAL_LIGHTS; i++)
        dirLightPosCoord[i] = dirLightViewMatrix[i] * vec4(fragPos, 1.0);

    mat3 normal_mtx = transpose(inverse(mat3(view_model)));
    normalCoord = normalize(normal_mtx * vNormal);

    viewMat = view;

    vec3 T = normalize(normal_mtx * vTangent);
    vec3 B = normalize(normal_mtx * vBitangent);
    vec3 N = normalize(normal_mtx * vNormal);
    tbn = mat3(T, B, N);
}