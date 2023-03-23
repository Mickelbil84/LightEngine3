#pragma once
#include "sprites/le3_engine_pointlight.xpm"

#include <sstream>
#include <fmt/core.h>

using fmt::print;

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