#version 410 core

layout(location = 0) in vec4 vPosition;
layout(location = 1) in vec2 vTexCoord;

uniform vec3 position;
uniform vec2 scale;

uniform float aspectRatio;

void main()
{
    vec4 pos = vec4(vPosition.x, aspectRatio * vPosition.z, -1.0, 1.0);
    gl_Position = pos;
}