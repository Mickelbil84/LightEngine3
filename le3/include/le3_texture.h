#pragma once
#include <string>
#include <gl/glew.h>

class LE3Texture
{
public:
    void Load(std::string filePath);
    void Use(GLuint activeTexture = 0);
    void Delete();

    GLuint GetTextureID() const;

private:
    GLuint m_texture;
};
