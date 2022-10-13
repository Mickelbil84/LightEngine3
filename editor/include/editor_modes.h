#pragma once

#include "editor_consts.h"
#include "editor_input.h"

enum LE3EditorModes
{
    LE3EDITOR_IDLE,
    LE3EDITOR_SELECT,
    LE3EDITOR_CAMERA,
    LE3EDITOR_GIZMO_DRAG,
};

struct LE3EditorModeState
{
    LE3EditorModeState();

    LE3EditorModes mode;
    
    bool bCanLeftClick;
};

void UpdateEditorMode(LE3EditorModeState& editorState, LE3EditorInput& input);