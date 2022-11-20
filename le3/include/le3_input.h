#pragma once

#include "SDL.h"

// Struct that stores the input state 
struct LE3Input
{
    const Uint8* keyboard;
	Sint32 xrel, yrel;
    bool bLeftMouseDown, bRightMouseDown;
};