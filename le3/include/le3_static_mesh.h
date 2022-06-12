#pragma once

#include "le3_mesh.h"
#include "le3_material.h"
#include "le3_object.h"

class LE3StaticMesh : public LE3Object
{
public:
    virtual void Update(double deltaTime);
    virtual void Draw();

    void SetMesh(LE3Mesh<LE3Vertex>* mesh);
    void SetMaterial(LE3Material* material);
protected:
    LE3Mesh<LE3Vertex>* m_mesh;
    LE3Material* m_material;
};