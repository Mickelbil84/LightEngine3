#include "le3_visual_debug.h"

LE3Mesh<LE3Vertex3p>* LE3VisualDebug::m_pDebugCube = nullptr;
LE3Mesh<LE3Vertex3p>* LE3VisualDebug::m_pDebugCylinder = nullptr;
LE3Mesh<LE3Vertex3p>* LE3VisualDebug::m_pDebugCone = nullptr;
LE3Shader* LE3VisualDebug::m_pDebugShader = nullptr;
LE3Camera* LE3VisualDebug::m_pCamera = nullptr;

void LE3VisualDebug::Init(LE3Camera* camera)
{
    std::string vertexShaderSource = std::string(
        "#version 410 core \n"
        "layout(location = 0) in vec4 vPosition;\n"
        "uniform mat4 model;\n"
        "uniform mat4 view;\n"
        "uniform mat4 projection;\n"
        "void main()\n"
        "{\n"
        "    gl_Position = projection * view * model * vPosition;\n"
        "}");
    std::string fragmentShaderSource = std::string(
        "#version 410 core \n"
        "uniform vec3 debugColor;\n"
        "out vec4 outColor;\n"
        "void main()\n"
        "{\n"
        "    outColor = vec4(debugColor, 1.0);\n"
        "}");

    m_pDebugShader = new LE3Shader();
    m_pDebugShader->CompileShaderFromSource(vertexShaderSource, fragmentShaderSource);

    std::vector<LE3Vertex3p> tmpData;

    m_pDebugCube = new LE3Mesh<LE3Vertex3p>();
    tmpData.clear();
    AddDebugBox(tmpData);
    m_pDebugCube->LoadMeshData(tmpData);
    std::cout << m_pDebugCube->m_count << std::endl;

    m_pCamera = camera;

}

void LE3VisualDebug::DrawDebugCube(glm::vec3 color)
{
    glm::mat4 model(1.f);

    m_pDebugShader->Use();
    m_pDebugShader->Uniform("view", m_pCamera->GetViewMatrix());
    m_pDebugShader->Uniform("projection", m_pCamera->GetProjectionMatrix());
    m_pDebugShader->Uniform("model", model);
    m_pDebugShader->Uniform("debugColor", color);
    m_pDebugCube->Draw(GL_LINES);

}