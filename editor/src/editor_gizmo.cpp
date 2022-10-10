#include "editor_gizmo.h"

LE3EditorGizmo::LE3EditorGizmo() :
    LE3Object("_gizmo")
{
}

void LE3EditorGizmo::Init(LE3Material* materialX, LE3Material* materialY, LE3Material* materialZ)
{
    float deltaPosition = gGizmoAxisLength + gGizmoAxisThickness;

    LE3EditorGizmoAxis* xAxis = new LE3EditorGizmoAxis();
    xAxis->SetName("_gizmoX");
    xAxis->SetPosition(glm::vec3(gGizmoAxisThickness, 0.0f, 0.0f));
    xAxis->SetRotation(glm::vec3(0.f, 0.f, -3.14159265f / 2.f));
    xAxis->Init(materialX);

    LE3EditorGizmoAxis* yAxis = new LE3EditorGizmoAxis();
    yAxis->SetName("_gizmoY");
    yAxis->SetPosition(glm::vec3(0.0f, gGizmoAxisThickness, 0.0f));
    yAxis->SetRotation(glm::vec3(0.f, 0.f, 0.f));
    yAxis->Init(materialY);

    LE3EditorGizmoAxis* zAxis = new LE3EditorGizmoAxis();
    zAxis->SetName("_gizmoZ");
    zAxis->SetPosition(glm::vec3(0.0f, 0.0f, gGizmoAxisThickness));
    zAxis->SetRotation(glm::vec3(3.14159265f / 2.f, 0.f, 0.f));
    zAxis->Init(materialZ);


    this->AppendChild(xAxis);
    this->AppendChild(yAxis);
    this->AppendChild(zAxis);
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
}

void LE3EditorGizmoAxis::Draw()
{
    // glDisable(GL_DEPTH_TEST);
    glClear(GL_DEPTH_BUFFER_BIT);
    LE3StaticMesh::Draw();
    // glEnable(GL_DEPTH_TEST);
}