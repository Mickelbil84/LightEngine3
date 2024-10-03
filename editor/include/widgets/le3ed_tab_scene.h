#pragma once

#include <map>

#include <le3.h>

namespace le3 {
    class LE3EditorTabScene {
    public:
        void init();
        void update();

    private:
        void recurseSceneTree(LE3ObjectPtr obj);

        ImGuiTableFlags flags;
        bool m_bShowEngineObjects = false;
        std::map<std::string, bool> m_openStatus;
    };
}