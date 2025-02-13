#pragma once

#include <le3.h>
#include <imfilebrowser.h>

#include "le3ed_project.h"

namespace le3 {
    class LE3EditorProjectBrowser : public LE3GameLogic  {
    public:
        virtual void init();
        virtual void render();

    private:
        ImGui::FileBrowser m_fileBrowser;

        // A valid folder is either empty or containing a project file
        bool isValidProjectDir(std::string dir);
    };

}