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
    refreshPropertiesCallback(nullptr),
    m_selectedObject(nullptr),
    m_draggedGizmoAxis(nullptr),
    bClickUp(true),
    scenePath(""),
    bPauseEngine(false),
    bPauseUpdate(false)
{

}

void LE3Editor::Init()
{
    this->scene.Init();

    // ------------------------
    // Setup Gizmo and Camera
    // ------------------------
    gizmo.Init();
    gizmo.SetHiddenInSceneGraph(true);
    gizmo.SetHidden(true);
    scene.GetRoot()->AppendChild(&gizmo);

    scene.AddFreeCamera(glm::vec3(0.f, 0.5f, 5.f));

    LE3VisualDebug::Init(scene.GetCamera().get());

    // gizmo.Reparent(&root);

    // LoadScene(scene, "scene.json");
    
}

void LE3Editor::Update(float deltaTime)
{
    if (bPauseEngine || bPauseUpdate)
        return;
    scene.GetRoot()->Update(deltaTime);
    scene.GetPhysics()->StepSimulation(deltaTime);

    // Update gizmo size
    float gizmoSize = 1.f + glm::length(scene.GetCamera()->GetPosition()) * gGizmoScaleFactor;
    gizmo.SetScale(gizmoSize);
    gizmo.Reparent(scene.GetRoot().get());  

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
    if (bPauseEngine || bPauseUpdate)
        return;
    UpdateHoveredObject(input);
    UpdateEditorMode(m_editorState, input);

    m_lastInput = input;
}

void LE3Editor::Render(int width, int height)
{
    if (bPauseEngine)
        return;
    scene.GetCamera()->SetAspectRatio((float)width / (float)height);
    for (const auto& [key, value] : scene.assets.m_shaders)
    {
        LE3Shader* shader = scene.assets.GetShader(key);
        shader->Use();
        shader ->Uniform("view", scene.GetCamera()->GetViewMatrix());
        shader->Uniform("projection", scene.GetCamera()->GetProjectionMatrix());
        scene.lightManager.RenderLights(shader);
    }

    // Update also the gizmo shaders
    gizmo.GetGizmoShader()->Use();
    gizmo.GetGizmoShader()->Uniform("view", scene.GetCamera()->GetViewMatrix());
    gizmo.GetGizmoShader()->Uniform("projection", scene.GetCamera()->GetProjectionMatrix());

    scene.GetRoot()->Draw();
}


LE3EditorGizmo* LE3Editor::GetGizmo() const
{
    return (LE3EditorGizmo*)&gizmo;
}

LE3Object* LE3Editor::GetHoveredObject() const
{
    return hoveredObject;
}

LE3Object* LE3Editor::GetSelectedObject() const
{
    return m_selectedObject;
}

void LE3Editor::SetSelectCallback(LE3SelectCallback* callback)
{
    selectCallback = callback;
}

void LE3Editor::SetRefreshPropertiesCallback(LE3RefreshPropertiesCallback* callback)
{
    refreshPropertiesCallback = callback;
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
    glm::mat4 projView = scene.GetCamera()->GetProjectionMatrix() * scene.GetCamera()->GetViewMatrix();

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
    glm::mat4 inv = glm::inverse(scene.GetCamera()->GetProjectionMatrix() * scene.GetCamera()->GetViewMatrix());
    glm::vec4 rayStartWorld = inv * rayStartScreen; rayStartWorld /= rayStartWorld.w;
    glm::vec4 rayEndWorld = inv * rayEndScreen; rayEndWorld /= rayEndWorld.w;
    
    glm::vec3 rayDir = glm::normalize(glm::vec3(rayEndWorld - rayStartWorld));
    glm::vec3 rayOrigin = glm::vec3(rayStartWorld);
    glm::vec3 rayEndpoint = rayOrigin + rayDir * 1000.f;
    btCollisionWorld::ClosestRayResultCallback RayCallback(
        btVector3(rayOrigin.x, rayOrigin.y, rayOrigin.z),
        btVector3(rayEndpoint.x, rayEndpoint.y, rayEndpoint.z)
    );
    scene.GetPhysics()->GetWorld()->rayTest(
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
    std::shared_ptr<LE3FreeCamera> freeCamera = std::static_pointer_cast<LE3FreeCamera>(scene.GetCamera());
    freeCamera->SetMoveVelocityX(0.f);
    freeCamera->SetMoveVelocityY(0.f);
    freeCamera->SetMoveVelocityZ(0.f);
    freeCamera->SetLookVelocityX(0.f);
    freeCamera->SetLookVelocityY(0.f);

    m_draggedGizmoAxis = nullptr;
}
void LE3Editor::ModeSelect()
{
    if (selectCallback)
        selectCallback->callback();
    this->SetSelectedObject(hoveredObject);
    if (refreshPropertiesCallback)
        refreshPropertiesCallback->callback();
}
void LE3Editor::ModeCamera(LE3EditorInput input)
{
    std::shared_ptr<LE3FreeCamera> freeCamera = std::static_pointer_cast<LE3FreeCamera>(scene.GetCamera());
    if (input.keyboard['W'])
        freeCamera->SetMoveVelocityY(1.f);
    else if (input.keyboard['S'])
        freeCamera->SetMoveVelocityY(-1.f);
    else
        freeCamera->SetMoveVelocityY(0.f);

    if (input.keyboard['D'])
        freeCamera->SetMoveVelocityX(1.f);
    else if (input.keyboard['A'])
        freeCamera->SetMoveVelocityX(-1.f);
    else
        freeCamera->SetMoveVelocityX(0.f);

    if (input.keyboard['E'])
        freeCamera->SetMoveVelocityZ(1.f);
    else if (input.keyboard['Q'])
        freeCamera->SetMoveVelocityZ(-1.f);
    else
        freeCamera->SetMoveVelocityZ(0.f);

    freeCamera->SetLookVelocityX((float)input.xrel);
    freeCamera->SetLookVelocityY(-(float)input.yrel);
}

void LE3Editor::ModeGizmoDrag(LE3EditorInput input)
{
    if (!m_draggedGizmoAxis)
        m_draggedGizmoAxis = (LE3EditorGizmoAxis*)hoveredObject;
    
    m_draggedGizmoAxis->SetIsHovered(true);

    // Get axis delta screen coords
    glm::mat4 projView = scene.GetCamera()->GetProjectionMatrix() * scene.GetCamera()->GetViewMatrix();
    
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

    if (refreshPropertiesCallback)
        refreshPropertiesCallback->callback();
}

void LE3Editor::ModeGizmoDragRelease()
{
    m_editorState.bReleaseGizmoFinished = true;

    // If we re-drag the object, then at least update the new position
    this->SetSelectedObject(m_selectedObject);
}

void LE3Editor::SetSelectedObject(LE3Object* obj)
{
    // Update last object
    if (m_selectedObject)
        m_selectedObject->SetSelected(false);

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
        m_selectedObject->SetSelected(true);
    }
    else
    {
        gizmo.SetHidden(true);
    }
}