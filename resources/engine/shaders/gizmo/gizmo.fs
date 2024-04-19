#version 410 core

in vec3 gizmoColor;

out vec4 outColor;

void main() {
    outColor = vec4(gizmoColor, 1.0);
}