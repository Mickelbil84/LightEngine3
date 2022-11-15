#version 410 core

layout(location = 0) in vec4 vPosition;
layout(location = 1) in vec2 vTexCoord;
layout(location = 2) in vec3 vNormal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

noperspective out vec2 texCoord;
out vec4 normalColor;

#define FIXED_POINT 100.0

void main()
{
    vec4 position = projection * view * model * vPosition;
    
    position.x = int((position.x + 1.0) * 320.0 * 0.5) + 0.5;
    position.y = int((position.y + 1.0) * 240.0 * 0.5) + 0.5;
    position.x = 2.0 * position.x / 320.0 - 1.0;
    position.y = 2.0 * position.y / 240.0 - 1.0;
    // position.w = 1.0;

    gl_Position = position;

    normalColor = vec4(vNormal, 1.0);
    texCoord = vTexCoord;
}