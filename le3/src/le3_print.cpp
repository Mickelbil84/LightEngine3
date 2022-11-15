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

void printMatrix(glm::mat4 m)
{
    std::cout << m[0][0] << "," << m[1][0] << "," << m[2][0] << "," << m[3][0] << std::endl;
    std::cout << m[0][1] << "," << m[1][1] << "," << m[2][1] << "," << m[3][1] << std::endl;
    std::cout << m[0][2] << "," << m[1][2] << "," << m[2][2] << "," << m[3][2] << std::endl;
    std::cout << m[0][3] << "," << m[1][3] << "," << m[2][3] << "," << m[3][3] << std::endl;
}