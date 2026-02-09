#version 410 core

layout(location = 0) in vec4 vPosition;
layout(location = 1) in vec2 vTexCoord;

uniform vec3 position;
uniform vec2 scale;

uniform float aspectRatio; // Ignored for now

void main()
{
    vec4 pos = vec4(vPosition.x, vPosition.z, -1.0, 1.0);
    pos = pos * vec4(scale, 1.0, 1.0) + vec4(position, 0.0);
    gl_Position = pos;
}