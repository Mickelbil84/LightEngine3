#include "editor_modes.h"

LE3EditorModeState::LE3EditorModeState() :
    mode(LE3EditorModes::LE3EDITOR_IDLE),
    bCanLeftClick(true)
{
}

void UpdateEditorMode(LE3EditorModeState& editorState, LE3EditorInput& input)
{
    switch (editorState.mode)
    {
    case LE3EditorModes::LE3EDITOR_IDLE:
        if (input.bLeftMouse)
        {
            if (input.keyboard[gEditorLookAroundKey])
            {
                editorState.mode = LE3EditorModes::LE3EDITOR_CAMERA;
                return;
            }
            else if (editorState.bCanLeftClick)
            {
                editorState.mode = LE3EditorModes::LE3EDITOR_SELECT;
                editorState.bCanLeftClick = false;
                return;
            }
        }
        else
        {
            editorState.bCanLeftClick = true;
        }
        break;

    case LE3EditorModes::LE3EDITOR_SELECT:
        editorState.mode = LE3EditorModes::LE3EDITOR_IDLE;
        break;

    case LE3EditorModes::LE3EDITOR_CAMERA:
        if (!input.keyboard[gEditorLookAroundKey])
        {
            editorState.mode = LE3EditorModes::LE3EDITOR_IDLE;
            if (input.bLeftMouse)
                editorState.bCanLeftClick = false;
        }
        break;

    case LE3EditorModes::LE3EDITOR_GIZMO_DRAG:
        break;
    
    default:
        break;
    }
}