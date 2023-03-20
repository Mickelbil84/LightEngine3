#pragma once

#include <le3_object.h>
#include <le3_static_mesh.h>
#include <le3_primitives.h>

#include "editor_consts.h"
#include "editor_math.h"


class LE3EditorGizmoAxis : public LE3StaticMesh
{
public:
    void Init(LE3Material* gizmoMaterial);

    virtual void Draw();
    virtual void Draw(LE3Shader* shader);

    bool GetIsHovered() const;
    void SetIsHovered(bool isHovered);

    bool CheckIfHoveredByMouse(glm::mat4 projViewMatrix, glm::vec2 cursorPosition);

    glm::vec3 GetAxisLine() const;
    void SetAxisLine(glm::vec3 line);

private:
    bool m_bIsHovered;
    glm::vec3 m_axisLine;
};

class LE3EditorGizmo : public LE3Object
{
public:
    LE3EditorGizmo();

    void Init();

    LE3EditorGizmoAxis *xAxis, *yAxis, *zAxis;

    // Reset bIsHovered for all axes
    void UnhoverAxes();

    LE3Shader* GetGizmoShader() const;

private:

    void InitMaterials();

    LE3Shader* gizmoShader;
    LE3Material materialX, materialY, materialZ;
};
