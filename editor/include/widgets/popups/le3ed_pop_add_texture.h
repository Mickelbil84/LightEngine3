#pragma once

#include "widgets/le3ed_popup.h"

namespace le3 {
    const std::string LE3ED_POP_ADD_TEXTURE = "Add Texture";

    class LE3EdPopAddTexture : public LE3EditorPopup {
    public:
        virtual void init() override;
        virtual void update() override;

    private:
        char m_textureName[256] = {0};
        char m_path[1024] = {0};
        bool m_bInterpolate = true;
    };
}