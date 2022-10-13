#pragma once

#include "le3_mesh.h"
#include "le3_shader.h"
#include "le3_camera.h"
#include "le3_primitives.h"

class LE3VisualDebug
{
public:
    // Generates all shaders and meshes for debugging.
    // Note that this initializes static members. 
    // Should only be called once, at the initialization of the program
    static void Init(LE3Camera* camera);

    static void DrawDebugLine(glm::vec3 start, glm::vec3 end, glm::vec3 color);
    static void DrawDebugCube(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, glm::vec3 color);
private:
    static LE3Mesh<LE3Vertex3p> *m_pDebugCube, *m_pDebugCylinder, *m_pDebugCone, *m_pDebugLine;
    static LE3Shader* m_pDebugShader;
    static LE3Camera* m_pCamera;
};

