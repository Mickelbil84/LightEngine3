#pragma once

#include <memory>

#include <glm/glm.hpp>

namespace le3 {
    
    enum LE3FramebufferType {
        LE3_FRAMEBUFFER_COLOR_DEPTH_STENCIL,
        LE3_FRAMEBUFFER_DEPTH_STENCIL,
    };

    class LE3Framebuffer {
    public:
        LE3Framebuffer(int width, int height, LE3FramebufferType type, bool interpolate);
        ~LE3Framebuffer();

        void bind();

        void useColorTexture(int i = 0);
        void useDepthTexture(int i = 0);

        // This is a helper, useful for shadowmaps
        // The bindnig index of the buffer textures is done manually anyway
        void setBindIdx(int idx) { m_bindIdx = idx; }
        uint32_t getBindIdx() const { return m_bindIdx; }

        uint32_t getColorTexture() const { return m_color; }
        uint32_t getDepthStencilTexture() const { return m_depthStencil; }

        inline int getWidth() const { return m_width; }
        inline int getHeight() const { return m_height; }

        glm::vec4 readPixel(glm::vec2 pos);

    protected:
        uint32_t m_fbo = -1;
        uint32_t m_color = -1, m_depthStencil = -1;
        uint32_t m_bindIdx = 0;

        int m_width, m_height;
    };
    
    using LE3FramebufferPtr = std::shared_ptr<LE3Framebuffer>;
}