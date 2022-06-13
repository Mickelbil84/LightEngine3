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

    // Unbind buffers
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    m_count = count;
    m_bIndexed = false;
}

template<typename LE3VertexType>
void LE3Mesh<LE3VertexType>::LoadMeshDataIndexed(GLsizeiptr size, LE3VertexType* data, 
        GLsizeiptr indexBufferSize, GLuint* indexBufferData,
        GLsizei count)
{
    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);

    glGenBuffers(1, &m_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, size, reinterpret_cast<void*>(data), GL_STATIC_DRAW);
    RegisterVertexAttribPointer(data);

    glGenBuffers(1, &m_ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexBufferSize, reinterpret_cast<void*>(indexBufferData), GL_STATIC_DRAW);
    
    // Unbind buffers
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    m_count = count;
    m_bIndexed = true;
}

template<typename LE3VertexType>
void LE3Mesh<LE3VertexType>::LoadMeshData(std::vector<LE3VertexType> data) 
{
    this->LoadMeshData(
        static_cast<GLsizeiptr>(data.size() * sizeof(LE3VertexType)), 
        &data[0], 
        static_cast<GLsizei>(data.size())
    );
}

template<typename LE3VertexType>
void LE3Mesh<LE3VertexType>::LoadMeshDataIndexed(std::vector<LE3VertexType> data, std::vector<GLuint> indices)
{
    this->LoadMeshDataIndexed(
        static_cast<GLsizeiptr>(data.size() * sizeof(LE3VertexType)), 
        &data[0], 
        static_cast<GLsizeiptr>(indices.size() * sizeof(GLuint)), 
        &indices[0],
        static_cast<GLsizei>(indices.size())
    );
}

template<typename LE3VertexType>
void LE3Mesh<LE3VertexType>::Draw(GLenum mode)
{
    glBindVertexArray(m_vao);
    if (!m_bIndexed)
        glDrawArrays(mode, 0, m_count);
    else
        glDrawElements(mode, m_count, GL_UNSIGNED_INT, NULL);
}

template class LE3Mesh<LE3Vertex3p>;
template class LE3Mesh<LE3Vertex3p3c>;
template class LE3Mesh<LE3Vertex3p2t3n>;
template class LE3Mesh<LE3Vertex3p2t3n3c>;