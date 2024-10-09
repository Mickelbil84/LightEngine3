#pragma once

#include <le3.h>

namespace le3 {
    class LE3EditorSettingsPanel {
    public:
        void init();
        void update();

    private:
        void updateSnapSettings();
        void updateSceneSettings();
    };
}