#include "editor_gizmo.h"

LE3EditorGizmo::LE3EditorGizmo() :
    LE3Object("_gizmo")
{
}

void LE3EditorGizmo::Init(LE3Material* materialX, LE3Material* materialY, LE3Material* materialZ)
{
    float deltaPosition = gGizmoAxisLength + gGizmoAxisThickness;

    xAxis = new LE3EditorGizmoAxis();
    xAxis->SetName("_gizmoX");
    xAxis->SetPosition(glm::vec3(gGizmoAxisThickness, 0.0f, 0.0f));
    xAxis->SetRotation(glm::vec3(0.f, 0.f, -3.14159265f / 2.f));
    xAxis->SetAxisLine(glm::vec3(1.f, 0.f, 0.f));
    xAxis->Init(materialX);

    yAxis = new LE3EditorGizmoAxis();
    yAxis->SetName("_gizmoY");
    yAxis->SetPosition(glm::vec3(0.0f, gGizmoAxisThickness, 0.0f));
    yAxis->SetRotation(glm::vec3(0.f, 0.f, 0.f));
    yAxis->SetAxisLine(glm::vec3(0.f, 1.f, 0.f));
    yAxis->Init(materialY);

    zAxis = new LE3EditorGizmoAxis();
    zAxis->SetName("_gizmoZ");
    zAxis->SetPosition(glm::vec3(0.0f, 0.0f, gGizmoAxisThickness));
    zAxis->SetRotation(glm::vec3(3.14159265f / 2.f, 0.f, 0.f));
    zAxis->SetAxisLine(glm::vec3(0.f, 0.f, 1.f));
    zAxis->Init(materialZ);


    this->AppendChild(xAxis);
    this->AppendChild(yAxis);
    this->AppendChild(zAxis);
}

void LE3EditorGizmo::UnhoverAxes()
{
    xAxis->SetIsHovered(false);
    yAxis->SetIsHovered(false);
    zAxis->SetIsHovered(false);
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
    m_material->GetShader()->Uniform("hovered", m_bIsHovered);
    LE3StaticMesh::Draw();
    // glEnable(GL_DEPTH_TEST);
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