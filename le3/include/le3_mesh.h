#pragma once

#include <map>
#include <string>
#include <vector>
#include <memory>

#include <gl/glew.h>
#include <glm/glm.hpp>

#include "le3_vertex.h"
#include "le3_physics.h"

struct LE3Bone
{
public:
    glm::mat4 transform;
    glm::mat4 offset;
    std::string name;
    GLuint id;

    std::shared_ptr<LE3Bone> parent = nullptr;

    glm::mat4 GetTransform();
};
struct LE3Skeleton
{
public:
    void AddBone(std::string boneName);
    std::shared_ptr<LE3Bone> GetBone(std::string boneName);

    glm::mat4 m_globalInverseTransform;
    std::vector<std::shared_ptr<LE3Bone>> m_bones;
    std::map<std::string, std::shared_ptr<LE3Bone>> m_boneMapping;
};

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
    LE3Skeleton m_skeleton;
};
