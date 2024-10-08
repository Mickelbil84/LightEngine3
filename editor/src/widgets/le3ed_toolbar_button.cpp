#include "widgets/le3ed_toolbar_button.h"
#include "le3ed_editor_systems.h"
using namespace le3;

void LE3EditorToolbarButton::setupHotkey(std::vector<std::string> hotkey) {
    this->hotkey = hotkey;
    LE3EditorSystems::instance().getHotkeysComponent()->bindHotkey(hotkey, onClick);
}