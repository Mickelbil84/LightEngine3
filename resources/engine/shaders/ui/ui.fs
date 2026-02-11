#version 410 core

out vec4 outColor;

#define UI_OBJECT_BASE 0
#define UI_OBJECT_HOVERED 1
#define UI_OBJECT_SELECTED 2

struct Material
{
    sampler2D diffuseTexture;
    bool bUseDiffuseTexture;
};

uniform Material material;
uniform vec4 baseColor, hoveredColor, selectedColor;
uniform int state;
uniform vec2 cropBottomLeft, cropTopRight;

in vec2 texCoord;

void main() {
    vec2 uv = vec2(
        cropBottomLeft.x + texCoord.x * (cropTopRight.x - cropBottomLeft.x),
        cropBottomLeft.y + texCoord.y * (cropTopRight.y - cropBottomLeft.y)
    );
    vec4 textureColor = 
        int(material.bUseDiffuseTexture) * texture(material.diffuseTexture, uv) + 
        (1 - int(material.bUseDiffuseTexture)) * vec4(1.0, 1.0, 1.0, 1.0);

    vec4 colorOverride = 
        (1 - min(1, state ^ UI_OBJECT_BASE)) * baseColor +
        (1 - min(1, state ^ UI_OBJECT_HOVERED)) * hoveredColor * 0.8 +
        (1 - min(1, state ^ UI_OBJECT_SELECTED)) * selectedColor * 0.6
    ;
    outColor = colorOverride * textureColor;
}