#version 410 core

in vec3 normal;
in vec3 gizmoColor;

out vec4 outColor;

void main() {
    vec3 lightDir = normalize(vec3(1, 1, 1));
    float ambient = 0.7;
    float alpha = ambient + clamp(dot(lightDir, normal), 0, 1);
    outColor = vec4(alpha * gizmoColor, 1.0);
}