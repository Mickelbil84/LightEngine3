#version 410 core

layout(location = 0) in vec4 vPosition;
layout(location = 1) in vec2 vTexCoord;
layout(location = 2) in vec3 vNormal;
layout(location = 3) in vec3 vColor;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 normal;
out vec3 pos;
out vec3 color;

void main()
{
    gl_Position = projection * view * model * vec4(vPosition.xyz, 1.0);
    pos = vec3(model * vPosition);
    normal = vec3(model * vec4(vNormal, 0.0));
    color = vColor;
}