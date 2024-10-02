#pragma once

#include <le3.h>

#include "le3ed_gui.h"

namespace le3 {
    class LE3EditorLogic  : public LE3GameLogic {
    public:
        LE3EditorLogic();

        void init();
        void update(float deltaTime);
        void render();
        void renderDebug();
        void handleInput(LE3Input input);

    private:
        LE3EditorGUI m_gui;
    };
}