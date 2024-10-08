#pragma once 

#include <string>
#include <functional>

namespace le3 {
    struct LE3EditorToolbarButton {
        LE3EditorToolbarButton(std::string name, std::string iconName) : name(name), iconName(iconName) {}
        LE3EditorToolbarButton(std::string name, std::string iconName, std::function<void()> onClick) : name(name), iconName(iconName), onClick(onClick) {}
        LE3EditorToolbarButton() : separator(true) {}

        void setupHotkey(std::vector<std::string> hotkey);

        std::string name;
        std::string iconName;
        std::vector<std::string> hotkey;
        std::function<void()> onClick = 0;
        std::function<bool()> isToggled = 0;

        bool separator = false; // If true, ignore all other fields
    };
}