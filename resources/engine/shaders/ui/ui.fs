#version 410 core

out vec4 outColor;

#define UI_OBJECT_BASE 0
#define UI_OBJECT_HOVERED 1
#define UI_OBJECT_SELECTED 2

uniform vec4 baseColor, hoveredColor, selectedColor;
uniform int state;

void main() {
    vec4 colorOverride = 
        (1 - min(1, state ^ UI_OBJECT_BASE)) * baseColor +
        (1 - min(1, state ^ UI_OBJECT_HOVERED)) * hoveredColor * 0.8 +
        (1 - min(1, state ^ UI_OBJECT_SELECTED)) * selectedColor * 0.6
    ;
    outColor = colorOverride;
}