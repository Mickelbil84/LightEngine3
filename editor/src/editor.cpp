#include "editor.h"
#include "wx/wx.h"

#ifndef __APPLE__
const std::string resource_prefix = std::string("../../");
#else
const std::string resource_prefix = std::string("../");
#endif

LE3Editor::LE3Editor() :
    hoveredObject(nullptr),
    selectCallback(nullptr),
    m_selectedObject(nullptr),
    m_draggedGizmoAxis(nullptr),
    bClickUp(true)
{

}

void LE3Editor::Init()
{
    //
    // Manually start the physics engine
    //
    this->physics.Init();

    // ------------------------
    // Setup Gizmo and Camera
    // ------------------------
    gizmo.Init();
    gizmo.SetHiddenInSceneGraph(true);
    gizmo.SetHidden(true);
    root.AppendChild(&gizmo);

    camera.SetPosition(glm::vec3(0.f, 0.5f, 5.f));
    camera.SetHiddenInSceneGraph(true);
    root.AppendChild(&camera);

    LE3VisualDebug::Init(&camera);

    // ---------------------------
    //   Load Assets
    // ---------------------------

    scene.assets.LoadShader("basic", 
        resource_prefix + "resources/shaders/basic/basic.vs", 
        resource_prefix + "resources/shaders/basic/basic.fs");

    scene.assets.LoadMesh("floor", "$BOX_0_-0.1_0_10_0.1_10_");
    
    scene.assets.LoadMesh("wheel", resource_prefix + "resources/models/cars/Audi R8 Wheel.fbx");
    scene.assets.LoadMesh("carBody", resource_prefix + "resources/models/cars/Audi R8 Body.fbx");
    scene.assets.LoadMesh("barrel", resource_prefix + "resources/models/gahan/barrel.obj");
    scene.assets.LoadMesh("buffer", resource_prefix + "resources/models/gahan/buffer.obj");
    

    scene.assets.CreateMaterial("red", "basic");
    scene.assets.GetMaterial("red")->diffuseColor = glm::vec4(1.f, 0.f, 0.f, 1.f);
    scene.assets.CreateMaterial("green", "basic");
    scene.assets.GetMaterial("green")->diffuseColor = glm::vec4(0.f, 1.f, 0.f, 1.f);
    scene.assets.CreateMaterial("blue", "basic");
    scene.assets.GetMaterial("blue")->diffuseColor = glm::vec4(0.f, 0.f, 1.f, 1.f);
    scene.assets.CreateMaterial("yellow", "basic");
    scene.assets.GetMaterial("yellow")->diffuseColor = glm::vec4(1.f, 1.f, 0.f, 1.f);

    scene.assets.CreateMaterial("carBody", "basic");
    scene.assets.LoadTexture("wood", resource_prefix + "resources/textures/woodparquet_59-2K/woodparquet_59_basecolor-2K-2K.png");
    scene.assets.GetMaterial("carBody")->SetDiffuseTexture(scene.assets.GetTexture("wood"));
    scene.assets.GetMaterial("carBody")->bUseDiffuseTexture = false;

    scene.assets.CreateMaterial("barrelMat", "basic");
    scene.assets.LoadTexture("barrelDiffuse", resource_prefix + "resources/textures/gahan/barrel_diffuse.tga");
    scene.assets.GetMaterial("barrelMat")->SetDiffuseTexture(scene.assets.GetTexture("barrelDiffuse"));
    scene.assets.GetMaterial("barrelMat")->bUseDiffuseTexture = true;

    scene.assets.CreateMaterial("bufferMat", "basic");
    scene.assets.LoadTexture("bufferDiffuse", resource_prefix + "resources/textures/gahan/buffer_diffuse.tga");
    scene.assets.GetMaterial("bufferMat")->SetDiffuseTexture(scene.assets.GetTexture("bufferDiffuse"));
    scene.assets.GetMaterial("bufferMat")->bUseDiffuseTexture = true;

    scene.assets.CreateMaterial("floorMat", "basic");
    scene.assets.LoadTexture("floorDiffuse", resource_prefix + "resources/textures/tile_floor.jpg");
    scene.assets.GetMaterial("floorMat")->SetDiffuseTexture(scene.assets.GetTexture("floorDiffuse"));
    scene.assets.GetMaterial("floorMat")->bUseDiffuseTexture = true;

    scene.SaveAssets("demo_assets.json");
    // scene.LoadAssets("demo_assets.json");
    

    
    // ---------------------------
    //   Create game objects
    // ---------------------------

    LE3StaticMesh* floor = new LE3StaticMesh("floor");
    floor->SetMesh(scene.assets.GetMesh("floor"));
    floor->SetMaterial(scene.assets.GetMaterial("floorMat"));
    floor->RegisterCollision(&physics);
    root.AppendChild(floor);

    LE3StaticMesh* barrel = new LE3StaticMesh("barrel");
    barrel->SetPosition(glm::vec3(1.f, 0.3f, 1.2f));
    barrel->SetMesh(scene.assets.GetMesh("barrel"));
    barrel->SetMaterial(scene.assets.GetMaterial("barrelMat"));
    barrel->SetScale(0.15f);
    barrel->RegisterCollision(&physics);
    root.AppendChild(barrel);

    LE3StaticMesh* buffer = new LE3StaticMesh("buffer");
    buffer->SetPosition(glm::vec3(-2.f, 0.025f, 1.2f));
    buffer->SetMesh(scene.assets.GetMesh("buffer"));
    buffer->SetMaterial(scene.assets.GetMaterial("bufferMat"));
    buffer->SetScale(0.15f);
    buffer->RegisterCollision(&physics);
    root.AppendChild(buffer);
    

    car.SetName("Car");
    // car.SetPosition(glm::vec3(0.f, 5.f, -5.f));
    car.SetRotation(glm::vec3(0.f, 3.14159265f / 4.f, 0.f));
    root.AppendChild(&car);

    carBodyMesh.SetName("CarBodyMesh");
    carBodyMesh.SetMesh(scene.assets.GetMesh("carBody"));
    carBodyMesh.SetMaterial(scene.assets.GetMaterial("carBody"));
    carBodyMesh.SetScale(0.3f);
    carBodyMesh.SetRotation(glm::vec3(-3.14159265f / 2.f, 0.f, -3.14159265f / 2.f));
    carBodyMesh.RegisterCollision(&physics);
    car.AppendChild(&carBodyMesh);

    wheelsFront.SetName("WheelsFront");
    wheelsFront.SetPosition(glm::vec3(-.705f, 0.175f, 0.f));
    car.AppendChild(&wheelsFront);
    wheelsBack.SetName("WheelsBack");
    wheelsBack.SetPosition(glm::vec3(.935f, 0.175f, 0.f));
    car.AppendChild(&wheelsBack);

    wheel1.SetName("Wheel1");
    wheel1.SetMesh(scene.assets.GetMesh("wheel"));
    wheel1.SetMaterial(scene.assets.GetMaterial("red"));
    wheel1.SetPosition(glm::vec3(0.f, 0.f, -.5f));
    wheel1.SetScale(0.33f);
    wheel1.SetRotation(glm::vec3(-3.14159265f / 2.f, 0.f, -3.14159265f / 2.f));
    wheel1.RegisterCollision(&physics);
    wheelsFront.AppendChild(&wheel1);

    wheel2.SetName("Wheel2");
    wheel2.SetMesh(scene.assets.GetMesh("wheel"));
    wheel2.SetMaterial(scene.assets.GetMaterial("green"));
    wheel2.SetPosition(glm::vec3(0.f, 0.f, .5f));
    wheel2.SetScale(0.33f);
    wheel2.SetRotation(glm::vec3(-3.14159265f / 2.f, 0.f, 3.14159265f / 2.f));
    wheel2.RegisterCollision(&physics);
    wheelsFront.AppendChild(&wheel2);

    wheel3.SetName("Wheel3");
    wheel3.SetMesh(scene.assets.GetMesh("wheel"));
    wheel3.SetMaterial(scene.assets.GetMaterial("blue"));
    wheel3.SetPosition(glm::vec3(0.f, 0.f, -.5f));
    wheel3.SetScale(0.33f);
    wheel3.SetRotation(glm::vec3(-3.14159265f / 2.f, 0.f, -3.14159265f / 2.f));
    wheel3.RegisterCollision(&physics);
    wheelsBack.AppendChild(&wheel3);

    wheel4.SetName("Wheel4");
    wheel4.SetMesh(scene.assets.GetMesh("wheel"));
    wheel4.SetMaterial(scene.assets.GetMaterial("yellow"));
    wheel4.SetPosition(glm::vec3(0.f, 0.f, .55f));
    wheel4.SetScale(0.33f);
    wheel4.SetRotation(glm::vec3(-3.14159265f / 2.f, 0.f, 3.14159265f / 2.f));
    wheel4.RegisterCollision(&physics);
    wheelsBack.AppendChild(&wheel4);

    gizmo.Reparent(&root);
}

void LE3Editor::Update(float deltaTime)
{
    root.Update(deltaTime);
    physics.StepSimulation(deltaTime);

    // Update gizmo size
    float gizmoSize = 1.f + glm::length(camera.GetPosition()) * gGizmoScaleFactor;
    gizmo.SetScale(gizmoSize);
    gizmo.Reparent(&root);  

    // Handle editor modes
    switch (m_editorState.mode)
    {
    case LE3EditorModes::LE3EDITOR_IDLE:
        ModeIdle();
        break;
    case LE3EditorModes::LE3EDITOR_SELECT:
        ModeSelect();
        break;
    case LE3EditorModes::LE3EDITOR_CAMERA:
        ModeCamera(m_lastInput);
        break;
    case LE3EditorModes::LE3EDITOR_GIZMO_DRAG:
        ModeGizmoDrag(m_lastInput);
        break;
    case LE3EditorModes::LE3EDITOR_GIZMO_DRAG_RELEASE:
        ModeGizmoDragRelease();
        break;
    
    default:
        break;
    }
}

void LE3Editor::HandleInput(LE3EditorInput input)
{
    UpdateHoveredObject(input);
    UpdateEditorMode(m_editorState, input);

    m_lastInput = input;
}

void LE3Editor::Render(int width, int height)
{
    camera.SetAspectRatio((float)width / (float)height);
    for (const auto& [key, value] : scene.assets.m_shaders)
    {
        LE3Shader* shader = scene.assets.GetShader(key);
        shader->Use();
        shader ->Uniform("view", camera.GetViewMatrix());
        shader->Uniform("projection", camera.GetProjectionMatrix());
    }

    // Update also the gizmo shaders
    gizmo.GetGizmoShader()->Use();
    gizmo.GetGizmoShader()->Uniform("view", camera.GetViewMatrix());
    gizmo.GetGizmoShader()->Uniform("projection", camera.GetProjectionMatrix());

    root.Draw();
}

LE3Object* LE3Editor::GetRoot() const
{
    return (LE3Object*) &root;
}

LE3EditorGizmo* LE3Editor::GetGizmo() const
{
    return (LE3EditorGizmo*)&gizmo;
}

LE3Object* LE3Editor::GetHoveredObject() const
{
    return hoveredObject;
}

void LE3Editor::SetSelectCallback(LE3SelectCallback* callback)
{
    selectCallback = callback;
}

bool LE3Editor::UpdateHoveredGizmo(LE3EditorInput input)
{
    gizmo.UnhoverAxes();
    m_editorState.bHoversGizmo = false;
    if (gizmo.GetHidden())
        return false;

    LE3EditorGizmoAxis* axes[] = {
        gizmo.xAxis, gizmo.yAxis, gizmo.zAxis
    };
    glm::vec2 cursorScreen(input.relativeMouseX, input.relativeMouseY);
    glm::mat4 projView = camera.GetProjectionMatrix() * camera.GetViewMatrix();

    for (LE3EditorGizmoAxis* axis : axes)
    {
        if (axis->CheckIfHoveredByMouse(projView, cursorScreen))
        {
            hoveredObject = axis;
            m_editorState.bHoversGizmo = true;
            return true;
        }
    }
    return false;
}  

void LE3Editor::UpdateHoveredObject(LE3EditorInput input)
{
    if (this->UpdateHoveredGizmo(input))
        return;
    // Get pointed object
    glm::vec4 rayStartScreen(
        input.relativeMouseX,
        input.relativeMouseY,
        -1.f, 1.f
    );
    glm::vec4 rayEndScreen(
        input.relativeMouseX,
        input.relativeMouseY,
        0.f, 1.f
    );
    glm::mat4 inv = glm::inverse(camera.GetProjectionMatrix() * camera.GetViewMatrix());
    glm::vec4 rayStartWorld = inv * rayStartScreen; rayStartWorld /= rayStartWorld.w;
    glm::vec4 rayEndWorld = inv * rayEndScreen; rayEndWorld /= rayEndWorld.w;
    
    glm::vec3 rayDir = glm::normalize(glm::vec3(rayEndWorld - rayStartWorld));
    glm::vec3 rayOrigin = glm::vec3(rayStartWorld);
    glm::vec3 rayEndpoint = rayOrigin + rayDir * 1000.f;
    btCollisionWorld::ClosestRayResultCallback RayCallback(
        btVector3(rayOrigin.x, rayOrigin.y, rayOrigin.z),
        btVector3(rayEndpoint.x, rayEndpoint.y, rayEndpoint.z)
    );
    physics.GetWorld()->rayTest(
        btVector3(rayOrigin.x, rayOrigin.y, rayOrigin.z),
        btVector3(rayEndpoint.x, rayEndpoint.y, rayEndpoint.z),
        RayCallback
    );

    if (RayCallback.hasHit())
    {
        LE3Object* obj = (LE3Object*) RayCallback.m_collisionObject->getUserPointer();
        hoveredObject = obj;
    }
    else
    {
        hoveredObject = nullptr;
    }
}

void LE3Editor::ModeIdle()
{
    camera.SetMoveVelocityX(0.f);
    camera.SetMoveVelocityY(0.f);
    camera.SetMoveVelocityZ(0.f);
    camera.SetLookVelocityX(0.f);
    camera.SetLookVelocityY(0.f);

    m_draggedGizmoAxis = nullptr;
}
void LE3Editor::ModeSelect()
{
    selectCallback->callback();
    this->SetSelectedObject(hoveredObject);
}
void LE3Editor::ModeCamera(LE3EditorInput input)
{
    if (input.keyboard['W'])
        camera.SetMoveVelocityY(1.f);
    else if (input.keyboard['S'])
        camera.SetMoveVelocityY(-1.f);
    else
        camera.SetMoveVelocityY(0.f);

    if (input.keyboard['D'])
        camera.SetMoveVelocityX(1.f);
    else if (input.keyboard['A'])
        camera.SetMoveVelocityX(-1.f);
    else
        camera.SetMoveVelocityX(0.f);

    if (input.keyboard['E'])
        camera.SetMoveVelocityZ(1.f);
    else if (input.keyboard['Q'])
        camera.SetMoveVelocityZ(-1.f);
    else
        camera.SetMoveVelocityZ(0.f);

    camera.SetLookVelocityX((float)input.xrel);
    camera.SetLookVelocityY(-(float)input.yrel);
}

void LE3Editor::ModeGizmoDrag(LE3EditorInput input)
{
    if (!m_draggedGizmoAxis)
        m_draggedGizmoAxis = (LE3EditorGizmoAxis*)hoveredObject;
    
    m_draggedGizmoAxis->SetIsHovered(true);

    // Get axis delta screen coords
    glm::mat4 projView = camera.GetProjectionMatrix() * camera.GetViewMatrix();
    
    // NOTE: ignoring the gizmo rotation seems to yield better results
    // glm::vec3 pWorld = glm::vec3(gizmo.GetModelMatrix() * m_draggedGizmoAxis->GetModelMatrix() * glm::vec4(0.f, 0.f, 0.f, 0.f));
    // glm::vec3 qWorld = glm::vec3(gizmo.GetModelMatrix() * m_draggedGizmoAxis->GetModelMatrix() * glm::vec4(0.f, gGizmoAxisLength, 0.f, 0.f));
    glm::vec3 pWorld = glm::vec3(m_draggedGizmoAxis->GetModelMatrix() * glm::vec4(0.f, 0.f, 0.f, 0.f));
    glm::vec3 qWorld = glm::vec3(m_draggedGizmoAxis->GetModelMatrix() * glm::vec4(0.f, gGizmoAxisLength, 0.f, 0.f));
    glm::vec2 pScreen = WorldToScreen(projView, pWorld);
    glm::vec2 qScreen = WorldToScreen(projView, qWorld);

    float deltaX = input.relativeMouseX - m_editorState.dragInitialPos.x;
    float deltaY = input.relativeMouseY - m_editorState.dragInitialPos.y;

    float t = glm::dot(glm::vec2(deltaX, deltaY), qScreen - pScreen);
    glm::vec3 projection = t * m_draggedGizmoAxis->GetAxisLine();
    m_editorState.deltaPos = gGizmoDragSpeed * projection;

    m_selectedObject->SetPosition(m_editorState.selectedInitialPos + m_editorState.deltaPos);
    gizmo.SetPosition(m_selectedObject->GetGlobalPosition());
}

void LE3Editor::ModeGizmoDragRelease()
{
    m_editorState.bReleaseGizmoFinished = true;

    // If we re-drag the object, then at least update the new position
    this->SetSelectedObject(m_selectedObject);
}

void LE3Editor::SetSelectedObject(LE3Object* obj)
{
    m_selectedObject = obj;
    if (m_selectedObject)
    {
        m_editorState.selectedInitialPos = m_selectedObject->GetPosition();

        // Update gizmo
        gizmo.SetHidden(false);
        gizmo.SetPosition(m_selectedObject->GetGlobalPosition());
        glm::vec3 gizmoRotation(0.f);
        if (m_selectedObject->GetParent())
            gizmoRotation = m_selectedObject->GetParent()->GetGlobalRotation();
        gizmo.SetRotation(gizmoRotation);
    }
    else
    {
        gizmo.SetHidden(true);
    }
}