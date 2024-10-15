#pragma once

#include "widgets/le3ed_popup.h"

namespace le3 {
    const std::string LE3ED_POP_ADD_MATERIAL = "Add Material";

    class LE3EdPopAddMaterial : public LE3EditorPopup {
    public:
        virtual void init() override;
        virtual void update() override;

    private:
        char m_materialName[256] = {0};
        char m_shaderName[256] = {0};
    };
}