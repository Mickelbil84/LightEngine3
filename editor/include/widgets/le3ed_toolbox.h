#pragma once

#include <vector>

#include <le3.h>
#include "le3ed_constants.h"
#include "le3ed_toolbar_button.h"

namespace le3 {
    class LE3EditorToolbox {
    public:
        void init();
        void update();

    private:
        std::vector<LE3EditorToolbarButton> m_buttons;
    };
}