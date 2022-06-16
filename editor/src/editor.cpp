#include "editor.h"
#include "wx/wx.h"

#ifndef __APPLE__
const std::string resource_prefix = std::string("../../");
#else
const std::string resource_prefix = std::string("../");
#endif

void LE3Editor::Init()
{
    // ---------------------------
    //   Load Assets
    // ---------------------------
    scene.assets.LoadShader("basic", 
        resource_prefix + "resources/shaders/basic/basic.vs", 
        resource_prefix + "resources/shaders/basic/basic.fs");
    scene.assets.AddMeshPath("car", resource_prefix + "resources/models/cars/Audi R8.fbx");
    scene.assets.CreateMaterial("car", "basic");

    // ---------------------------
    //   Create game objects
    // ---------------------------
    camera.SetPosition(glm::vec3(0.f, 0.5f, 5.f));
    root.AppendChild(&camera);

    car.SetPosition(glm::vec3(0.f, 0.f, 2.f));
    car.SetMesh(scene.assets.GetMesh("car"));
    car.SetMaterial(scene.assets.GetMaterial("car"));
    car.SetScale(0.3f);
    car.SetRotation(glm::vec3(-3.14159265f / 2.f, 0.f, -3.14159265f / 2.f));
    root.AppendChild(&car);
}

void LE3Editor::Update(float deltaTime)
{
    root.Update(deltaTime);
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
    LE3Shader* shader = scene.assets.GetShader("basic");

    if (shader)
    {
        shader ->Use();
        shader ->Uniform("view", camera.GetViewMatrix());
        shader->Uniform("projection", camera.GetProjectionMatrix((float)width / (float)height));
        root.Draw();
    }
}
