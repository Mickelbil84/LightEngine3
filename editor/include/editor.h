#pragma once

#include <map>

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

#include "editor_gizmo.h"

struct LE3EditorInput
{
    std::map<int, bool> keyboard;
	int xrel, yrel;
    int mouseX, mouseY;
    int screenWidth, screenHeight;
    float relativeMouseX, relativeMouseY;
    bool bLeftMouse;
};

class LE3SelectCallback
{
public:
    virtual void callback() = 0;
};

class LE3Editor
{
    LE3SceneRoot root;
    LE3EditorGizmo gizmo;
    LE3PhysicsComponent physics;
    LE3Object* hoveredObject;
    LE3SelectCallback* selectCallback;
    bool bClickUp;

    LE3Object car, wheelsFront, wheelsBack;
	LE3StaticMesh carBodyMesh, wheel1, wheel2, wheel3, wheel4;
	LE3FreeCamera camera;

public:
    LE3Editor();

    LE3SceneManager scene;
    int paneWidth, paneHeight;

public:
    void Init();
    void Update(float deltaTime);
    void HandleInput(LE3EditorInput input);
    void Render(int width, int height);

    LE3Object* GetRoot() const;
    LE3EditorGizmo* GetGizmo() const;
    LE3Object* GetHoveredObject() const;
    void SetSelectCallback(LE3SelectCallback* callback);
};