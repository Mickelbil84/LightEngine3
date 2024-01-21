#include "le3_primitives.h"
using namespace le3;

LE3MeshPtr<LE3Vertex3p3c> le3::createHelloOpenGLTriangle() {
    std::vector<LE3Vertex3p3c> vertices(3);
    vertices[0].position[0] = .5f * -1.f; vertices[0].position[1] = .5f * -1.f; vertices[0].position[2] = .5f * 0.f;
    vertices[1].position[0] = .5f *  0.f; vertices[1].position[1] = .5f *  1.f; vertices[1].position[2] = .5f * 0.f;
    vertices[2].position[0] = .5f *  1.f; vertices[2].position[1] = .5f * -1.f; vertices[2].position[2] = .5f * 0.f;

    vertices[0].color[0] =  1.f; vertices[0].color[1] =  0.f; vertices[0].color[2] = 0.f;
    vertices[1].color[0] =  0.f; vertices[1].color[1] =  1.f; vertices[1].color[2] = 0.f;
    vertices[2].color[0] =  0.f; vertices[2].color[1] =  0.f; vertices[2].color[2] = 1.f;
    return std::make_shared<LE3Mesh<LE3Vertex3p3c>>(vertices);
}

LE3MeshPtr<LE3Vertex> le3::createBox(float x0, float y0, float z0, float width, float height, float depth) {
    float hw = .5f * width;
    float hh = .5f * height;
    float hd = .5f * depth;

    // Define the 8 vertices of the cube
    glm::vec3 v1(x0 - hw, y0 + hh, z0 + hd);
    glm::vec3 v2(x0 - hw, y0 + hh, z0 - hd);
    glm::vec3 v3(x0 + hw, y0 + hh, z0 - hd);
    glm::vec3 v4(x0 + hw, y0 + hh, z0 + hd);
    glm::vec3 v5(x0 - hw, y0 - hh, z0 + hd);
    glm::vec3 v6(x0 - hw, y0 - hh, z0 - hd);
    glm::vec3 v7(x0 + hw, y0 - hh, z0 - hd);
    glm::vec3 v8(x0 + hw, y0 - hh, z0 + hd);

    // Define the 6 normals of the faces
    glm::vec3 n1(1.f, 0.f, 0.f);
    glm::vec3 n2(-1.f, 0.f, 0.f);
    glm::vec3 n3(0.f, 1.f, 0.f);
    glm::vec3 n4(0.f, -1.f, 0.f);
    glm::vec3 n5(0.f, 0.f, 1.f);
    glm::vec3 n6(0.f, 0.f, -1.f);

    // Define the 4 texture coordinates
    glm::vec2 t1(0.f, 0.f);
    glm::vec2 t2(0.f, 1.f);
    glm::vec2 t3(1.f, 1.f);
    glm::vec2 t4(1.f, 0.f);

    // Define the 3 tex coord multipliers
    glm::vec2 m1(width, depth);
    glm::vec2 m2(depth, height);
    glm::vec2 m3(width, height);

    std::vector<LE3Vertex> buffer;

    // Top Face
    buffer.push_back(vertexFromGLM(v1, t1 * m1, n3));
    buffer.push_back(vertexFromGLM(v2, t2 * m1, n3));
    buffer.push_back(vertexFromGLM(v3, t3 * m1, n3));
    buffer.push_back(vertexFromGLM(v1, t1 * m1, n3));
    buffer.push_back(vertexFromGLM(v3, t3 * m1, n3));
    buffer.push_back(vertexFromGLM(v4, t4 * m1, n3));

    // Bottom Face
    buffer.push_back(vertexFromGLM(v5, t1 * m1, n4));
    buffer.push_back(vertexFromGLM(v6, t2 * m1, n4));
    buffer.push_back(vertexFromGLM(v7, t3 * m1, n4));
    buffer.push_back(vertexFromGLM(v5, t1 * m1, n4));
    buffer.push_back(vertexFromGLM(v7, t3 * m1, n4));
    buffer.push_back(vertexFromGLM(v8, t4 * m1, n4));

    // Right Face
    buffer.push_back(vertexFromGLM(v8, t1 * m2, n1));
    buffer.push_back(vertexFromGLM(v4, t2 * m2, n1));
    buffer.push_back(vertexFromGLM(v3, t3 * m2, n1));
    buffer.push_back(vertexFromGLM(v8, t1 * m2, n1));
    buffer.push_back(vertexFromGLM(v3, t3 * m2, n1));
    buffer.push_back(vertexFromGLM(v7, t4 * m2, n1));

    // Left Face
    buffer.push_back(vertexFromGLM(v5, t1 * m2, n2));
    buffer.push_back(vertexFromGLM(v1, t2 * m2, n2));
    buffer.push_back(vertexFromGLM(v2, t3 * m2, n2));
    buffer.push_back(vertexFromGLM(v5, t1 * m2, n2));
    buffer.push_back(vertexFromGLM(v2, t3 * m2, n2));
    buffer.push_back(vertexFromGLM(v6, t4 * m2, n2));

    // Front Face
    buffer.push_back(vertexFromGLM(v5, t1 * m3, n5));
    buffer.push_back(vertexFromGLM(v1, t2 * m3, n5));
    buffer.push_back(vertexFromGLM(v4, t3 * m3, n5));
    buffer.push_back(vertexFromGLM(v5, t1 * m3, n5));
    buffer.push_back(vertexFromGLM(v4, t3 * m3, n5));
    buffer.push_back(vertexFromGLM(v8, t4 * m3, n5));

    // Back Face
    buffer.push_back(vertexFromGLM(v6, t1 * m3, n6));
    buffer.push_back(vertexFromGLM(v2, t2 * m3, n6));
    buffer.push_back(vertexFromGLM(v3, t3 * m3, n6));
    buffer.push_back(vertexFromGLM(v6, t1 * m3, n6));
    buffer.push_back(vertexFromGLM(v3, t3 * m3, n6));
    buffer.push_back(vertexFromGLM(v7, t4 * m3, n6));

    return std::make_shared<LE3Mesh<LE3Vertex>>(buffer);
}