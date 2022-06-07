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
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(LE3Vertex3p3c), 
        reinterpret_cast<void*>(offsetof(LE3Vertex3p3c, color)));
}

void RegisterVertexAttribPointer(LE3Vertex3p2t3n* v)
{
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(LE3Vertex3p2t3n), 
        reinterpret_cast<void*>(offsetof(LE3Vertex3p2t3n, position)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(LE3Vertex3p2t3n), 
        reinterpret_cast<void*>(offsetof(LE3Vertex3p2t3n, uv)));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(LE3Vertex3p2t3n), 
        reinterpret_cast<void*>(offsetof(LE3Vertex3p2t3n, normal)));
}

void RegisterVertexAttribPointer(LE3Vertex3p2t3n3c* v)
{
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(LE3Vertex3p2t3n3c), 
        reinterpret_cast<void*>(offsetof(LE3Vertex3p2t3n3c, position)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(LE3Vertex3p2t3n3c), 
        reinterpret_cast<void*>(offsetof(LE3Vertex3p2t3n3c, uv)));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(LE3Vertex3p2t3n3c), 
        reinterpret_cast<void*>(offsetof(LE3Vertex3p2t3n3c, normal)));
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(LE3Vertex3p2t3n3c), 
        reinterpret_cast<void*>(offsetof(LE3Vertex3p2t3n3c, color)));    
}