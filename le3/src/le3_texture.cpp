#include "le3_texture.h"
#include "le3_print.h"

#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

void LE3Texture::Load(std::string filePath)
{
    // First load the data
    int x, y, n;
    unsigned char* data = stbi_load(filePath.c_str(), &x, &y, &n, 0);
    if (!data)
    {
        #ifndef NDEBUG
        PrintTitle("Load Texture Error");
        std::cout << "Failed loading texture:\t" << filePath << std::endl;
        #endif
        return;
    }
    GLenum format = GL_RGB;
    if (n == 4)
        format = GL_RGBA;

    glGenTextures(1, &m_texture);
    glBindTexture(GL_TEXTURE_2D, m_texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, format, x, y, 0, format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data);
}

void LE3Texture::Use(GLuint activeTexture)
{
    glActiveTexture(GL_TEXTURE0 + activeTexture);
    glBindTexture(GL_TEXTURE_2D, m_texture);

}

void LE3Texture::Delete()
{
    glDeleteTextures(1, &m_texture);
}

GLuint LE3Texture::GetTextureID() const
{
    return m_texture;
}