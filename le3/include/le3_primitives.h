#pragma once

#include <vector>
#include <glm/glm.hpp>
#include "le3_vertex.h"

// Appends an isosceles triangle to a given vector vertex buffer
void AddIsoscelesTriangle(std::vector<LE3Vertex3p>& buffer, 
    GLfloat x0, GLfloat y0, GLfloat z0,
    GLfloat width, GLfloat height);

// Adds the "Hello OpenGL" triangle, with different color for each vertex
void AddHelloOpenGLTriangle(std::vector<LE3Vertex3p3c>& buffer);

// Appends an axis-aligned box to a given vector vertex buffer
void AddBox(std::vector<LE3Vertex>& buffer,
    GLfloat x0, GLfloat y0, GLfloat z0,
    GLfloat width, GLfloat height, GLfloat depth);