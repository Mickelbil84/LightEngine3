#include "le3_scene_root.h"

LE3SceneRoot::LE3SceneRoot() : LE3Object("Root")
{

}

void LE3SceneRoot::UpdateRecurse(double deltaTime, LE3Object* object)
{
    for (auto child : object->GetChildren())   
    {
        child->Update(deltaTime);
        UpdateRecurse(deltaTime, child);
    }
}

void LE3SceneRoot::DrawRecurse(LE3Object* object)
{
    for (auto child : object->GetChildren())   
    {
        child->Draw();
        DrawRecurse(child);
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