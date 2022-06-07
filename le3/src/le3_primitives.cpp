#include "le3_primitives.h"

void AddIsoscelesTriangle(std::vector<LE3Vertex3p>& buffer, 
    GLfloat x0, GLfloat y0, GLfloat z0,
    GLfloat width, GLfloat height)
{
    buffer.push_back({x0 - 0.5f * width, y0 - 0.5f * height, z0});
    buffer.push_back({x0, y0 + 0.5f * height, z0});
    buffer.push_back({x0 + 0.5f * width, y0 - 0.5f * height, z0});
}

void AddHelloOpenGLTriangle(std::vector<LE3Vertex3p3c>& buffer)
{
    buffer.push_back({
        -0.5f, -0.5f, 0.f,
        1.f, 0.f, 0.f
    });
    buffer.push_back({
        0.f, 0.5f, 0.f,
        0.f, 1.f, 0.f
    });
    buffer.push_back({
        0.5f, -0.5f, 0.f,
        0.f, 0.f, 1.f
    });
}
