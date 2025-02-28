#pragma once

#include <vector>
#include <string>

#include "widgets/le3ed_popup.h"

namespace le3 {
    const std::string LE3ED_POP_LOAD_SCENE = "Open Scene";

    class LE3EdPopLoadScene : public LE3EditorPopup {
    public:
        virtual void init() override;
        virtual void update() override;

    private:
        std::vector<std::string> m_availableScenes;
        int m_selectionIdx = 0;
    };
}