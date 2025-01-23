#pragma once

#include "widgets/le3ed_popup.h"

namespace le3 {
    const std::string LE3ED_POP_REPARENT = "Reparent";

    class LE3EditorPopReparent : public LE3EditorPopup {
    public:
        virtual void init() override;
        virtual void update() override;

    private:
        std::string m_objName, m_newParentName;

        void setNameString(std::string& str);
    };
}