#pragma once

#include <vector>

#include <le3.h>
#include "le3ed_popup.h"
#include "le3ed_constants.h"
#include "le3ed_toolbar_button.h"

namespace le3 {
    class LE3EditorToolbar {
    public:
        void init();
        void update();

    private:
        std::vector<LE3EditorToolbarButton> m_buttons;
        std::map<std::string, LE3EditorPopup*> m_popups;
    };
}