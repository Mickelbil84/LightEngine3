#pragma once

#include <le3_object.h>
#include <le3_static_mesh.h>
#include <le3_primitives.h>

#include "editor_consts.h"

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
};