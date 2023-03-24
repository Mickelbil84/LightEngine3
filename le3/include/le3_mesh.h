#pragma once

#include <vector>
#include <gl/glew.h>
#include <glm/glm.hpp>

#include "le3_vertex.h"
#include "le3_physics.h"

template<typename LE3VertexType>
class LE3Mesh
{
public:
    // Loads the mesh data to the GPU.
    void LoadMeshData(GLsizeiptr size, LE3VertexType* data, GLsizei count);
    // Loads the mesh data and indices to the GPU.
    void LoadMeshDataIndexed(GLsizeiptr size, LE3VertexType* data, 
        GLsizeiptr indexBufferSize, GLuint* indexBufferData,
        GLsizei count);

    // Loads the mesh data to the GPU. Assumes the data is given as an `std::vector`.
    void LoadMeshData(std::vector<LE3VertexType> data);
    // Loads the mesh data and indices to the GPU. Assumes the data is given as an `std::vector`.
    void LoadMeshDataIndexed(std::vector<LE3VertexType> data, std::vector<GLuint> indices);
    
    // Draws the mesh to the screen (we assume a shader is already bound)
    void Draw(GLenum mode = GL_TRIANGLES);

    LE3BoxCollision GetBoxCollision() const;

protected:
public:
    void ComputeAABB(GLsizeiptr size, LE3VertexType* data);

    GLuint m_vao, m_vbo, m_ibo;
    GLsizei m_count;
    bool m_bIndexed;
    LE3BoxCollision m_boxCollision;

    // In case of skeletal mesh
    std::vector<glm::mat4> m_bones;
};
