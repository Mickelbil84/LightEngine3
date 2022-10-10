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

    // Define the 3 tex coord multipliers
    glm::vec2 m1(width, depth);
    glm::vec2 m2(depth, height);
    glm::vec2 m3(width, height);

    // Top Face
    buffer.push_back(VertexFromGLM(v1, t1 * m1, n3));
    buffer.push_back(VertexFromGLM(v2, t2 * m1, n3));
    buffer.push_back(VertexFromGLM(v3, t3 * m1, n3));
    buffer.push_back(VertexFromGLM(v1, t1 * m1, n3));
    buffer.push_back(VertexFromGLM(v3, t3 * m1, n3));
    buffer.push_back(VertexFromGLM(v4, t4 * m1, n3));

    // Bottom Face
    buffer.push_back(VertexFromGLM(v5, t1 * m1, n4));
    buffer.push_back(VertexFromGLM(v6, t2 * m1, n4));
    buffer.push_back(VertexFromGLM(v7, t3 * m1, n4));
    buffer.push_back(VertexFromGLM(v5, t1 * m1, n4));
    buffer.push_back(VertexFromGLM(v7, t3 * m1, n4));
    buffer.push_back(VertexFromGLM(v8, t4 * m1, n4));

    // Right Face
    buffer.push_back(VertexFromGLM(v8, t1 * m2, n1));
    buffer.push_back(VertexFromGLM(v4, t2 * m2, n1));
    buffer.push_back(VertexFromGLM(v3, t3 * m2, n1));
    buffer.push_back(VertexFromGLM(v8, t1 * m2, n1));
    buffer.push_back(VertexFromGLM(v3, t3 * m2, n1));
    buffer.push_back(VertexFromGLM(v7, t4 * m2, n1));

    // Left Face
    buffer.push_back(VertexFromGLM(v5, t1 * m2, n2));
    buffer.push_back(VertexFromGLM(v1, t2 * m2, n2));
    buffer.push_back(VertexFromGLM(v2, t3 * m2, n2));
    buffer.push_back(VertexFromGLM(v5, t1 * m2, n2));
    buffer.push_back(VertexFromGLM(v2, t3 * m2, n2));
    buffer.push_back(VertexFromGLM(v6, t4 * m2, n2));

    // Front Face
    buffer.push_back(VertexFromGLM(v5, t1 * m3, n5));
    buffer.push_back(VertexFromGLM(v1, t2 * m3, n5));
    buffer.push_back(VertexFromGLM(v4, t3 * m3, n5));
    buffer.push_back(VertexFromGLM(v5, t1 * m3, n5));
    buffer.push_back(VertexFromGLM(v4, t3 * m3, n5));
    buffer.push_back(VertexFromGLM(v8, t4 * m3, n5));

    // Back Face
    buffer.push_back(VertexFromGLM(v6, t1 * m3, n6));
    buffer.push_back(VertexFromGLM(v2, t2 * m3, n6));
    buffer.push_back(VertexFromGLM(v3, t3 * m3, n6));
    buffer.push_back(VertexFromGLM(v6, t1 * m3, n6));
    buffer.push_back(VertexFromGLM(v3, t3 * m3, n6));
    buffer.push_back(VertexFromGLM(v7, t4 * m3, n6));
}

void AddCylinder(std::vector<LE3Vertex>& buffer,
    GLfloat x0, GLfloat y0, GLfloat z0,
    GLfloat radius, GLfloat height, GLushort resolution)
{
    std::vector<LE3Vertex> bottomFace, topFace;
    for (GLushort i = 0; i < resolution; i++)
    {
        GLfloat theta = (GLfloat)i / (GLfloat) resolution * 2.f * 3.14159265f;
        GLfloat x = x0 + radius * cos(theta);
        GLfloat z = z0 + radius * sin(theta);
        
        glm::vec3 normal(x, 0.f, z);
        glm::vec3 posBottom(x, y0, z);
        glm::vec3 posTop(x, y0 + height, z);

        bottomFace.push_back(VertexFromGLM(posBottom, glm::vec2(), normal));
        topFace.push_back(VertexFromGLM(posTop, glm::vec2(), normal));
    }

    for (GLushort i = 0; i < resolution; i++)
    {
        buffer.push_back(bottomFace[i]);
        buffer.push_back(topFace[(i+1) % resolution]);
        buffer.push_back(topFace[i]);
        buffer.push_back(bottomFace[i]);
        buffer.push_back(topFace[(i+1) % resolution]);
        buffer.push_back(bottomFace[(i+1) % resolution]);
    }
}

void AddCone(std::vector<LE3Vertex>& buffer,
    GLfloat x0, GLfloat y0, GLfloat z0,
    GLfloat radius, GLfloat height, GLushort resolution)
{
    std::vector<LE3Vertex> bottomFace;
    for (GLushort i = 0; i < resolution; i++)
    {
        GLfloat theta = (GLfloat)i / (GLfloat) resolution * 2.f * 3.14159265f;
        GLfloat x = x0 + radius * cos(theta);
        GLfloat z = z0 + radius * sin(theta);
        
        glm::vec3 normal(x, 0.f, z);
        glm::vec3 posBottom(x, y0, z);

        bottomFace.push_back(VertexFromGLM(posBottom, glm::vec2(), normal));
    }

    LE3Vertex topVertex = VertexFromGLM(glm::vec3(x0, y0+height, z0), glm::vec2(), glm::vec3(0.f, 1.f, 0.f));

    for (GLushort i = 0; i < resolution; i++)
    {
        buffer.push_back(bottomFace[i]);
        buffer.push_back(topVertex);
        buffer.push_back(bottomFace[(i+1) % resolution]);
    }
}