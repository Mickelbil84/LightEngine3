#pragma once

#include <vector>
#include <cstddef>

#include <glm/glm.hpp>

#include "le3_skeleton.h"
#include "le3_animation.h"

namespace le3 {
    constexpr int MAX_BONES_PER_VERTEX = 8;

    // Vertex struct with 3 floats for position
    struct LE3Vertex3p {
        float position[3]; // location = 0
    };

    // Vertex struct with 3 floats for position and 3 floats for color
    struct LE3Vertex3p3c {
        float position[3]; // location = 0
        float color[3]; // location = 3
    };

    // Vertex struct with 3 floats for position, 2 for texture and 3 for normal
    struct LE3Vertex3p2t3n {
        float position[3]; // location = 0
        float uv[2]; // location = 1
        float normal[3]; // location = 2
    };

    // Vertex struct with 3 floats for position, 2 for texture, 3 for normal and 3 for color
    struct LE3Vertex3p2t3n3c {
        float position[3]; // location = 0
        float uv[2]; // location = 1
        float normal[3]; // location = 2
        float color[3]; // location = 3
    };

    struct LE3Vertex3p2t3n3tn3b {
        float position[3]; // location = 0
        float uv[2]; // location = 1
        float normal[3]; // location = 2
        float tangent[3]; // location = 4
        float bitangent[3]; // location = 5
    };

    // Vertex with pos, texsture, normal, tangent-bitangent & bone ids and weights
    struct LE3Vertex3p2t3n3tn3b4b4w {
        float position[3]; // location = 0
        float uv[2]; // location = 1
        float normal[3]; // location = 2
        float tangent[3]; // location = 4
        float bitangent[3]; // location = 5
        int32_t bones[4]; // location = 6
        float weights[4]; // location = 7
        int32_t bones2[4]; // location = 8
        float weights2[4]; // location = 9
    };

    template<typename LE3VertexType>
    class LE3Mesh {
    public:
        LE3Mesh(std::vector<LE3VertexType>& data);
        LE3Mesh(std::vector<LE3VertexType>& data, std::vector<uint32_t>& indices, bool keepData = false);
        ~LE3Mesh();

        void draw() { drawTriangles(); }
        void drawTriangles();
        void drawLines();
        void drawPoints(float pointSize);

        LE3Skeleton& getSkeleton() { return m_skeleton; }
        void setSkeleton(LE3Skeleton skeleton) { m_skeleton = skeleton; }
        std::map<std::string, LE3AnimationTrack>& getAnimationTracks() { return m_animationTracks; }
        void addAnimationTrack(std::string name, LE3AnimationTrack track) { m_animationTracks[name] = track; }
    
        std::vector<LE3VertexType>& getKeptData() { return m_keptData; }   
        std::vector<uint32_t>& getKeptIndices() { return m_keptIndices; }

    protected:
        uint32_t m_vao = -1, m_vbo = -1, m_ibo = -1, m_count;
        bool m_bIndexed;

        void loadMeshData(std::vector<LE3VertexType>& data, std::vector<uint32_t>& indices);
        void draw(int mode);

        // For keeping data
        std::vector<LE3VertexType> m_keptData;
        std::vector<uint32_t> m_keptIndices;

        // In case of a skeletal mesh
        LE3Skeleton m_skeleton;
        std::map<std::string, LE3AnimationTrack> m_animationTracks;

    };
    template<typename LE3VertexType>
    using LE3MeshPtr = std::shared_ptr<LE3Mesh<LE3VertexType>>;
    
    // The default vertex type is the one with the most data (and skeletal if relevant)
    using LE3Vertex = LE3Vertex3p2t3n3tn3b;
    using LE3VertexSkeletal = LE3Vertex3p2t3n3tn3b4b4w;

    using LE3ScreenRect = LE3Mesh<LE3Vertex3p>;
    using LE3StaticMesh = LE3Mesh<LE3Vertex>;
    using LE3SkeletalMesh = LE3Mesh<LE3VertexSkeletal>;

    using LE3ScreenRectPtr = std::shared_ptr<LE3ScreenRect>;
    using LE3StaticMeshPtr = std::shared_ptr<LE3StaticMesh>;
    using LE3SkeletalMeshPtr = std::shared_ptr<LE3SkeletalMesh>;

    // Create a default vertex type using glm
    LE3Vertex vertexFromGLM(glm::vec3 position, glm::vec2 uv, glm::vec3 normal,
        glm::vec3 tangent = glm::vec3(1.f, 0.f, 0.f), glm::vec3 bitangent = glm::vec3(0.f, 1.f, 0.f));
    LE3Vertex3p vertexFromGLM(glm::vec3 position);
    LE3VertexSkeletal vertexSkeletalFromGLM(glm::vec3 position, glm::vec2 uv, glm::vec3 normal,
        glm::vec3 tangent = glm::vec3(1.f, 0.f, 0.f), glm::vec3 bitangent = glm::vec3(0.f, 1.f, 0.f),
        glm::ivec4 bones = glm::ivec4(-1), glm::vec4 weights = glm::vec4(0.f));
    
    // Register the type of `LE3Vertex3p` as the current vertex type, argument `v` is example for type.
    void registerVertexAttribPointer(LE3Vertex3p* v);
    // Register the type of `LE3Vertex3p3c` as the current vertex type, argument `v` is example for type.
    void registerVertexAttribPointer(LE3Vertex3p3c* v);
    // Register the type of `LE3Vertex3p2t3n` as the current vertex type, argument `v` is example for type.
    void registerVertexAttribPointer(LE3Vertex3p2t3n* v);
    // Register the type of `LE3Vertex3p2t3n3c` as the current vertex type, argument `v` is example for type.
    void registerVertexAttribPointer(LE3Vertex3p2t3n3c* v);
    // Register the type of `LE3Vertex3p2t3n3tn3b` as the current vertex type, argument `v` is example for type.
    void registerVertexAttribPointer(LE3Vertex3p2t3n3tn3b* v);
    // Register the type of `LE3Vertex3p2t3n3tn3b4b4w` as the current vertex type, argument `v` is example for type.
    void registerVertexAttribPointer(LE3Vertex3p2t3n3tn3b4b4w* v);
}