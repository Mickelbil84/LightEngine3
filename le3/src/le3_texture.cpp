#include "le3_texture.h"
using namespace le3;

#ifdef __linux__
#include <GL/glew.h>
#else
#include <gl/glew.h>
#endif

LE3Texture::LE3Texture(std::vector<unsigned char> data, int width, int height, int nChannels, bool interpolate) {
    GLenum format = nChannels < 4 ? GL_RGB : GL_RGBA;

    glGenTextures(1, &m_texture);
    glBindTexture(GL_TEXTURE_2D, m_texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    if (!interpolate)
    {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }
    else
    {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    }
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, &data[0]);
    glGenerateMipmap(GL_TEXTURE_2D);
}
LE3Texture::~LE3Texture() {
    if (m_texture >= 0) glDeleteTextures(1, &m_texture);
}

void LE3Texture::use(uint32_t activeTexture) {
    glActiveTexture(GL_TEXTURE0 + activeTexture);
    glBindTexture(GL_TEXTURE_2D, m_texture);
}