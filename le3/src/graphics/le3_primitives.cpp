#include "graphics/le3_primitives.h"
using namespace le3;

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

std::shared_ptr<LE3Mesh<LE3Vertex3p>> le3::createDebugLine() {
    std::vector<LE3Vertex3p> vertices(2);
    vertices[0].position[0] = 0.f; vertices[0].position[1] = 0.f; vertices[0].position[2] = 0.f;
    vertices[1].position[0] = 1.f; vertices[1].position[1] = 1.f; vertices[1].position[2] = 1.f;
    return std::make_shared<LE3Mesh<LE3Vertex3p>>(vertices);
}
std::shared_ptr<LE3Mesh<LE3Vertex3p>> le3::createDebugBox() {
    std::vector<LE3Vertex3p> buffer;
    std::vector<glm::vec3> verts;
    verts.push_back(glm::vec3(-.5f, .5f, .5f));
    verts.push_back(glm::vec3(-.5f, .5f, -.5f));
    verts.push_back(glm::vec3(.5f, .5f, -.5f));
    verts.push_back(glm::vec3(.5f, .5f, .5f));
    verts.push_back(glm::vec3(-.5f, -.5f, .5f));
    verts.push_back(glm::vec3(-.5f, -.5f, -.5f));
    verts.push_back(glm::vec3(.5f, -.5f, -.5f));
    verts.push_back(glm::vec3(.5f, -.5f, .5f));
    char indices[] = {
        1,2 ,2,3, 3,4, 4,1,
        5,6, 6,7, 7,8, 8,5,
        1,5, 2,6, 3,7, 4,8
    };

    for (int i = 0; i < 24; i++)
        buffer.push_back(vertexFromGLM(verts[indices[i]-1]));
    return std::make_shared<LE3Mesh<LE3Vertex3p>>(buffer);
}

std::shared_ptr<LE3Mesh<LE3Vertex3p>> le3::createDebugBoxDiagonals() {
    std::vector<LE3Vertex3p> buffer;
    std::vector<glm::vec3> verts;
    verts.push_back(glm::vec3(-.5f, .5f, .5f));
    verts.push_back(glm::vec3(-.5f, .5f, -.5f));
    verts.push_back(glm::vec3(.5f, .5f, -.5f));
    verts.push_back(glm::vec3(.5f, .5f, .5f));
    verts.push_back(glm::vec3(-.5f, -.5f, .5f));
    verts.push_back(glm::vec3(-.5f, -.5f, -.5f));
    verts.push_back(glm::vec3(.5f, -.5f, -.5f));
    verts.push_back(glm::vec3(.5f, -.5f, .5f));
    char indices[] = {
        1,2 ,2,3, 3,4, 4,1,
        5,6, 6,7, 7,8, 8,5,
        1,5, 2,6, 3,7, 4,8,
        4,7, 6,8, 2,5, 1,3, 
    };
    for (int i = 0; i < 32; i++)
        buffer.push_back(vertexFromGLM(verts[indices[i]-1]));
    return std::make_shared<LE3Mesh<LE3Vertex3p>>(buffer);
}


std::shared_ptr<LE3Mesh<LE3Vertex3p3c>> le3::createHelloOpenGLTriangle() {
    std::vector<LE3Vertex3p3c> vertices(3);
    vertices[0].position[0] = .5f * -1.f; vertices[0].position[1] = .5f * -1.f; vertices[0].position[2] = .5f * 0.f;
    vertices[1].position[0] = .5f *  0.f; vertices[1].position[1] = .5f *  1.f; vertices[1].position[2] = .5f * 0.f;
    vertices[2].position[0] = .5f *  1.f; vertices[2].position[1] = .5f * -1.f; vertices[2].position[2] = .5f * 0.f;

    vertices[0].color[0] =  1.f; vertices[0].color[1] =  0.f; vertices[0].color[2] = 0.f;
    vertices[1].color[0] =  0.f; vertices[1].color[1] =  1.f; vertices[1].color[2] = 0.f;
    vertices[2].color[0] =  0.f; vertices[2].color[1] =  0.f; vertices[2].color[2] = 1.f;
    return std::make_shared<LE3Mesh<LE3Vertex3p3c>>(vertices);
}

std::shared_ptr<LE3ScreenRect> le3::createScreenRect() {
    std::vector<LE3Vertex3p> vertices(6);

    vertices[0].position[0] = -1.f; vertices[0].position[1] = -1.f; vertices[0].position[2] = 0.f;
    vertices[1].position[0] =  1.f; vertices[1].position[1] = -1.f; vertices[1].position[2] = 0.f;
    vertices[2].position[0] =  1.f; vertices[2].position[1] =  1.f; vertices[2].position[2] = 0.f;

    vertices[3].position[0] = -1.f; vertices[3].position[1] = -1.f; vertices[3].position[2] = 0.f;
    vertices[4].position[0] =  1.f; vertices[4].position[1] =  1.f; vertices[4].position[2] = 0.f;
    vertices[5].position[0] = -1.f; vertices[5].position[1] =  1.f; vertices[5].position[2] = 0.f;
    return std::make_shared<LE3Mesh<LE3Vertex3p>>(vertices);
}

std::vector<LE3Vertex> le3::_createPlaneBuffer(float x0, float y0, float z0, float width, float height) {
    std::vector<LE3Vertex> buffer;
    glm::vec3 v1(x0 - .5f * width, y0, z0 - .5f * height);
    glm::vec3 v2(x0 - .5f * width, y0, z0 + .5f * height);
    glm::vec3 v3(x0 + .5f * width, y0, z0 + .5f * height);
    glm::vec3 v4(x0 + .5f * width, y0, z0 - .5f * height);
    glm::vec3 n(0.f, 1.f, 0.f);
    glm::vec2 t1(0.f, 0.f);
    glm::vec2 t2(0.f, 1.f);
    glm::vec2 t3(1.f, 1.f);
    glm::vec2 t4(1.f, 0.f);
    buffer.push_back(vertexFromGLM(v1, t1, n));
    buffer.push_back(vertexFromGLM(v2, t2, n));
    buffer.push_back(vertexFromGLM(v3, t3, n));
    buffer.push_back(vertexFromGLM(v1, t1, n));
    buffer.push_back(vertexFromGLM(v3, t3, n));
    buffer.push_back(vertexFromGLM(v4, t4, n));
    return buffer;
}

std::shared_ptr<LE3Mesh<LE3Vertex>> le3::createPlane(float x0, float y0, float z0, float width, float height) {
    std::vector<LE3Vertex> buffer = _createPlaneBuffer(x0, y0, z0, width, height);
    return std::make_shared<LE3Mesh<LE3Vertex>>(buffer);
}


std::vector<LE3Vertex> le3::_createBoxBuffer(float x0, float y0, float z0, float width, float height, float depth) {
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

    return buffer;
}

std::shared_ptr<LE3Mesh<LE3Vertex>> le3::createBox(float x0, float y0, float z0, float width, float height, float depth) {
    std::vector<LE3Vertex> buffer = _createBoxBuffer(x0, y0, z0, width, height, depth);
    return std::make_shared<LE3Mesh<LE3Vertex>>(buffer);
}

std::vector<LE3Vertex> le3::_createCylinderBuffer(float x0, float y0, float z0, float radius, float height, int resolution, bool withCaps) {
    glm::vec3 centerBottom(x0, y0, z0), centerTop(x0, y0 + height, z0);
    std::vector<glm::vec3> circle;
    for (int i = 0; i < resolution; ++i) {
        float theta = (float)i / (float)resolution * 2.f * M_PI;
        circle.push_back(glm::vec3(cosf(theta), 0.f, sinf(theta)));
    }

    std::vector<LE3Vertex> buffer;

    for (int i = 0; i < resolution; ++i) {
        int i_ = (i+1) % resolution;

        if (withCaps) {
            buffer.push_back(vertexFromGLM(centerBottom + radius * circle[i_], 0.25f * (glm::vec2(circle[i_].x, circle[i_].z) + 1.f), glm::vec3(0.f, -1.f, 0.f)));
            buffer.push_back(vertexFromGLM(centerBottom + radius * circle[i], 0.25f * (glm::vec2(circle[i].x, circle[i].z) + 1.f), glm::vec3(0.f, -1.f, 0.f)));
            buffer.push_back(vertexFromGLM(centerBottom, 0.25f * (glm::vec2(0.f) + 1.f), glm::vec3(0.f, -1.f, 0.f)));

            buffer.push_back(vertexFromGLM(centerTop + radius * circle[i_], 0.25f * (glm::vec2(circle[i_].x, circle[i_].z) + 1.f) + glm::vec2(0.f, 0.5f), glm::vec3(0.f, 1.f, 0.f)));
            buffer.push_back(vertexFromGLM(centerTop + radius * circle[i], 0.25f * (glm::vec2(circle[i].x, circle[i].z) + 1.f) + glm::vec2(0.f, 0.5f), glm::vec3(0.f, 1.f, 0.f)));
            buffer.push_back(vertexFromGLM(centerTop, 0.25f * (glm::vec2(0.f) + 1.f) + glm::vec2(0.f, 0.5f), glm::vec3(0.f, 1.f, 0.f)));
        }

        LE3Vertex v1 = vertexFromGLM(centerBottom + radius * circle[i_], glm::vec2(0.5f + 0.5f* (float)(resolution+1-i-1.f) / (float)(resolution+1.f), 1.f), circle[i_]);
        LE3Vertex v2 = vertexFromGLM(centerBottom + radius * circle[i], glm::vec2(0.5f + 0.5f* (float)(resolution+1-i) / (float)(resolution+1.f), 1.f), circle[i]);
        LE3Vertex v3 = vertexFromGLM(centerTop + radius * circle[i], glm::vec2(0.5f + 0.5f* (float)(resolution+1-i) / (float)(resolution+1.f), 0.f), circle[i]);
        LE3Vertex v4 = vertexFromGLM(centerTop + radius * circle[i_], glm::vec2(0.5f + 0.5f* (float)(resolution+1-i-1.f) / (float)(resolution+1.f), 0.f), circle[i_]);
        buffer.push_back(v1);buffer.push_back(v2);buffer.push_back(v3);
        buffer.push_back(v1);buffer.push_back(v3);buffer.push_back(v4);
    }

    return buffer;
}

std::shared_ptr<LE3Mesh<LE3Vertex>> le3::createCylinder(float x0, float y0, float z0, float radius, float height, int resolution, bool withCaps) {
    std::vector<LE3Vertex> buffer = le3::_createCylinderBuffer(x0, y0, z0, radius, height, resolution, withCaps);
    auto pMesh = std::make_shared<LE3StaticMesh>(buffer);
    pMesh->setColliderType(LE3ColliderType::LE3ColliderType_Cylinder);
    return pMesh;
}

std::shared_ptr<LE3Mesh<LE3Vertex3p>> le3::createDebugCylinder() {
    std::vector<LE3Vertex> tmpBuffer = le3::_createCylinderBuffer(0.f, 0.f, 0.f, 1.f, 1.f, 8, true);
    std::vector<LE3Vertex3p> buffer;
    for (int i = 0; i < tmpBuffer.size(); i += 3) {
        buffer.push_back(vertexFromGLM(glm::vec3(tmpBuffer[i].position[0], tmpBuffer[i].position[1], tmpBuffer[i].position[2])));
        buffer.push_back(vertexFromGLM(glm::vec3(tmpBuffer[i+1].position[0], tmpBuffer[i+1].position[1], tmpBuffer[i+1].position[2])));
        buffer.push_back(vertexFromGLM(glm::vec3(tmpBuffer[i+2].position[0], tmpBuffer[i+2].position[1], tmpBuffer[i+2].position[2])));
        buffer.push_back(vertexFromGLM(glm::vec3(tmpBuffer[i].position[0], tmpBuffer[i].position[1], tmpBuffer[i].position[2])));
    }
    return std::make_shared<LE3Mesh<LE3Vertex3p>>(buffer);
}


std::vector<LE3Vertex> le3::_createConeBuffer(float x0, float y0, float z0, float radius, float height, int resolution, bool withCaps) {
    glm::vec3 centerBottom(x0, y0, z0), centerTop(x0, y0 + height, z0);
    std::vector<glm::vec3> circle;
    for (int i = 0; i < resolution; ++i) {
        float theta = (float)i / (float)resolution * 2.f * M_PI;
        circle.push_back(glm::vec3(cosf(theta), 0.f, sinf(theta)));
    }

    std::vector<LE3Vertex> buffer;

    for (int i = 0; i < resolution; ++i) {
        int i_ = (i+1) % resolution;

        if (withCaps) {
            buffer.push_back(vertexFromGLM(centerBottom + radius * circle[i_], 0.25f * (glm::vec2(circle[i_].x, circle[i_].z) + 1.f), glm::vec3(0.f, -1.f, 0.f)));
            buffer.push_back(vertexFromGLM(centerBottom + radius * circle[i], 0.25f * (glm::vec2(circle[i].x, circle[i].z) + 1.f), glm::vec3(0.f, -1.f, 0.f)));
            buffer.push_back(vertexFromGLM(centerBottom, 0.25f * (glm::vec2(0.f) + 1.f), glm::vec3(0.f, -1.f, 0.f)));
        }

        LE3Vertex v1 = vertexFromGLM(centerBottom + radius * circle[i_], glm::vec2(0.5f + 0.5f * (float)(resolution+1-i-1.f) / (float)(resolution+1.f), 1.f), circle[i_]);
        LE3Vertex v2 = vertexFromGLM(centerBottom + radius * circle[i], glm::vec2(0.5f + 0.5f * (float)(resolution+1.f-i) / (float)(resolution+1.f), 1.f), circle[i]);
        LE3Vertex v3 = vertexFromGLM(centerTop, glm::vec2(0.75f, 0.f), glm::normalize(glm::vec3(1.f)));
        buffer.push_back(v1);buffer.push_back(v2);buffer.push_back(v3);
    }

    return buffer;
}

std::shared_ptr<LE3Mesh<LE3Vertex>> le3::createCone(float x0, float y0, float z0, float radius, float height, int resolution, bool withCaps) {
    std::vector<LE3Vertex> buffer = le3::_createConeBuffer(x0, y0, z0, radius, height, resolution, withCaps);
    auto pMesh = std::make_shared<LE3StaticMesh>(buffer);
    pMesh->setColliderType(LE3ColliderType::LE3ColliderType_Cone);
    return pMesh;
}

std::vector<LE3Vertex> le3::_createTorusBuffer(float x0, float y0, float z0, float majorRadius, float minorRadius, int resolution) {
    std::vector<LE3Vertex> buffer;
    std::vector<LE3Vertex> firstLayer, secondLayer;
    resolution += 1;

    for (int i = 0; i <= resolution; i++)
    {
        float theta = (float) (i % resolution) / (float)(resolution - 1) * 2 * 3.14159265f;
        secondLayer.clear();
        for (int j = 0; j <= resolution; j++)
        {
            float phi = (float) (j % resolution) / (float) (resolution - 1) * 2 * 3.14159265f;
            glm::vec3 pos(
                (majorRadius + minorRadius * cosf(phi)) * cosf(theta) + x0,
                (minorRadius * sinf(phi)) + z0,
                (majorRadius + minorRadius * cosf(phi)) * sinf(theta) + y0
            );
            glm::vec2 uv(0.5f * theta / 3.14159265f, 0.5f * phi / 3.14159265f);
            if (i == 0 || i == (resolution-1))
                uv.x += 0.001f;
            glm::vec3 normal(
                cosf(theta) * cosf(phi),
                sinf(phi),
                sinf(theta) * cosf(phi)
            );
            secondLayer.push_back(vertexFromGLM(pos, uv, normal));
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

    return buffer;
}

std::shared_ptr<LE3Mesh<LE3Vertex>> le3::createTorus(float x0, float y0, float z0, float majorRadius, float minorRadius, int resolution) {
    std::vector<LE3Vertex> buffer = le3::_createTorusBuffer(x0, y0, z0, majorRadius, minorRadius, resolution);
    auto pMesh = std::make_shared<LE3StaticMesh>(buffer);
    pMesh->setColliderType(LE3ColliderType::LE3ColliderType_ConvexHull);
    return pMesh;
}

std::vector<LE3Vertex> le3::_createSphereBuffer(float x0, float y0, float z0, float radius, int resolution, int hemisphere) {
    std::vector<LE3Vertex> buffer;
    std::vector<LE3Vertex> firstLayer, secondLayer;
    int factor = 1;
    // if (hemisphere != 0) factor = 2;
    resolution += 1;

    for (int i = 0; i <= resolution / factor; i++)
    {
        float theta = (float) (i % resolution) / (float)(resolution - 1) * 3.14159265f - 3.14159265f / 2.f;
        if (hemisphere > 0) theta = 0.5f * (theta + 3.14159265f / 2.f);
        else if (hemisphere < 0) theta = 0.5f * (theta - 3.14159265f / 2.f);
        secondLayer.clear();
        for (int j = 0; j <= resolution; j++)
        {
            float phi = (float) (j % resolution) / (float) (resolution - 1) * 2 * 3.14159265f;
            glm::vec3 pos(
                radius * cosf(theta) * cosf(phi) + x0,
                radius * sinf(theta) + y0,
                radius * cosf(theta) * sinf(phi) + z0
            );
            glm::vec2 uv(0.5f * theta / 3.14159265f, 0.5f * phi / 3.14159265f);
            if (i == 0 || i == (resolution-1))
                uv.x += 0.001f;
            glm::vec3 normal(
                cosf(theta) * cosf(phi),
                sinf(theta),
                cosf(theta) * sinf(phi)
            );
            secondLayer.push_back(vertexFromGLM(pos, uv, normal));
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

    return buffer;
}

std::shared_ptr<LE3Mesh<LE3Vertex>> le3::createSphere(float x0, float y0, float z0, float radius, int resolution) {
    std::vector<LE3Vertex> buffer = le3::_createSphereBuffer(x0, y0, z0, radius, resolution);
    auto pMesh = std::make_shared<LE3StaticMesh>(buffer);
    pMesh->setColliderType(LE3ColliderType::LE3ColliderType_Sphere);
    return pMesh;
}


std::shared_ptr<LE3Mesh<LE3Vertex3p>> le3::createDebugCone() {
    std::vector<LE3Vertex> tmpBuffer = le3::_createConeBuffer(0.f, 0.f, 0.f, 1.f, 1.f, 8, true);
    std::vector<LE3Vertex3p> buffer;
    for (int i = 0; i < tmpBuffer.size(); i += 3) {
        buffer.push_back(vertexFromGLM(glm::vec3(tmpBuffer[i].position[0], tmpBuffer[i].position[1], tmpBuffer[i].position[2])));
        buffer.push_back(vertexFromGLM(glm::vec3(tmpBuffer[i+1].position[0], tmpBuffer[i+1].position[1], tmpBuffer[i+1].position[2])));
        buffer.push_back(vertexFromGLM(glm::vec3(tmpBuffer[i+2].position[0], tmpBuffer[i+2].position[1], tmpBuffer[i+2].position[2])));
        buffer.push_back(vertexFromGLM(glm::vec3(tmpBuffer[i].position[0], tmpBuffer[i].position[1], tmpBuffer[i].position[2])));
    }
    return std::make_shared<LE3Mesh<LE3Vertex3p>>(buffer);
}

std::shared_ptr<LE3Mesh<LE3Vertex3p>> le3::createDebugCapsule() {
    std::vector<LE3Vertex> tmpBuffer;
    std::vector<LE3Vertex> topSphere = le3::_createSphereBuffer(0.f, 0.75f, 0.f, 0.25f, 8, 1);
    std::vector<LE3Vertex> middle = le3::_createCylinderBuffer(0.f, 0.25f, 0.f, 0.25f, 0.5f, 8, false);
    std::vector<LE3Vertex> bottomSphere = le3::_createSphereBuffer(0.f, 0.25f, 0.f, 0.25f, 8, -1);
    std::copy(topSphere.begin(), topSphere.end(), std::back_inserter(tmpBuffer));
    std::copy(middle.begin(), middle.end(), std::back_inserter(tmpBuffer));
    std::copy(bottomSphere.begin(), bottomSphere.end(), std::back_inserter(tmpBuffer));

    std::vector<LE3Vertex3p> buffer;
    for (int i = 0; i < tmpBuffer.size(); i += 3) {
        buffer.push_back(vertexFromGLM(glm::vec3(tmpBuffer[i].position[0], tmpBuffer[i].position[1], tmpBuffer[i].position[2])));
        buffer.push_back(vertexFromGLM(glm::vec3(tmpBuffer[i+1].position[0], tmpBuffer[i+1].position[1], tmpBuffer[i+1].position[2])));
        buffer.push_back(vertexFromGLM(glm::vec3(tmpBuffer[i+2].position[0], tmpBuffer[i+2].position[1], tmpBuffer[i+2].position[2])));
        buffer.push_back(vertexFromGLM(glm::vec3(tmpBuffer[i].position[0], tmpBuffer[i].position[1], tmpBuffer[i].position[2])));
    }
    return std::make_shared<LE3Mesh<LE3Vertex3p>>(buffer);
}

std::shared_ptr<LE3Mesh<LE3Vertex3p>> le3::createDebugSphere() {
    std::vector<LE3Vertex> tmpBuffer = le3::_createSphereBuffer(0.f, 0.f, 0.f, 1.f, 8);
    std::vector<LE3Vertex3p> buffer;
    for (int i = 0; i < tmpBuffer.size(); i += 3) {
        buffer.push_back(vertexFromGLM(glm::vec3(tmpBuffer[i].position[0], tmpBuffer[i].position[1], tmpBuffer[i].position[2])));
        buffer.push_back(vertexFromGLM(glm::vec3(tmpBuffer[i+1].position[0], tmpBuffer[i+1].position[1], tmpBuffer[i+1].position[2])));
        buffer.push_back(vertexFromGLM(glm::vec3(tmpBuffer[i+2].position[0], tmpBuffer[i+2].position[1], tmpBuffer[i+2].position[2])));
        buffer.push_back(vertexFromGLM(glm::vec3(tmpBuffer[i].position[0], tmpBuffer[i].position[1], tmpBuffer[i].position[2])));
    }
    return std::make_shared<LE3Mesh<LE3Vertex3p>>(buffer);
}

std::shared_ptr<LE3Mesh<LE3Vertex>> le3::createGizmoArrow() {
    // TODO: Make constants in engine config
    std::vector<LE3Vertex> buffer = le3::_createCylinderBuffer(0.f, 0.f, 0.f, 0.015f, 0.5f, 8, true);
    std::vector<LE3Vertex> cone = le3::_createConeBuffer(0.f, 0.5f, 0.f, 0.035f, 0.065f, 8, true);
    std::copy(cone.begin(), cone.end(), std::back_inserter(buffer));
    return std::make_shared<LE3StaticMesh>(buffer);
}

std::shared_ptr<LE3Mesh<LE3Vertex>> le3::createGizmoScaleArrow() {
    // TODO: Make constants in engine config
    std::vector<LE3Vertex> buffer = le3::_createCylinderBuffer(0.f, 0.f, 0.f, 0.015f, 0.5f, 8, true);
    std::vector<LE3Vertex> box = le3::_createBoxBuffer(0.f, 0.5f, 0.f, 0.04f, 0.04f, 0.04f);
    std::copy(box.begin(), box.end(), std::back_inserter(buffer));
    return std::make_shared<LE3StaticMesh>(buffer);
}

std::shared_ptr<LE3Mesh<LE3Vertex>> le3::createGizmoCircle() {
    return createTorus(0.f, 0.f, 0.f, 0.4f, 0.01f, 32);
}

std::shared_ptr<LE3Mesh<LE3Vertex>> le3::createGizmoPlane() {
    return createBox(0.25f, 0.25f, 0.f, 0.075f, 0.075f, 0.001f);
}

std::shared_ptr<LE3Mesh<LE3Vertex>> le3::createGizmoCenter() {
    // TODO: Make constants in engine config
    return createBox(0.f, 0.f, 0.f, 0.06f, 0.06f, 0.06f);
}