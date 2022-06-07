#include "le3_primitives.h"

void AddIsoscelesTriangle(std::vector<LE3Vertex3p>& buffer, 
    GLfloat x0, GLfloat y0, GLfloat z0,
    GLfloat width, GLfloat height)
{
    buffer.push_back({x0 - 0.5f * width, y0 - 0.5f * height, z0});
    buffer.push_back({x0, y0 + 0.5f * height, z0});
    buffer.push_back({x0 + 0.5f * width, y0 - 0.5f * height, z0});
}

void AddHelloOpenGLTriangle(std::vector<LE3Vertex3p3c>& buffer)
{
    buffer.push_back({
        -0.5f, -0.5f, 0.f,
        1.f, 0.f, 0.f
    });
    buffer.push_back({
        0.f, 0.5f, 0.f,
        0.f, 1.f, 0.f
    });
    buffer.push_back({
        0.5f, -0.5f, 0.f,
        0.f, 0.f, 1.f
    });
}

void AddBox(std::vector<LE3Vertex>& buffer,
    GLfloat x0, GLfloat y0, GLfloat z0,
    GLfloat width, GLfloat height, GLfloat depth)
{
    GLfloat hw = 0.5f * width;
    GLfloat hh = 0.5f * height;
    GLfloat hd = 0.5f * depth;

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

    // Top Face
    buffer.push_back(VertexFromGLM(v1, t1, n3));
    buffer.push_back(VertexFromGLM(v2, t2, n3));
    buffer.push_back(VertexFromGLM(v3, t3, n3));
    buffer.push_back(VertexFromGLM(v1, t1, n3));
    buffer.push_back(VertexFromGLM(v3, t3, n3));
    buffer.push_back(VertexFromGLM(v4, t4, n3));

    // Bottom Face
    buffer.push_back(VertexFromGLM(v5, t1, n4));
    buffer.push_back(VertexFromGLM(v6, t2, n4));
    buffer.push_back(VertexFromGLM(v7, t3, n4));
    buffer.push_back(VertexFromGLM(v5, t1, n4));
    buffer.push_back(VertexFromGLM(v7, t3, n4));
    buffer.push_back(VertexFromGLM(v8, t4, n4));

    // Right Face
    buffer.push_back(VertexFromGLM(v8, t1, n1));
    buffer.push_back(VertexFromGLM(v4, t2, n1));
    buffer.push_back(VertexFromGLM(v3, t3, n1));
    buffer.push_back(VertexFromGLM(v8, t1, n1));
    buffer.push_back(VertexFromGLM(v3, t3, n1));
    buffer.push_back(VertexFromGLM(v7, t4, n1));

    // Left Face
    buffer.push_back(VertexFromGLM(v5, t1, n2));
    buffer.push_back(VertexFromGLM(v1, t2, n2));
    buffer.push_back(VertexFromGLM(v2, t3, n2));
    buffer.push_back(VertexFromGLM(v5, t1, n2));
    buffer.push_back(VertexFromGLM(v2, t3, n2));
    buffer.push_back(VertexFromGLM(v6, t4, n2));

    // Front Face
    buffer.push_back(VertexFromGLM(v5, t1, n5));
    buffer.push_back(VertexFromGLM(v1, t2, n5));
    buffer.push_back(VertexFromGLM(v4, t3, n5));
    buffer.push_back(VertexFromGLM(v5, t1, n5));
    buffer.push_back(VertexFromGLM(v4, t3, n5));
    buffer.push_back(VertexFromGLM(v8, t4, n5));

    // Back Face
    buffer.push_back(VertexFromGLM(v6, t1, n6));
    buffer.push_back(VertexFromGLM(v2, t2, n6));
    buffer.push_back(VertexFromGLM(v3, t3, n6));
    buffer.push_back(VertexFromGLM(v6, t1, n6));
    buffer.push_back(VertexFromGLM(v3, t3, n6));
    buffer.push_back(VertexFromGLM(v7, t4, n6));
}