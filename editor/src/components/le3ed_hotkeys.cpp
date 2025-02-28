#include "components/le3ed_hotkeys.h"
#include "le3ed_editor_systems.h"
using namespace le3;

void LE3EditorHotkeys::handleInput(LE3Input input) {
    if (input.bRightMouseDown) return; // Right mouse blocks hotkeys
    for (auto& hotkey : m_hotkeys) {
        resolveBinding(input, hotkey.first);
    }
    m_prevInput = input;
}

void LE3EditorHotkeys::bindHotkey(std::vector<std::string> hotkey, std::function<void()> callback) {
    m_hotkeys[hotkey] = callback;
}

void LE3EditorHotkeys::resolveBinding(LE3Input input, std::vector<std::string> hotkey) {
    // Check if any of the keys was off previous frame
    bool flag = false;
    for (std::string key : hotkey) {
        if (!m_prevInput.keys[key]) {
            flag = true;
            break;
        }
    }
    if (!flag) return;

    // Check that all keys are pressed
    for (std::string key : hotkey) {
        if (!input.keys[key]) return;
    }

    // If we get here, we at the first frame for which before the hotkey was not pressed, and now it is
    m_pendingHotkeys.push_back(hotkey);
}

void LE3EditorHotkeys::solveHotkeys() {
    for (auto hotkey : m_pendingHotkeys) {
        m_hotkeys[hotkey]();
    }
    LE3EditorSystems::instance().updatePopups();
    m_pendingHotkeys.clear();
}