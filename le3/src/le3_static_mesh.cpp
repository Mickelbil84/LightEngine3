#include "le3_static_mesh.h"

void LE3StaticMesh::Update(double deltaTime)
{
    LE3Object::Update(deltaTime);
}
void LE3StaticMesh::Draw()
{
    m_material->Apply(m_globalModelMatrix);
    m_mesh->Draw();
}

void LE3StaticMesh::SetMesh(LE3Mesh<LE3Vertex>* mesh)
{
    m_mesh = mesh;
}
void LE3StaticMesh::SetMaterial(LE3Material* material)
{
    m_material = material;
}
