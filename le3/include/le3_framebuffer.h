#pragma once

#include <memory>

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

        void useColorTexture();
        void useDepthTexture();

    protected:
        uint32_t m_fbo = -1;
        uint32_t m_color = -1, m_depthStencil = -1;

        int m_width, m_height;
    };
    
    using LE3FramebufferPtr = std::shared_ptr<LE3Framebuffer>;
}