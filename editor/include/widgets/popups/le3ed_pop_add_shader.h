#pragma once

#include "widgets/le3ed_popup.h"

namespace le3 {
    const std::string LE3ED_POP_ADD_SHADER = "Add Shader";

    class LE3EdPopAddShader : public LE3EditorPopup {
    public:
        virtual void init() override;
        virtual void update() override;

    private:
        char m_shaderName[256] = {0};
        char m_pathVS[1024] = {0};
        char m_pathFS[1024] = {0};
    };
}