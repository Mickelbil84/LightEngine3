#version 410 core

out vec4 outColor;

#define UI_OBJECT_BASE 0u
#define UI_OBJECT_HOVERED 1u
#define UI_OBJECT_SELECTED 2u

uniform vec4 baseColor, hoveredColor, selectedColor;
uniform uint state;

void main() {
    vec4 colorOverride = 
        (1u - min(1u, state ^ UI_OBJECT_BASE)) * baseColor +
        (1u - min(1u, state ^ UI_OBJECT_HOVERED)) * hoveredColor +
        (1u - min(1u, state ^ UI_OBJECT_SELECTED)) * selectedColor
    ;
    outColor = colorOverride;
}