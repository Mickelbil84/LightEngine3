#version 410 core

layout(location = 0) in vec4 vPosition;
layout(location = 1) in vec2 vTexCoord;
layout(location = 2) in vec3 vNormal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec2 texCoord;
out vec4 normalColor;

void main()
{
    gl_Position = projection * view * model * vPosition;
    normalColor = vec4(vNormal, 1.0);
    texCoord = vTexCoord;
}