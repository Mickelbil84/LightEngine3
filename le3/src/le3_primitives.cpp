#include "le3_primitives.h"

#include <iostream>

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

void AddDebugBox(std::vector<LE3Vertex3p>& buffer)
{
    // Define the 8 vertices of the cube
    std::vector<glm::vec3> vertices;
    vertices.push_back(glm::vec3(-.5f, .5f, .5f));
    vertices.push_back(glm::vec3(-.5f, .5f, -.5f));
    vertices.push_back(glm::vec3(.5f, .5f, -.5f));
    vertices.push_back(glm::vec3(.5f, .5f, .5f));
    vertices.push_back(glm::vec3(-.5f, -.5f, .5f));
    vertices.push_back(glm::vec3(-.5f, -.5f, -.5f));
    vertices.push_back(glm::vec3(.5f, -.5f, -.5f));
    vertices.push_back(glm::vec3(.5f, -.5f, .5f));
    char indices[] = {
        1,2 ,2,3, 3,4, 4,1,
        5,6, 6,7, 7,8, 8,5,
        1,5, 2,6, 3,7, 4,8
    };
    for (int i = 0; i < 24; i++)
        buffer.push_back(VertexFromGLM(vertices[indices[i]-1]));
    
}

void AddCylinder(std::vector<LE3Vertex>& buffer,
    GLfloat x0, GLfloat y0, GLfloat z0,
    GLfloat radius, GLfloat height, GLushort resolution, GLushort withCaps)
{   
    // Generate the vertices for top and bottom caps
    std::vector<LE3Vertex> bottomFace, topFace;
    for (GLushort i = 0; i <= resolution; i++)
    {
        GLfloat theta = (GLfloat)(i % resolution) / (GLfloat) resolution * 2.f * 3.14159265f;
        GLfloat x = x0 + radius * cos(theta);
        GLfloat z = z0 + radius * sin(theta);
        
        glm::vec3 normal(x, 0.f, z);
        glm::vec3 posBottom(x, y0, z);
        glm::vec3 posTop(x, y0 + height, z);

        glm::vec2 uvBottom((GLfloat)i / (GLfloat) resolution, 0.f);
        glm::vec2 uvTop((GLfloat)i / (GLfloat) resolution, height / (2.f * 3.14159265f * radius));

        bottomFace.push_back(VertexFromGLM(posBottom, uvBottom, normal));
        topFace.push_back(VertexFromGLM(posTop, uvTop, normal));
    }  

    // Push data for sides
    for (GLushort i = 0; i < resolution; i++)
    {
        buffer.push_back(bottomFace[i]);
        buffer.push_back(topFace[(i+1)]);
        buffer.push_back(topFace[i]);
        buffer.push_back(bottomFace[i]);
        buffer.push_back(topFace[(i+1)]);
        buffer.push_back(bottomFace[(i+1)]);
    }

    // Push data for caps
    if (withCaps)
    {
        LE3Vertex centerBottom, centerTop;
        centerBottom = VertexFromGLM(glm::vec3(x0, y0, z0), glm::vec2(0.5f, 0.5f), glm::vec3(0.f, -1.f, 0.f));
        centerTop = VertexFromGLM(glm::vec3(x0, y0 + height, z0), glm::vec2(0.5f, 0.5f), glm::vec3(0.f, 1.f, 0.f));

        // Fix uvs
        for (GLushort i = 0; i <= resolution; i++)
        {
            GLfloat theta = (GLfloat)(i % resolution) / (GLfloat) resolution * 2.f * 3.14159265f;
            bottomFace[i].uv[0] = topFace[i].uv[0] = 1.f / (2.f * 3.14159265f) * cosf(theta) + 0.5f;
            bottomFace[i].uv[1] = topFace[i].uv[1] = 1.f / (2.f * 3.14159265f) * sinf(theta) + 0.5f;

            bottomFace[i].normal[0] = 0.f;
            bottomFace[i].normal[1] = -1.f;
            bottomFace[i].normal[2] = 0.f;

            topFace[i].normal[0] = 0.f;
            topFace[i].normal[1] = 1.f;
            topFace[i].normal[2] = 0.f;
        }

        for (GLushort i = 0; i < resolution; i++)
        {
            buffer.push_back(bottomFace[i]);
            buffer.push_back(centerBottom);
            buffer.push_back(bottomFace[i+1]);
            buffer.push_back(topFace[i]);
            buffer.push_back(centerTop);
            buffer.push_back(topFace[i+1]);
        } 
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

        glm::vec2 uv(
            0.5f * cosf(theta) + 0.5f,
            0.5f * sinf(theta) + 0.5f
        );

        bottomFace.push_back(VertexFromGLM(posBottom, uv, normal));
    }

    LE3Vertex topVertex = VertexFromGLM(glm::vec3(x0, y0+height, z0), glm::vec2(0.5f, 0.5f), glm::vec3(0.f, 1.f, 0.f));
    LE3Vertex bottomVertex = VertexFromGLM(glm::vec3(x0, y0, z0), glm::vec2(0.5f, 0.5f), glm::vec3(0.f, 1.f, 0.f));

    for (GLushort i = 0; i < resolution; i++)
    {
        buffer.push_back(bottomFace[i]);
        buffer.push_back(topVertex);
        buffer.push_back(bottomFace[(i+1) % resolution]);

        buffer.push_back(bottomFace[i]);
        buffer.push_back(bottomVertex);
        buffer.push_back(bottomFace[(i+1) % resolution]);
    }
}

void AddSphere(std::vector<LE3Vertex>& buffer,
    GLfloat x0, GLfloat y0, GLfloat z0,
    GLfloat radius, GLushort resolution)
{
    std::vector<LE3Vertex> firstLayer, secondLayer;
    resolution += 1;
    
    for (int i = 0; i <= resolution; i++)
    {
        float theta = (GLfloat) (i % resolution) / (GLfloat)(resolution - 1) * 3.14159265f;
        secondLayer.clear();
        for (int j = 0; j <= resolution; j++)
        {
            float phi = (GLfloat) (j % resolution) / (GLfloat) (resolution - 1) * 2 * 3.14159265f;
            glm::vec3 pos(
                radius * sinf(theta) * cosf(phi) + x0,
                radius * cosf(theta) + y0,
                radius * sinf(theta) * sinf(phi) + z0
            );
            glm::vec2 uv(0.5f * theta / 3.14159265f, 0.5f * phi / 3.14159265f);
            if (i == 0 || i == (resolution-1))
                uv.x += 0.001f;
            glm::vec3 normal(
                sinf(theta) * cosf(phi),
                cosf(theta),
                sinf(theta) * sinf(phi)
            );
            secondLayer.push_back(VertexFromGLM(pos, uv, normal));
        }

        if (i > 0)
        {
            for (int k = 0; k < resolution; k++)
            {
                buffer.push_back(firstLayer[k]);
                buffer.push_back(firstLayer[k+1]); 
                buffer.push_back(secondLayer[k]);
                buffer.push_back(firstLayer[k+1]); 
                buffer.push_back(secondLayer[k]); 
                buffer.push_back(secondLayer[k+1]);
            }
        }

        firstLayer.clear();
        for (int k = 0; k <= resolution; firstLayer.push_back(secondLayer[k++]));
    }
    
}

void AddTorus(std::vector<LE3Vertex>& buffer,
    GLfloat x0, GLfloat y0, GLfloat z0,
    GLfloat majorRadius, GLfloat minorRadius, GLushort resolution)
{
    std::vector<LE3Vertex> firstLayer, secondLayer;
    resolution += 1;

    for (int i = 0; i <= resolution; i++)
    {
        float theta = (GLfloat) (i % resolution) / (GLfloat)(resolution - 1) * 2 * 3.14159265f;
        secondLayer.clear();
        for (int j = 0; j <= resolution; j++)
        {
            float phi = (GLfloat) (j % resolution) / (GLfloat) (resolution - 1) * 2 * 3.14159265f;
            glm::vec3 pos(
                (majorRadius + minorRadius * cosf(phi)) * cosf(theta) + x0,
                (minorRadius * sinf(phi)) + z0,
                (majorRadius + minorRadius * cosf(phi)) * sinf(theta) + y0
            );
            glm::vec2 uv(0.5f * theta / 3.14159265f, 0.5f * phi / 3.14159265f);
            if (i == 0 || i == (resolution-1))
                uv.x += 0.001f;
            glm::vec3 normal(
                sinf(theta) * cosf(phi),
                cosf(theta),
                sinf(theta) * sinf(phi)
            );
            secondLayer.push_back(VertexFromGLM(pos, uv, normal));
        }

        if (i > 0)
        {
            for (int k = 0; k < resolution; k++)
            {
                buffer.push_back(firstLayer[k]);
                buffer.push_back(firstLayer[k+1]); 
                buffer.push_back(secondLayer[k]);
                buffer.push_back(firstLayer[k+1]); 
                buffer.push_back(secondLayer[k]); 
                buffer.push_back(secondLayer[k+1]);
            }
        }

        firstLayer.clear();
        for (int k = 0; k <= resolution; firstLayer.push_back(secondLayer[k++]));
    }
}