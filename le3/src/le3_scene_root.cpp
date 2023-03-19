#include "le3_scene_root.h"

LE3SceneRoot::LE3SceneRoot() : LE3Object("Root")
{

}

void LE3SceneRoot::UpdateRecurse(double deltaTime, LE3Object* object)
{
    for (auto child : object->GetChildren())   
    {
        if (!child)
            continue;
        child->Update(deltaTime);
        UpdateRecurse(deltaTime, child);
    }
}

void LE3SceneRoot::DrawRecurse(LE3Object* object)
{
    if (object->GetHidden())
        return;

    for (auto child : object->GetChildren())   
    {
        if (!child)
            continue;
        child->Draw();
        DrawRecurse(child);
    }
}
void LE3SceneRoot::DrawRecurse(LE3Object* object, LE3Shader* shader)
{
    if (object->GetHidden())
        return;

    for (auto child : object->GetChildren())   
    {
        if (!child)
            continue;
        child->Draw(shader);
        DrawRecurse(child, shader);
    }
}

void LE3SceneRoot::Update(double deltaTime)
{
    UpdateRecurse(deltaTime, this);
}
void LE3SceneRoot::Draw()
{
    DrawRecurse(this);
}
void LE3SceneRoot::Draw(LE3Shader* shader)
{
    DrawRecurse(this, shader);
}