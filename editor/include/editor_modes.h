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

struct LE3EditorModeState
{
    LE3EditorModeState();

    LE3EditorModes mode;
    
    bool bCanLeftClick;
    bool bHoversGizmo;
    bool bReleaseGizmoFinished;
    glm::vec2 dragInitialPos;
    glm::vec3 selectedInitialPos;
    glm::vec3 deltaPos;
};

void UpdateEditorMode(LE3EditorModeState& editorState, LE3EditorInput& input);