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

    void SetName(std::string name);
    std::string GetName() const;

private:
    GLuint m_texture;
    std::string m_name;
};
