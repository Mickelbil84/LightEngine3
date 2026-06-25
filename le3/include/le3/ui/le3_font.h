#pragma once

#include <string>
#include <memory>
#include <vector>

#include "stb_rect_pack.h"
#include "stb_truetype.h"

namespace le3 {

    const int LE3_FONT_ATLAS_WIDTH = 512;
    const int LE3_FONT_ATLAS_HEIGHT = 512;
    const int LE3_FONT_FIRST_CHAR = 32;
    const int LE3_FONT_NUM_CHARS = 96;

    class LE3Font {
    public:
        LE3Font(std::vector<unsigned char> fontFileData, float fontSize);
        ~LE3Font();

        inline std::string getName() const { return m_name; }
        inline void setName(std::string name) { m_name = name; }
        inline float getFontSize() const { return m_fontSize; }

        inline uint32_t getAtlasTextureID() const { return m_atlasTexture; }
        inline int getAtlasWidth() const { return LE3_FONT_ATLAS_WIDTH; }
        inline int getAtlasHeight() const { return LE3_FONT_ATLAS_HEIGHT; }

        const stbtt_packedchar* getPackedChars() const { return m_packedChars; }

    private:
        std::string m_name;
        float m_fontSize;

        stbtt_packedchar m_packedChars[LE3_FONT_NUM_CHARS];
        uint32_t m_atlasTexture = 0;
    };
    using LE3FontPtr = std::weak_ptr<LE3Font>;
}
