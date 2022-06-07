#pragma once

#include <vector>
#include <gl/glew.h>

#include "le3_vertex.h"

template<typename LE3VertexType>
class LE3Mesh
{
public:
    // Loads the mesh data to the GPU.
    void LoadMeshData(GLsizeiptr size, LE3VertexType* data, GLsizei count);
    // Loads the mesh data to the GPU. Assumes the data is given as an `std::vector`.
    void LoadMeshData(std::vector<LE3VertexType> data);
    
    // Draws the mesh to the screen (we assume a shader is already bound)
    void Draw(GLenum mode = GL_TRIANGLES);

protected:
    GLuint m_vao, m_vbo;
    GLsizei m_count;
};
