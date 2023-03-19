#pragma once

#include <gl/glew.h>

struct LE3ShadowMap
{
    LE3ShadowMap();
    void Init(GLuint shadowMapWidth, GLuint shadowMapHeight);
    void Clear(); // Clear the framebuffer and the texture
    
    void Bind();
    void Unbind();

    GLuint fbo;
    GLuint texId;
    GLuint bindIdx;
    GLuint width, height;
};