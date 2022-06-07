#include "le3_print.h"

void PrintTitle(std::string title)
{
    size_t bannerLength = title.length() + 2 * TITLE_PAD + 2;

    for (size_t i = 0; i < bannerLength; ++i)
        std::cout << TITLE_CHAR;
    std::cout << std::endl << TITLE_CHAR;
    for (size_t i = 0; i < TITLE_PAD; ++i)
        std::cout << TITLE_SPACE;
    std::cout << title;
    for (size_t i = 0; i < TITLE_PAD; ++i)
        std::cout << TITLE_SPACE;
    std::cout << TITLE_CHAR << std::endl;
    for (size_t i = 0; i < bannerLength; ++i)
        std::cout << TITLE_CHAR;
    std::cout << std::endl;
}