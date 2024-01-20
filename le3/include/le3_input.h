#pragma once

#include <map>
#include <string>

namespace le3 {
    // Key names are of the type "KEY_<XXX>", e.g. KEY_W, KEY_UP, KEY_ESCAPE, etc. 
    struct LE3Input {
        std::map<std::string, bool> keys;

        bool bLeftMouseDown, bRightMouseDown;
        int32_t xrel, yrel;
    };
}