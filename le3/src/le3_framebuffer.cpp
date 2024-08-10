#include "le3_framebuffer.h"
using namespace le3;

#include <stdexcept>

#ifdef __linux__
#include <GL/glew.h>
#else
#include <gl/glew.h>
#endif


LE3Framebuffer::LE3Framebuffer(int width, int height, LE3FramebufferType type, bool interpolate) : m_width(width), m_height(height) {
    glGenFramebuffers(1, &m_fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);

    GLint flag = interpolate ? GL_LINEAR : GL_NEAREST;
    // Attach color texture (if applicable)
    if (type == LE3FramebufferType::LE3_FRAMEBUFFER_COLOR_DEPTH_STENCIL) {
        glGenTextures(1, &m_color);
        glBindTexture(GL_TEXTURE_2D, m_color);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, flag);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, flag);  
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_color, 0);
    }

    // Attach depth+stencil texture
    glGenTextures(1, &m_depthStencil);
    glBindTexture(GL_TEXTURE_2D, m_depthStencil);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, m_width, m_height, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, flag);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, flag); 
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER); 
    float borderColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, m_depthStencil, 0);
    
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        throw std::runtime_error("Could not create a complete framebuffer");
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
    
LE3Framebuffer::~LE3Framebuffer() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    if (m_fbo > 0) glDeleteFramebuffers(1, &m_fbo);
}
    
void LE3Framebuffer::bind()
{
    glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
}

void LE3Framebuffer::useColorTexture(int i)
{
    glActiveTexture(GL_TEXTURE0 + i);
    glBindTexture(GL_TEXTURE_2D, m_color);
}

void LE3Framebuffer::useDepthTexture(int i)
{
    glActiveTexture(GL_TEXTURE0 + i);
    glBindTexture(GL_TEXTURE_2D, m_depthStencil);
}

glm::vec4 LE3Framebuffer::readPixel(glm::vec2 pos) {
    bind();
    glReadBuffer(GL_COLOR_ATTACHMENT0);
    glm::vec4 pixel;
    glReadPixels((int)pos.x, (int)pos.y, 1, 1, GL_RGBA, GL_FLOAT, &pixel[0]);
    return pixel;
}