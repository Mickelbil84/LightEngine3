#version 430 core

out vec4 fColor;

in vec4 normalColor;

void main()
{
    fColor = (normalColor + 2) / 3;
}