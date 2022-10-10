#pragma once

#include <le3_object.h>
#include <le3_static_mesh.h>
#include <le3_primitives.h>

const float gGizmoAxisThickness = 0.01f;
const float gGizmoAxisLength = 0.3f;
const float gGizmoConeThicnkess = 1.5f * gGizmoAxisThickness;
const float gGizmoConeLength = 3.f * gGizmoAxisThickness;
const float gGizmoScaleFactor = 0.5f;

class LE3EditorGizmo : public LE3Object
{
public:
    LE3EditorGizmo();

    void Init(LE3Material* materialX, LE3Material* materialY, LE3Material* materialZ);
};

class LE3EditorGizmoAxis : public LE3StaticMesh
{
public:
    void Init(LE3Material* gizmoMaterial);

    virtual void Draw();

    // virtual void Update(double deltaTime);
    // virtual void Draw();
};