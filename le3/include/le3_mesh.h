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
    // Loads the mesh data and indices to the GPU.
    void LoadMeshDataIndexed(GLsizeiptr size, LE3VertexType* data, 
        GLsizeiptr indexBufferSize, GLushort* indexBufferData,
        GLsizei count);

    // Loads the mesh data to the GPU. Assumes the data is given as an `std::vector`.
    void LoadMeshData(std::vector<LE3VertexType> data);
    // Loads the mesh data and indices to the GPU. Assumes the data is given as an `std::vector`.
    void LoadMeshDataIndexed(std::vector<LE3VertexType> data, std::vector<GLushort> indices);
    
    // Draws the mesh to the screen (we assume a shader is already bound)
    void Draw(GLenum mode = GL_TRIANGLES);
    // Draws the indexed mesh to the screen (we assume a shader is already bound)
    void DrawIndexed(GLenum mode = GL_TRIANGLES);

protected:
    GLuint m_vao, m_vbo, m_ibo;
    GLsizei m_count;
};
