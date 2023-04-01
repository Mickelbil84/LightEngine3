#version 410 core

#define MAX_DIRECTIONAL_LIGHTS 4
#define MAX_SPOT_LIGHTS 2

#define MAX_BONES_PER_VERTEX 8
#define MAX_NUM_BONES 100

layout(location = 0) in vec4 vPosition;
layout(location = 1) in vec2 vTexCoord;
layout(location = 2) in vec3 vNormal;
layout(location = 4) in vec3 vTangent;
layout(location = 5) in vec3 vBitangent;

layout(location = 6) in ivec4 vBones;
layout(location = 7) in vec4 vWeights;
layout(location = 8) in ivec4 vBones2;
layout(location = 9) in vec4 vWeights2;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 dirLightViewMatrix[MAX_DIRECTIONAL_LIGHTS];
uniform mat4 spotLightViewMatrix[MAX_SPOT_LIGHTS];

uniform bool bIsSkeletal;
uniform mat4 boneMatrices[MAX_NUM_BONES];

out vec2 texCoord;
out vec3 posCoord;
out vec4 dirLightPosCoord[MAX_DIRECTIONAL_LIGHTS];
out vec4 spotLightPosCoord[MAX_SPOT_LIGHTS];
out vec3 normalCoord;
out mat3 tbn;

void main()
{
    vec4 position = vPosition;
    if (bIsSkeletal)
    {
        position = vec4(0.0);
        for (int i = 0; i < MAX_BONES_PER_VERTEX; i++)
        {
            if (i < 4)
            {
                if (vBones[i] < 0) continue;
                if (vBones[i] >= MAX_NUM_BONES)
                {
                    position = vPosition;
                    break;
                }
                vec4 deltaPos = boneMatrices[vBones[i]] * vPosition;
                position += deltaPos * vWeights[i];
            }
            else
            {
                if (vBones2[i-4] < 0) continue;
                if (vBones2[i-4] >= MAX_NUM_BONES)
                {
                    position = vPosition;
                    break;
                }
                vec4 deltaPos = boneMatrices[vBones2[i-4]] * vPosition;
                position += deltaPos * vWeights2[i-4];
            }
        }

        position.w = 1.0;
    }

    gl_Position = projection * view * model * position;
    texCoord = vTexCoord;
    posCoord = vec3(model * position);
    
    for (int i = 0; i < MAX_DIRECTIONAL_LIGHTS; i++)
        dirLightPosCoord[i] = dirLightViewMatrix[i] * vec4(posCoord, 1.0);
    for (int i = 0; i < MAX_SPOT_LIGHTS; i++)
        spotLightPosCoord[i] = spotLightViewMatrix[i] * vec4(posCoord, 1.0);

    mat3 normal_mtx = mat3(transpose(inverse(model)));
    normalCoord = normalize(normal_mtx * vNormal);

    vec3 T = normalize(normal_mtx * vTangent);
    vec3 B = normalize(normal_mtx * vBitangent);
    vec3 N = normalize(normal_mtx * vNormal);
    tbn = mat3(T, B, N);
}