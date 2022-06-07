#pragma once

#include <gl/glew.h>
#include <cstddef>
#include <glm/glm.hpp>

// Vertex struct with 3 floats for position
struct LE3Vertex3p
{
    GLfloat position[3]; // location = 0
};

// Vertex struct with 3 floats for position and 3 floats for color
struct LE3Vertex3p3c
{
    GLfloat position[3]; // location = 0
    GLfloat color[3]; // location = 3
};

// Vertex struct with 3 floats for position, 2 for texture and 3 for normal
struct LE3Vertex3p2t3n
{
    GLfloat position[3]; // location = 0
    GLfloat uv[2]; // location = 1
    GLfloat normal[3]; // location = 2
};

// Vertex struct with 3 floats for position, 2 for texture, 3 for normal and 3 for color
struct LE3Vertex3p2t3n3c
{
    GLfloat position[3]; // location = 0
    GLfloat uv[2]; // location = 1
    GLfloat normal[3]; // location = 2
    GLfloat color[3]; // location = 3
};

// The default vertex type is the one with (position, uv, normal)
using LE3Vertex = LE3Vertex3p2t3n; 
// Create a default vertex using glm vectors
LE3Vertex VertexFromGLM(glm::vec3 position, glm::vec2 uv, glm::vec3 normal);


// Register the type of `LE3Vertex3p` as the current vertex type, argument `v` is example for type.
void RegisterVertexAttribPointer(LE3Vertex3p* v);
// Register the type of `LE3Vertex3p3c` as the current vertex type, argument `v` is example for type.
void RegisterVertexAttribPointer(LE3Vertex3p3c* v);
// Register the type of `LE3Vertex3p2t3n` as the current vertex type, argument `v` is example for type.
void RegisterVertexAttribPointer(LE3Vertex3p2t3n* v);
// Register the type of `LE3Vertex3p2t3n3c` as the current vertex type, argument `v` is example for type.
void RegisterVertexAttribPointer(LE3Vertex3p2t3n3c* v);