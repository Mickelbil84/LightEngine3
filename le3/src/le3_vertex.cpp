#include "le3_vertex.h"

void RegisterVertexAttribPointer(LE3Vertex3p* v)
{
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(LE3Vertex3p), 
        reinterpret_cast<void*>(offsetof(LE3Vertex3p, position)));
}

void RegisterVertexAttribPointer(LE3Vertex3p3c* v)
{
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(LE3Vertex3p3c), 
        reinterpret_cast<void*>(offsetof(LE3Vertex3p3c, position)));
    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(LE3Vertex3p3c), 
        reinterpret_cast<void*>(offsetof(LE3Vertex3p3c, color)));
}