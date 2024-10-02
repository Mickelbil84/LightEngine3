#pragma once 

#include <string>

namespace le3 {
    struct LE3EditorToolbarButton {
        LE3EditorToolbarButton(std::string name, std::string iconName) : name(name), iconName(iconName) {}
        LE3EditorToolbarButton() : separator(true) {}

        std::string name;
        std::string iconName;

        bool separator = false; // If true, ignore all other fields
    };
}