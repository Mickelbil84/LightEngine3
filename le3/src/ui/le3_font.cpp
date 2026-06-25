#include "ui/le3_font.h"
using namespace le3;

#ifdef __linux__
#include <GL/glew.h>
#else
#include <gl/glew.h>
#endif

#define STB_RECT_PACK_IMPLEMENTATION
#include "stb_rect_pack.h"

#define STB_TRUETYPE_IMPLEMENTATION
#include "stb_truetype.h"

LE3Font::LE3Font(std::vector<unsigned char> fontFileData, float fontSize) : m_fontSize(fontSize) {
    unsigned char atlasBitmap[LE3_FONT_ATLAS_WIDTH * LE3_FONT_ATLAS_HEIGHT];

    stbtt_pack_context packContext;
    stbtt_PackBegin(&packContext, atlasBitmap, LE3_FONT_ATLAS_WIDTH, LE3_FONT_ATLAS_HEIGHT, 0, 1, nullptr);
    stbtt_PackSetOversampling(&packContext, 2, 2);
    stbtt_PackFontRange(&packContext, fontFileData.data(), 0, fontSize,
        LE3_FONT_FIRST_CHAR, LE3_FONT_NUM_CHARS, m_packedChars);
    stbtt_PackEnd(&packContext);

    glGenTextures(1, &m_atlasTexture);
    glBindTexture(GL_TEXTURE_2D, m_atlasTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, LE3_FONT_ATLAS_WIDTH, LE3_FONT_ATLAS_HEIGHT, 0, GL_RED, GL_UNSIGNED_BYTE, atlasBitmap);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
}

LE3Font::~LE3Font() {
    if (m_atlasTexture) glDeleteTextures(1, &m_atlasTexture);
}
