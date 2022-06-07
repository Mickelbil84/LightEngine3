#pragma once
#include <iostream>

#define TITLE_SPACE ' '
#define TITLE_CHAR '-'
#define TITLE_PAD 2

// Prints a title with a bounding box. Used for debug prints.
// Example:
//      PrintTitle("test") 
// Output:
//      ----------
//      -  test  -
//      ----------
void PrintTitle(std::string title);