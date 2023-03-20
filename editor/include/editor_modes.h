#pragma once

#include <glm/glm.hpp>

#include "editor_consts.h"
#include "editor_input.h"

enum LE3EditorModes
{
    LE3EDITOR_IDLE,
    LE3EDITOR_SELECT,
    LE3EDITOR_CAMERA,
    LE3EDITOR_GIZMO_DRAG,
    LE3EDITOR_GIZMO_DRAG_RELEASE,
};

enum LE3EditorGizmoModes
{
    LE3EDITOR_GIZMO_SELECT,
    LE3EDITOR_GIZMO_MOVE,
    LE3EDITOR_GIZMO_ROTATE,
    LE3EDITOR_GIZMO_SCALE,
};

struct LE3EditorModeState
{
    LE3EditorModeState();

    LE3EditorModes mode;
    LE3EditorGizmoModes gizmoMode;
    
    bool bCanLeftClick;
    bool bHoversGizmo;
    bool bReleaseGizmoFinished;
    glm::vec2 dragInitialPos;
    glm::vec3 selectedInitialPos;
    glm::vec3 selectedInitialRot;
    float selectedInitialScale;
    glm::vec3 deltaPos;
};

void UpdateEditorMode(LE3EditorModeState& editorState, LE3EditorInput& input);