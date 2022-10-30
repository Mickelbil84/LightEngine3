#pragma once

#include <map>
#include <math.h>

#include <le3_application.h>
#include <le3_shader.h>
#include <le3_mesh.h>
#include <le3_primitives.h>
#include <le3_camera.h>
#include <le3_texture.h>
#include <le3_material.h>
#include <le3_scene_root.h>
#include <le3_static_mesh.h>
#include <le3_asset_manager.h>
#include <le3_scene_manager.h>
#include <le3_physics.h>
#include <le3_visual_debug.h>

#include "editor_input.h"
#include "editor_modes.h"
#include "editor_math.h"
#include "editor_gizmo.h"

class LE3SelectCallback
{
public:
    virtual void callback() = 0;
};

class LE3RefreshPropertiesCallback
{
public:
    virtual void callback() = 0;
};

class LE3Editor
{
    // Editor input modes and states
    LE3EditorModeState m_editorState;
    LE3EditorInput m_lastInput;

    LE3Object* m_selectedObject;
    LE3EditorGizmoAxis* m_draggedGizmoAxis;


    LE3EditorGizmo gizmo;
    LE3Object* hoveredObject;
    LE3SelectCallback* selectCallback;
    LE3RefreshPropertiesCallback* refreshPropertiesCallback;

    bool bClickUp;

    glm::vec3 p, q;

    LE3Object car, wheelsFront, wheelsBack;
	LE3StaticMesh carBodyMesh, wheel1, wheel2, wheel3, wheel4;

public:
    LE3Editor();

    LE3SceneManager scene;
    std::string scenePath;
    int paneWidth, paneHeight;
    bool bPauseEngine;

public:
    void Init();
    void Update(float deltaTime);
    void HandleInput(LE3EditorInput input);
    void Render(int width, int height);

    LE3EditorGizmo* GetGizmo() const;
    LE3Object* GetHoveredObject() const;
    void SetSelectCallback(LE3SelectCallback* callback);
    void SetSelectedObject(LE3Object* obj);
    LE3Object* GetSelectedObject() const;
    void SetRefreshPropertiesCallback(LE3RefreshPropertiesCallback* callback);

    void ModeIdle();
    void ModeSelect();
    void ModeCamera(LE3EditorInput input);
    void ModeGizmoDrag(LE3EditorInput input);
    void ModeGizmoDragRelease();

    bool UpdateHoveredGizmo(LE3EditorInput input); // return true if gizmo is hovered
    void UpdateHoveredObject(LE3EditorInput input);
};