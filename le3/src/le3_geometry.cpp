#include "le3_geometry.h"
using namespace le3;

#ifdef __linux__
#include <GL/glew.h>
#else
#include <gl/glew.h>
#endif

#include "le3_engine_systems.h"


template<typename LE3VertexType>
LE3Mesh<LE3VertexType>::LE3Mesh(std::vector<LE3VertexType>& data) {
    std::vector<uint32_t> indices;
    loadMeshData(data, indices);
}

template<typename LE3VertexType>
LE3Mesh<LE3VertexType>::LE3Mesh(std::vector<LE3VertexType>& data, std::vector<uint32_t>& indices, bool keepData) {
    loadMeshData(data, indices);
    if (keepData) {
        m_keptData = data;
        m_keptIndices = indices;
    }
}

template<typename LE3VertexType>
LE3Mesh<LE3VertexType>::~LE3Mesh() {
    if (LE3EngineSystems::instance().isHeadless()) return; // Allow loading meshes also in headless mode
    if (m_ibo >= 0) glDeleteBuffers(1, &m_ibo);
    if (m_vbo >= 0) glDeleteBuffers(1, &m_vbo);
    if (m_vao >= 0) glDeleteVertexArrays(1, &m_vao);
}

template<typename LE3VertexType>
void LE3Mesh<LE3VertexType>::loadMeshData(std::vector<LE3VertexType>& data, std::vector<uint32_t>& indices) {
    if (LE3EngineSystems::instance().isHeadless()) return; // Allow loading meshes also in headless mode
    m_bIndexed = indices.size() != 0;

    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);

    glGenBuffers(1, &m_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(LE3VertexType), &data[0], GL_STATIC_DRAW);
    registerVertexAttribPointer(&data[0]);

    if (m_bIndexed) {
        glGenBuffers(1, &m_ibo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(uint32_t), &indices[0], GL_STATIC_DRAW);
    }

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    if (m_bIndexed) glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    m_count = m_bIndexed ? indices.size() : data.size();
}

template<typename LE3VertexType>
void LE3Mesh<LE3VertexType>::drawTriangles() {
    draw(GL_TRIANGLES);
}

template<typename LE3VertexType>
void LE3Mesh<LE3VertexType>::drawLines() {
    draw(GL_LINES);
}

template<typename LE3VertexType>
void LE3Mesh<LE3VertexType>::drawPoints(float pointSize) {
    glPointSize(pointSize);
    draw(GL_POINTS);
}

template<typename LE3VertexType>
void LE3Mesh<LE3VertexType>::draw(int mode) {
    glBindVertexArray(m_vao);
    if (m_bIndexed) glDrawElements(mode, m_count, GL_UNSIGNED_INT, NULL);
    else glDrawArrays(mode, 0, m_count);
}


namespace le3 {
    void registerVertexAttribPointer(LE3Vertex3p* v)
    {
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(LE3Vertex3p), 
            reinterpret_cast<void*>(offsetof(LE3Vertex3p, position)));
    }

    void registerVertexAttribPointer(LE3Vertex3p3c* v)
    {
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(LE3Vertex3p3c), 
            reinterpret_cast<void*>(offsetof(LE3Vertex3p3c, position)));
        glEnableVertexAttribArray(3);
        glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(LE3Vertex3p3c), 
            reinterpret_cast<void*>(offsetof(LE3Vertex3p3c, color)));
    }

    void registerVertexAttribPointer(LE3Vertex3p2t3n* v)
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

    void registerVertexAttribPointer(LE3Vertex3p2t3n3c* v)
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

    void registerVertexAttribPointer(LE3Vertex3p2t3n3tn3b* v)
    {
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(LE3Vertex3p2t3n3tn3b), 
            reinterpret_cast<void*>(offsetof(LE3Vertex3p2t3n3tn3b, position)));
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(LE3Vertex3p2t3n3tn3b), 
            reinterpret_cast<void*>(offsetof(LE3Vertex3p2t3n3tn3b, uv)));
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(LE3Vertex3p2t3n3tn3b), 
            reinterpret_cast<void*>(offsetof(LE3Vertex3p2t3n3tn3b, normal)));
        glEnableVertexAttribArray(4);
        glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(LE3Vertex3p2t3n3tn3b), 
            reinterpret_cast<void*>(offsetof(LE3Vertex3p2t3n3tn3b, tangent)));
        glEnableVertexAttribArray(5);
        glVertexAttribPointer(5, 3, GL_FLOAT, GL_FALSE, sizeof(LE3Vertex3p2t3n3tn3b), 
            reinterpret_cast<void*>(offsetof(LE3Vertex3p2t3n3tn3b, bitangent)));
    }

    void registerVertexAttribPointer(LE3Vertex3p2t3n3tn3b4b4w* v)
    {
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(LE3Vertex3p2t3n3tn3b4b4w), 
            reinterpret_cast<void*>(offsetof(LE3Vertex3p2t3n3tn3b4b4w, position)));
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(LE3Vertex3p2t3n3tn3b4b4w), 
            reinterpret_cast<void*>(offsetof(LE3Vertex3p2t3n3tn3b4b4w, uv)));
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(LE3Vertex3p2t3n3tn3b4b4w), 
            reinterpret_cast<void*>(offsetof(LE3Vertex3p2t3n3tn3b4b4w, normal)));
        glEnableVertexAttribArray(4);
        glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(LE3Vertex3p2t3n3tn3b4b4w), 
            reinterpret_cast<void*>(offsetof(LE3Vertex3p2t3n3tn3b4b4w, tangent)));
        glEnableVertexAttribArray(5);
        glVertexAttribPointer(5, 3, GL_FLOAT, GL_FALSE, sizeof(LE3Vertex3p2t3n3tn3b4b4w), 
            reinterpret_cast<void*>(offsetof(LE3Vertex3p2t3n3tn3b4b4w, bitangent)));


        glEnableVertexAttribArray(6);
        glVertexAttribIPointer(6, 4, GL_INT, sizeof(LE3Vertex3p2t3n3tn3b4b4w), 
            reinterpret_cast<void*>(offsetof(LE3Vertex3p2t3n3tn3b4b4w, bones)));
        glEnableVertexAttribArray(7);
        glVertexAttribPointer(7, 4, GL_FLOAT, GL_FALSE, sizeof(LE3Vertex3p2t3n3tn3b4b4w), 
            reinterpret_cast<void*>(offsetof(LE3Vertex3p2t3n3tn3b4b4w, weights)));
        glEnableVertexAttribArray(8);
        glVertexAttribIPointer(8, 4, GL_INT, sizeof(LE3Vertex3p2t3n3tn3b4b4w), 
            reinterpret_cast<void*>(offsetof(LE3Vertex3p2t3n3tn3b4b4w, bones2)));
        glEnableVertexAttribArray(9);
        glVertexAttribPointer(9, 4, GL_FLOAT, GL_FALSE, sizeof(LE3Vertex3p2t3n3tn3b4b4w), 
            reinterpret_cast<void*>(offsetof(LE3Vertex3p2t3n3tn3b4b4w, weights2)));
    }


    LE3Vertex vertexFromGLM(glm::vec3 position, glm::vec2 uv, glm::vec3 normal, glm::vec3 tangent, glm::vec3 bitangent)
    {
        LE3Vertex v;
        v.position[0] = position.x;
        v.position[1] = position.y;
        v.position[2] = position.z;
        v.uv[0] = uv.x;
        v.uv[1] = uv.y;
        v.normal[0] = normal.x;
        v.normal[1] = normal.y;
        v.normal[2] = normal.z;
        v.tangent[0] = tangent.x;
        v.tangent[1] = tangent.y;
        v.tangent[2] = tangent.z;
        v.bitangent[0] = bitangent.x;
        v.bitangent[1] = bitangent.y;
        v.bitangent[2] = bitangent.z;
        return v;
    }

    LE3Vertex3p vertexFromGLM(glm::vec3 position)
    {
        LE3Vertex3p v;
        v.position[0] = position.x;
        v.position[1] = position.y;
        v.position[2] = position.z;
        return v;
    }

    LE3VertexSkeletal vertexSkeletalFromGLM(glm::vec3 position, glm::vec2 uv, glm::vec3 normal, 
        glm::vec3 tangent, glm::vec3 bitangent, glm::ivec4 bones, glm::vec4 weights)
    {
        LE3VertexSkeletal v;
        v.position[0] = position.x; v.position[1] = position.y; v.position[2] = position.z;
        v.uv[0] = uv.x; v.uv[1] = uv.y;
        v.normal[0] = normal.x; v.normal[1] = normal.y; v.normal[2] = normal.z;
        v.tangent[0] = tangent.x; v.tangent[1] = tangent.y; v.tangent[2] = tangent.z;
        v.bitangent[0] = bitangent.x; v.bitangent[1] = bitangent.y; v.bitangent[2] = bitangent.z;
        v.bones[0] = bones.x; v.bones[1] = bones.y; v.bones[2] = bones.z; v.bones[3] = bones.w;
        v.weights[0] = weights.x; v.weights[1] = weights.y; v.weights[2] = weights.z; v.weights[3] = weights.w;
        return v;
    }

    template class LE3Mesh<LE3Vertex3p>;
    template class LE3Mesh<LE3Vertex3p3c>;
    template class LE3Mesh<LE3Vertex3p2t3n>;
    template class LE3Mesh<LE3Vertex3p2t3n3c>;
    template class LE3Mesh<LE3Vertex3p2t3n3tn3b>;
    template class LE3Mesh<LE3Vertex3p2t3n3tn3b4b4w>;
}