#pragma once

#include <vector>

#include "components/le3ed_gui.h"
#include "components/le3ed_scenes.h"

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
        std::vector<LE3EditorComponent*> m_pComponents;
        LE3EditorGUI m_gui;
        LE3EditorScenes m_scenes;
    };
}