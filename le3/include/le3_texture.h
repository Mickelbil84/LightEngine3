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

    static bool g_bPS1TextureMode;

private:
    static unsigned char* LoadXPM(std::string xpmStr, int* x, int* y, int* n);

    GLuint m_texture;
    std::string m_name;
};
