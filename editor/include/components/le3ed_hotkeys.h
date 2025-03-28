#pragma once

#include "le3ed_component.h"
#include "le3ed_constants.h"

namespace le3 {

    class LE3EditorHotkeys : public LE3EditorComponent{
    public:
        LE3ED_COMPONENT_DEAFULT_CTOR(LE3EditorHotkeys)
        void handleInput(LE3Input input);
        void solveHotkeys(); // Called by the le3ed_gui.cpp, to resolve hotkeys inside the update GUI loop
        void manualFireHotkey(std::vector<std::string> hotkey) { m_pendingHotkeys.push_back(hotkey); }

        void bindHotkey(std::vector<std::string> hotkey, std::function<void()> callback);

    private:
        void resolveBinding(LE3Input input, std::vector<std::string> hotkey);

        LE3Input m_prevInput;
        std::map<std::vector<std::string>, std::function<void()>> m_hotkeys;
        std::vector<std::vector<std::string>> m_pendingHotkeys;
    };
}