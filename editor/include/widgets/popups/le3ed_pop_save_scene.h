#pragma once

#include <vector>
#include <string>

#include "widgets/le3ed_popup.h"

namespace le3 {
    const std::string LE3ED_POP_SAVE_SCENE = "Save Scene";

    class LE3EdPopSaveScene : public LE3EditorPopup {
    public:
        virtual void init() override;
        virtual void update() override;

    private:
        char m_sceneName[1024];
    };
}