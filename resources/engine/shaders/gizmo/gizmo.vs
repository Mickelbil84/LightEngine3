#version 410 core

layout(location = 0) in vec4 vPosition;
layout(location = 2) in vec3 vNormal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform int gizmoAxis;

out vec3 normal;
out vec3 gizmoColor;

mat4 getGizmoAxisRot() {
    if (gizmoAxis == 0) {
        return mat4(
            0, 1, 0, 0,
            1, 0, 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1
        );
    }
    if (gizmoAxis == 2) {
        return mat4(
            1, 0, 0, 0,
            0, 0, 1, 0,
            0, 1, 0, 0,
            0, 0, 0, 1
        );
    }
    return mat4(1.0);
}

vec3 getGizmoColor() {
    if (gizmoAxis == 0) return vec3(1, 0, 0);
    if (gizmoAxis == 1) return vec3(0, 1, 0);
    if (gizmoAxis == 2) return vec3(0, 0, 1);
    return vec3(0.8);
}

void main() {
    gl_Position = projection * view * model * getGizmoAxisRot() * vPosition;
    normal = vNormal;
    gizmoColor = getGizmoColor();
}