#include "editor.h"
#include "wx/wx.h"

#ifndef __APPLE__
const std::string resource_prefix = std::string("../../");
#else
const std::string resource_prefix = std::string("../");
#endif

void LE3Editor::Init()
{
    // // ---------------------------
    // //   Load Assets
    // // ---------------------------
    // scene.assets.LoadShader("basic", 
    //     resource_prefix + "resources/shaders/basic/basic.vs", 
    //     resource_prefix + "resources/shaders/basic/basic.fs");
    // scene.assets.AddMeshPath("car", resource_prefix + "resources/models/cars/Audi R8.fbx");
    // scene.assets.CreateMaterial("car", "basic");

    // // ---------------------------
    // //   Create game objects
    // // ---------------------------
    // camera.SetPosition(glm::vec3(0.f, 0.5f, 5.f));
    // root.AppendChild(&camera);

    // car.SetPosition(glm::vec3(0.f, 0.f, 2.f));
    // car.SetName("Car");
    // car.SetMesh(scene.assets.GetMesh("car"));
    // car.SetMaterial(scene.assets.GetMaterial("car"));
    // car.SetScale(0.3f);
    // car.SetRotation(glm::vec3(-3.14159265f / 2.f, 0.f, -3.14159265f / 2.f));
    // root.AppendChild(&car);

    // ---------------------------
    //   Load Assets
    // ---------------------------
    scene.assets.LoadShader("gizmo",
        resource_prefix + "resources/shaders/editor/gizmo.vs", 
        resource_prefix + "resources/shaders/editor/gizmo.fs");

    scene.assets.CreateMaterial("gizmoX", "gizmo");
    scene.assets.GetMaterial("gizmoX")->diffuseColor = glm::vec4(1.f, 0.f, 0.f, 1.f);
    scene.assets.CreateMaterial("gizmoY", "gizmo");
    scene.assets.GetMaterial("gizmoY")->diffuseColor = glm::vec4(0.f, 1.f, 0.f, 1.f);
    scene.assets.CreateMaterial("gizmoZ", "gizmo");
    scene.assets.GetMaterial("gizmoZ")->diffuseColor = glm::vec4(0.f, 0.f, 1.f, 1.f);

    scene.assets.LoadShader("basic", 
        resource_prefix + "resources/shaders/moving_car/moving_car.vs", 
        resource_prefix + "resources/shaders/moving_car/moving_car.fs");

    std::vector<LE3Vertex> box;
    AddBox(box, 0.f, 0.f, 0.f, .5f, .5f, .3f);
    scene.assets.LoadMesh("wheel", resource_prefix + "resources/models/cars/Audi R8 Wheel.fbx");
    scene.assets.LoadMesh("carBody", resource_prefix + "resources/models/cars/Audi R8 Body.fbx");

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
    scene.assets.GetMaterial("carBody")->diffuseTexture = scene.assets.GetTexture("wood");
    scene.assets.GetMaterial("carBody")->bUseDiffuseTexture = false;
    
    // ---------------------s------
    //   Create game objects
    // ---------------------------
    gizmo.Init(
        scene.assets.GetMaterial("gizmoX"),
        scene.assets.GetMaterial("gizmoY"),
        scene.assets.GetMaterial("gizmoZ"));
    gizmo.SetHiddenInSceneGraph(true);
    gizmo.SetHidden(true);
    root.AppendChild(&gizmo);

    camera.SetPosition(glm::vec3(0.f, 0.5f, 5.f));
    camera.SetHiddenInSceneGraph(true);
    root.AppendChild(&camera);

    car.SetName("Car");
    // car.SetPosition(glm::vec3(0.f, 0.f, -5.f));
    root.AppendChild(&car);

    carBodyMesh.SetName("CarBodyMesh");
    carBodyMesh.SetMesh(scene.assets.GetMesh("carBody"));
    carBodyMesh.SetMaterial(scene.assets.GetMaterial("carBody"));
    carBodyMesh.SetScale(0.3f);
    carBodyMesh.SetRotation(glm::vec3(-3.14159265f / 2.f, 0.f, -3.14159265f / 2.f));
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
    wheelsFront.AppendChild(&wheel1);

    wheel2.SetName("Wheel2");
    wheel2.SetMesh(scene.assets.GetMesh("wheel"));
    wheel2.SetMaterial(scene.assets.GetMaterial("green"));
    wheel2.SetPosition(glm::vec3(0.f, 0.f, .5f));
    wheel2.SetScale(0.33f);
    wheel2.SetRotation(glm::vec3(-3.14159265f / 2.f, 0.f, 3.14159265f / 2.f));
    wheelsFront.AppendChild(&wheel2);

    wheel3.SetName("Wheel3");
    wheel3.SetMesh(scene.assets.GetMesh("wheel"));
    wheel3.SetMaterial(scene.assets.GetMaterial("blue"));
    wheel3.SetPosition(glm::vec3(0.f, 0.f, -.5f));
    wheel3.SetScale(0.33f);
    wheel3.SetRotation(glm::vec3(-3.14159265f / 2.f, 0.f, -3.14159265f / 2.f));
    wheelsBack.AppendChild(&wheel3);

    wheel4.SetName("Wheel4");
    wheel4.SetMesh(scene.assets.GetMesh("wheel"));
    wheel4.SetMaterial(scene.assets.GetMaterial("yellow"));
    wheel4.SetPosition(glm::vec3(0.f, 0.f, .55f));
    wheel4.SetScale(0.33f);
    wheel4.SetRotation(glm::vec3(-3.14159265f / 2.f, 0.f, 3.14159265f / 2.f));
    wheelsBack.AppendChild(&wheel4);

    gizmo.Reparent(&root);
}

void LE3Editor::Update(float deltaTime)
{
    root.Update(deltaTime);

    // Update gizmo size
    float gizmoSize = 1.f + glm::length(camera.GetPosition()) * gGizmoScaleFactor;
    gizmo.SetScale(gizmoSize);
    gizmo.Reparent(&root);
    
}

void LE3Editor::HandleInput(LE3EditorInput input)
{
    if (!input.bLeftMouse)
    {
        camera.SetMoveVelocityX(0.f);
        camera.SetMoveVelocityY(0.f);
        camera.SetMoveVelocityZ(0.f);
        camera.SetLookVelocityX(0.f);
        camera.SetLookVelocityY(0.f);
        return;
    }
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

void LE3Editor::Render(int width, int height)
{
    for (const auto& [key, value] : scene.assets.m_shaders)
    {
        LE3Shader* shader = scene.assets.GetShader(key);
        shader->Use();
        shader ->Uniform("view", camera.GetViewMatrix());
        shader->Uniform("projection", camera.GetProjectionMatrix((float)width / (float)height));
    }

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