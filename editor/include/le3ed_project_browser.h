#pragma once

#include <le3.h>
#include <imfilebrowser.h>

namespace le3 {
    class LE3EditorProjectBrowser : public LE3GameLogic  {
    public:
        virtual void init();
        virtual void render();

    private:
        ImGui::FileBrowser m_fileBrowser;
    };

}