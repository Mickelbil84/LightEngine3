#pragma once

#include "le3_object.h"

class LE3SceneRoot : public LE3Object
{
public:
    LE3SceneRoot();
    virtual void Update(double deltaTime);
    virtual void Draw();

private:
    void UpdateRecurse(double deltaTime, LE3Object* object);
    void DrawRecurse(LE3Object* object);
};