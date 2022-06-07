#version 430 core

layout(location = 0) in vec4 vPosition;
layout(location = 4) in vec4 vColor;

out vec4 color;

void main()
{
    gl_Position = vPosition;
    color = vColor;
}