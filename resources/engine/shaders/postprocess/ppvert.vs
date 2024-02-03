#version 410 core
layout(location = 0) in vec4 vPosition;

out vec2 uv;

void main() {
    gl_Position = vPosition;
    uv = vec2(vPosition.xy * 0.5 + 0.5);
}