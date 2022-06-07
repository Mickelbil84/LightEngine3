#pragma once

#include <gl/glew.h>
#include <cstddef>

// Vertex struct with 3 floats for position
struct LE3Vertex3p
{
    GLfloat position[3]; // location = 0
};

// Vertex struct with 3 floats for position and 3 floats for color
struct LE3Vertex3p3c
{
    GLfloat position[3]; // location = 0
    GLfloat color[3]; // location = 4
};



// Register the type of `LE3Vertex3p` as the current vertex type, argument `v` is example for type.
void RegisterVertexAttribPointer(LE3Vertex3p* v);
// Register the type of `LE3Vertex3p3c` as the current vertex type, argument `v` is example for type.
void RegisterVertexAttribPointer(LE3Vertex3p3c* v);