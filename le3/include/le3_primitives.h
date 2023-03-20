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
void AddDebugBox(std::vector<LE3Vertex3p>& buffer);

// Appends a cylinder to a given vector vertex buffer
void AddCylinder(std::vector<LE3Vertex>& buffer,
    GLfloat x0, GLfloat y0, GLfloat z0,
    GLfloat radius, GLfloat height, GLushort resolution, GLushort withCaps = 0);

// Appends a cone to a given vector vertex buffer
void AddCone(std::vector<LE3Vertex>& buffer,
    GLfloat x0, GLfloat y0, GLfloat z0,
    GLfloat radius, GLfloat height, GLushort resolution);

// Appends a sphere to a given vector vertex buffer
void AddSphere(std::vector<LE3Vertex>& buffer,
    GLfloat x0, GLfloat y0, GLfloat z0,
    GLfloat radius, GLushort resolution);

// Appends a torus to a given vector vertex buffer
void AddTorus(std::vector<LE3Vertex>& buffer,
    GLfloat x0, GLfloat y0, GLfloat z0,
    GLfloat majorRadius, GLfloat minorRadius, GLushort resolution);