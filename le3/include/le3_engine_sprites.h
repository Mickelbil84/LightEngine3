#pragma once
#include "sprites/sprite_engine_ambientlight.xpm"
#include "sprites/sprite_engine_directionallight.xpm"
#include "sprites/sprite_engine_pointlight.xpm"
#include "sprites/sprite_engine_spotlight.xpm"

#include <sstream>

inline std::string SpriteToString(const char* const* xpm)
{
    std::string res = "/* XPM */\n";

    // Read first line to infer how many lines there are
    std::string firstLine = xpm[0];
    std::istringstream ssFirstLine(firstLine);
    int width, height, char_table_size;
    ssFirstLine >> width;
    ssFirstLine >> height;
    ssFirstLine >> char_table_size;

    for (int i = 0; i < 1 + char_table_size + height; i++)
        res += std::string(xpm[i]) + '\n';

    return res;
}