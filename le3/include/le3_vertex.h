#pragma once

#include <gl/glew.h>
#include <cstddef>
#include <glm/glm.hpp>

#define MAX_BONES_PER_VERTEX 4

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

struct LE3Vertex3p2t3n3tn3b
{
    GLfloat position[3]; // location = 0
    GLfloat uv[2]; // location = 1
    GLfloat normal[3]; // location = 2
    GLfloat tangent[3]; // location = 4
    GLfloat bitangent[3]; // location = 5
};

// Vertex with pos, texsture, normal, tangent-bitangent & bone ids and weights
struct LE3Vertex3p2t3n3tn3b4b4w
{
    GLfloat position[3]; // location = 0
    GLfloat uv[2]; // location = 1
    GLfloat normal[3]; // location = 2
    GLfloat tangent[3]; // location = 4
    GLfloat bitangent[3]; // location = 5
    GLint bones[MAX_BONES_PER_VERTEX]; // location = 6
    GLfloat weights[MAX_BONES_PER_VERTEX]; // location = 7
};

// The default vertex type is the one with (position, uv, normal)
using LE3Vertex = LE3Vertex3p2t3n3tn3b; 
using LE3VertexSkeletal = LE3Vertex3p2t3n3tn3b4b4w;
// Create a default vertex using glm vectors
LE3Vertex VertexFromGLM(glm::vec3 position, glm::vec2 uv, glm::vec3 normal, 
    glm::vec3 tangent = glm::vec3(1.f, 0.f, 0.f), glm::vec3 bitangent = glm::vec3(1.f, 0.f, 0.f));
LE3Vertex3p VertexFromGLM(glm::vec3 position);
LE3VertexSkeletal VertexSkeletalFromGLM(glm::vec3 position, glm::vec2 uv, glm::vec3 normal, 
    glm::vec3 tangent = glm::vec3(1.f, 0.f, 0.f), glm::vec3 bitangent = glm::vec3(1.f, 0.f, 0.f),
    glm::ivec4 bones=glm::ivec4(-1), glm::vec4 weights=glm::vec4(0.f));


// Register the type of `LE3Vertex3p` as the current vertex type, argument `v` is example for type.
void RegisterVertexAttribPointer(LE3Vertex3p* v);
// Register the type of `LE3Vertex3p3c` as the current vertex type, argument `v` is example for type.
void RegisterVertexAttribPointer(LE3Vertex3p3c* v);
// Register the type of `LE3Vertex3p2t3n` as the current vertex type, argument `v` is example for type.
void RegisterVertexAttribPointer(LE3Vertex3p2t3n* v);
// Register the type of `LE3Vertex3p2t3n3c` as the current vertex type, argument `v` is example for type.
void RegisterVertexAttribPointer(LE3Vertex3p2t3n3c* v);
// Register the type of `LE3Vertex3p2t3n3tn3b` as the current vertex type, argument `v` is example for type.
void RegisterVertexAttribPointer(LE3Vertex3p2t3n3tn3b* v);
// Register the type of `LE3Vertex3p2t3n3tn3b4b4w` as the current vertex type, argument `v` is example for type.
void RegisterVertexAttribPointer(LE3Vertex3p2t3n3tn3b4b4w* v);