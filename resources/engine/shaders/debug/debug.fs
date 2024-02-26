#version 410 core

uniform vec3 debugColor;
out vec4 outColor;

void main() {
    outColor = vec4(debugColor, 1.0);
}