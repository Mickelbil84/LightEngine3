#include "le3_mesh.h"

template<typename LE3VertexType>
void LE3Mesh<LE3VertexType>::LoadMeshData(GLsizeiptr size, LE3VertexType* data, GLsizei count)
{
    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);

    glGenBuffers(1, &m_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, size, reinterpret_cast<void*>(data), GL_STATIC_DRAW);
    RegisterVertexAttribPointer(data);
    glBindBuffer(GL_ARRAY_BUFFER, 0); // Unbind buffer

    m_count = count;
}

template<typename LE3VertexType>
void LE3Mesh<LE3VertexType>::LoadMeshData(std::vector<LE3VertexType> data) 
{
    this->LoadMeshData(
        static_cast<GLsizeiptr>(data.size() * sizeof(LE3VertexType)), 
        &data[0], 
        static_cast<GLsizei>(data.size()));
}

template<typename LE3VertexType>
void LE3Mesh<LE3VertexType>::Draw(GLenum mode)
{
    glBindVertexArray(m_vao);
    glDrawArrays(mode, 0, m_count);
}

template class LE3Mesh<LE3Vertex3p>;
template class LE3Mesh<LE3Vertex3p3c>;