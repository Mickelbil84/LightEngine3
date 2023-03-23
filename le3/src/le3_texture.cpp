#include "le3_texture.h"
#include "le3_print.h"

#include <iostream>
#include <sstream>
#include <vector>
#include <map>

#include <fmt/core.h>
using fmt::print;

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

bool LE3Texture::g_bPS1TextureMode = false;

void LE3Texture::Load(std::string filePath)
{
    // First load the data
    int x, y, n;
    unsigned char* data;
    
    if (filePath.find(std::string("/* XPM */")) != std::string::npos)
    {
        data = LE3Texture::LoadXPM(filePath, &x, &y, &n);
        // return;
    }
    else
        data = stbi_load(filePath.c_str(), &x, &y, &n, 0);

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
    if (!LE3Texture::g_bPS1TextureMode)
    {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }
    else
    {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    }
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

void LE3Texture::SetName(std::string name)
{
    this->m_name = name;
}
std::string LE3Texture::GetName() const
{
    return this->m_name;
}

unsigned char* LE3Texture::LoadXPM(std::string xpmStr, int* x, int* y, int* n)
{
    std::istringstream ss(xpmStr);
    std::string line;
    enum {XPM_VALUES, XPM_COLORS, XPM_PIXELS, XPM_DONE};
    int curr_state = XPM_VALUES;

    int idx = 0, j;
    unsigned char* img;
    std::map<char, glm::ivec4> char_table;
    while (std::getline(ss, line))
    {
        // Skip comment lines
        if (line.find("/*") != std::string::npos || line.find("*/") != std::string::npos) continue;

        std::istringstream lss(line);
        int width, height, char_table_size;
        std::string color;
        char c, tmp;
        glm::ivec4 tmpv;

        switch (curr_state)
        {
        case XPM_VALUES:
            lss >> width;
            lss >> height; 
            lss >> char_table_size;

            *x = width;
            *y = height;
            *n = 4;
            img = new unsigned char[width * height * 4];
            curr_state = XPM_COLORS;
            break;
        
        case XPM_COLORS:
            c = line[0];
            color = line.substr(4);
            
            if (color == "None")
                tmpv = glm::ivec4(0);
            else
            {
                tmpv.r = std::stoi(color.substr(1,2), 0, 16);
                tmpv.g = std::stoi(color.substr(3,2), 0, 16);
                tmpv.b = std::stoi(color.substr(5,2), 0, 16);
                tmpv.a = 255;
            }

            char_table[c] = tmpv;

            idx++;
            if (idx == char_table_size)
            {
                idx = 0;
                curr_state = XPM_PIXELS;
            }
            break;

        case XPM_PIXELS:
            for (j = 0; j < width; j++)
            {
                tmpv = char_table[line[j]];
                img[(height - 1 - idx) * width * 4 + j * 4 + 0] = tmpv.r;
                img[(height - 1 - idx) * width * 4 + j * 4 + 1] = tmpv.g;
                img[(height - 1 - idx) * width * 4 + j * 4 + 2] = tmpv.b;
                img[(height - 1 - idx) * width * 4 + j * 4 + 3] = tmpv.a;
            }

            idx++;
            if (idx == height)
                curr_state = XPM_DONE;
            break;

        default:
            break;
        }
    }

    return img;
}