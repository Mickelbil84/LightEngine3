#pragma once

#include <map>
#include <string>
#include <vector>
#include <algorithm>

namespace le3 {
    // Key names are of the type "KEY_<XXX>", e.g. KEY_W, KEY_UP, KEY_ESCAPE, etc. 
    struct LE3Input {
        std::map<std::string, bool> keys;
        std::vector<std::string> keyDownEvt;
        std::vector<std::string> keyUpEvt;

        bool bLeftMouseDown = false, bRightMouseDown = false;
        int32_t xrel, yrel;
        int32_t mouseX, mouseY;

        bool isKeyDownEvent(std::string key) { return std::find(keyDownEvt.begin(), keyDownEvt.end(), key) != keyDownEvt.end(); }
        bool isKeyUpEvent(std::string key) { return std::find(keyUpEvt.begin(), keyUpEvt.end(), key) != keyUpEvt.end(); }
    };
}