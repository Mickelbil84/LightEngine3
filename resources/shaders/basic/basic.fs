#version 430 core

uniform sampler2D diffuseTexture;

out vec4 fColor;

in vec2 texCoord;
in vec4 normalColor;

void main()
{
    // fColor = (normalColor + 2) / 3;

    fColor = texture(diffuseTexture, texCoord);
    // fColor = vec4(texCoord.xy, 1, 1);
}