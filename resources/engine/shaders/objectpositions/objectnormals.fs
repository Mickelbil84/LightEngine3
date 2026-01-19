#version 410 core

in vec3 normalCoord;
out vec4 color;

void main() {
    color = vec4(normalCoord, 1.0);
}