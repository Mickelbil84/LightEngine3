#include "editor_gizmo.h"

LE3EditorGizmo::LE3EditorGizmo() :
    LE3Object("_gizmo")
{
}

void LE3EditorGizmo::Init()
{
    InitMaterials();

    float deltaPosition = gGizmoAxisLength + gGizmoAxisThickness;

    xAxis = new LE3EditorGizmoAxis();
    xAxis->SetName("_gizmoX");
    xAxis->SetPosition(glm::vec3(gGizmoAxisThickness, 0.0f, 0.0f));
    xAxis->SetRotation(glm::vec3(0.f, 0.f, -3.14159265f / 2.f));
    xAxis->SetAxisLine(glm::vec3(1.f, 0.f, 0.f));
    xAxis->Init(&materialX);

    yAxis = new LE3EditorGizmoAxis();
    yAxis->SetName("_gizmoY");
    yAxis->SetPosition(glm::vec3(0.0f, gGizmoAxisThickness, 0.0f));
    yAxis->SetRotation(glm::vec3(0.f, 0.f, 0.f));
    yAxis->SetAxisLine(glm::vec3(0.f, 1.f, 0.f));
    yAxis->Init(&materialY);

    zAxis = new LE3EditorGizmoAxis();
    zAxis->SetName("_gizmoZ");
    zAxis->SetPosition(glm::vec3(0.0f, 0.0f, gGizmoAxisThickness));
    zAxis->SetRotation(glm::vec3(3.14159265f / 2.f, 0.f, 0.f));
    zAxis->SetAxisLine(glm::vec3(0.f, 0.f, 1.f));
    zAxis->Init(&materialZ);


    this->AppendChild(xAxis);
    this->AppendChild(yAxis);
    this->AppendChild(zAxis);
}

void LE3EditorGizmo::InitMaterials()
{
    std::string vertexShaderSource = std::string(
        "#version 410 core \n"
        "layout(location = 0) in vec4 vPosition;\n"
        "layout(location = 1) in vec2 vTexCoord;\n"
        "layout(location = 2) in vec3 vNormal;\n"
        "uniform mat4 model;\n"
        "uniform mat4 view;\n"
        "uniform mat4 projection;\n"
        "out vec4 normalColor;\n"
        "void main()\n"
        "{\n"
        "    gl_Position = projection * view * model * vPosition;\n"
        "    normalColor = vec4(vNormal, 1.0);\n"
        "}");
    std::string fragmentShaderSource = std::string(
        "#version 410 core \n"
        "struct Material\n"
        "{\n"
        "   vec4 diffuseColor;\n"
        "   sampler2D diffuseTexture;\n"
        "   bool bUseDiffuseTexture;\n"
        "};\n"
        "uniform Material material;\n"
        "uniform bool hovered;\n"
        "out vec4 fColor;\n"
        "in vec4 normalColor;\n"
        "void main()\n"
        "{\n"
        "    // Diffuse color\n"
        "    vec4 diffuseColor = material.diffuseColor;\n"
        "    if (hovered)\n"
        "       diffuseColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);\n"
        "    // Lambert light\n"
        "    vec3 dir = normalize(vec3(1, 0.5, 1));\n"
        "    float light = max(0, dot(dir, normalize(vec3(normalColor)))) + 0.5f;\n"
        "    fColor = light * diffuseColor;\n"
        "}");
    gizmoShader = new LE3Shader();
    gizmoShader->CompileShaderFromSource(vertexShaderSource, fragmentShaderSource);
    gizmoShader->SetName("gizmoShader");
    materialX.SetShader(gizmoShader);
    materialX.diffuseColor = glm::vec4(1.f, 0.f, 0.f, 1.f);
    materialY.SetShader(gizmoShader);
    materialY.diffuseColor = glm::vec4(0.f, 1.f, 0.f, 1.f);
    materialZ.SetShader(gizmoShader);
    materialZ.diffuseColor = glm::vec4(0.f, 0.f, 1.f, 1.f);
}

void LE3EditorGizmo::UnhoverAxes()
{
    xAxis->SetIsHovered(false);
    yAxis->SetIsHovered(false);
    zAxis->SetIsHovered(false);
}

LE3Shader* LE3EditorGizmo::GetGizmoShader() const
{
    return gizmoShader;
}

void LE3EditorGizmoAxis::Init(LE3Material* gizmoMaterial)
{
    std::vector<LE3Vertex> axisBox;
    // AddBox(axisBox, 0.f, 0.f, 0.f, gGizmoAxisLength, gGizmoAxisThickness, gGizmoAxisThickness);
    AddCylinder(axisBox, 0.f, 0.f, 0.f, gGizmoAxisThickness, gGizmoAxisLength, 16);
    AddCone(axisBox, 0.f, gGizmoAxisLength, 0.f, gGizmoConeThicnkess, gGizmoConeLength, 16);
    m_mesh = new LE3Mesh<LE3Vertex>();
    this->m_mesh->LoadMeshData(axisBox);
    this->SetMaterial(gizmoMaterial);
    this->m_bIsHovered = false;
}

void LE3EditorGizmoAxis::Draw()
{
    // glDisable(GL_DEPTH_TEST);
    glClear(GL_DEPTH_BUFFER_BIT);
    m_material->GetShader()->Use();
    m_material->GetShader()->Uniform("hovered", (GLuint)m_bIsHovered);
    LE3StaticMesh::Draw();
    // glEnable(GL_DEPTH_TEST);
}
void LE3EditorGizmoAxis::Draw(LE3Shader* shader)
{
}

bool LE3EditorGizmoAxis::GetIsHovered() const
{
    return m_bIsHovered;
}
void LE3EditorGizmoAxis::SetIsHovered(bool isHovered)
{
    m_bIsHovered = isHovered;
}

glm::vec3 LE3EditorGizmoAxis::GetAxisLine() const
{
    return m_axisLine;
}
void LE3EditorGizmoAxis::SetAxisLine(glm::vec3 line)
{
    this->m_axisLine = line;
}

bool LE3EditorGizmoAxis::CheckIfHoveredByMouse(glm::mat4 projViewMatrix, glm::vec2 cursorPosition)
{
    glm::vec3 pWorld = glm::vec3(GetModelMatrix() * glm::vec4(0.f, 0.f, 0.f, 1.f));
    glm::vec3 qWorld = glm::vec3(GetModelMatrix() * glm::vec4(0.f, gGizmoAxisLength, 0.f, 1.f));
    glm::vec2 pScreen = WorldToScreen(projViewMatrix, pWorld);
    glm::vec2 qScreen = WorldToScreen(projViewMatrix, qWorld);

    float dist = minimum_distance(pScreen, qScreen, cursorPosition);
    if (dist < gGizmoSelectionDist)
    {
        SetIsHovered(true);
        return true;
    }
    return false;
}