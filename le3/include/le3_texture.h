#pragma once

#include <memory>
#include <vector>
#include <string>

namespace le3 {
    class LE3Texture {
    public:
        LE3Texture(std::vector<unsigned char> data, int width, int height, int nChannels, bool interpolate);
        ~LE3Texture();

        void use(uint32_t activeTexture = 0);

        inline uint32_t getTextureID() const { return m_texture; }

        inline std::string getName() const { return m_name; }
        inline void setName(std::string name) { m_name = name; }


    protected:
        uint32_t m_texture = -1;
        std::string m_name;
    };
    using LE3TexturePtr = std::shared_ptr<LE3Texture>;
}