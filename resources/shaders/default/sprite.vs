#version 410 core

layout(location = 0) in vec4 vPosition;
layout(location = 1) in vec2 vTexCoord;
layout(location = 2) in vec3 vNormal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec2 texCoord;
out vec4 normalColor;

#define FIXED_POINT 100.0

void main()
{
    float scale = length(vec3(model[0][0], model[1][0], model[2][0]));
    mat4 model_norot = mat4(model);
    model_norot[0][0] = scale; model_norot[0][1] = 0.0; model_norot[0][2] = 0.0;
    model_norot[1][0] = 0.0; model_norot[1][1] = scale; model_norot[1][2] = 0.0;
    model_norot[2][0] = 0.0; model_norot[2][1] = 0.0; model_norot[2][2] = scale;

    mat4 inv_view = mat4(view);
    inv_view[3][0] = 0.0;
    inv_view[3][1] = 0.0;
    inv_view[3][2] = 0.0;
    inv_view = inverse(inv_view);
    gl_Position = projection * view  * model_norot * inv_view * vPosition;
    normalColor = vec4(vNormal, 1.0);
    texCoord = vTexCoord;
}