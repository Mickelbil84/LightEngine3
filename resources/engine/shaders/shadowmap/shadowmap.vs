#version 410 core

layout(location = 0) in vec4 vPosition;
layout(location = 6) in ivec4 vBones;
layout(location = 7) in vec4 vWeights;
layout(location = 8) in ivec4 vBones2;
layout(location = 9) in vec4 vWeights2;

uniform mat4 model;
uniform mat4 lightMatrix;
uniform bool bIsSkeletal;
uniform mat4 boneMatrices[100];

void main()
{
    vec4 position = vPosition;
    if (bIsSkeletal)
        {
            position = vec4(0.0);
            for (int i = 0; i < 8; i++)
            {
                if (i < 4)
                {
                    if (vBones[i] < 0) continue;
                    vec4 deltaPos = boneMatrices[vBones[i]] * vPosition;
                    position += deltaPos * vWeights[i];
                }
                else
                {
                    if (vBones2[i-4] < 0) continue;
                    vec4 deltaPos = boneMatrices[vBones2[i-4]] * vPosition;
                    position += deltaPos * vWeights2[i-4];
                }
         }
            position.w = 1.0;
        }

    gl_Position = lightMatrix * model * position;
}