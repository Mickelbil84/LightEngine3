#pragma once

#include <le3.h>

#include "le3ed_tab_scene.h"
#include "le3ed_tab_content.h"

namespace le3 {
    class LE3EditorSidepanelTop {
    public:
        void init();
        void update();

    private:
        LE3EditorTabScene m_tabScene;
        LE3EditorTabContent m_tabContent;
    };
}