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

uniform bool bIsSkeletal;
uniform mat4 boneMatrices[MAX_NUM_BONES];

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
}