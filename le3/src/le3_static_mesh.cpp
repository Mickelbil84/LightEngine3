#include "le3_static_mesh.h"
#include "le3_visual_debug.h"

LE3StaticMesh::LE3StaticMesh(std::string name, glm::vec3 position, glm::vec3 rotation, float scale) :
    LE3Object(name, position, rotation, scale),
    m_pRigidBody(nullptr)
{

}

void LE3StaticMesh::Update(double deltaTime)
{
    LE3Object::Update(deltaTime);

    if (m_pRigidBody)
    {
        btTransform transform;
        transform.setFromOpenGLMatrix(glm::value_ptr(GetModelMatrix() * glm::scale(glm::vec3(1/m_scale))));
        m_pRigidBody->setCenterOfMassTransform(transform);
    }
}
void LE3StaticMesh::Draw()
{
    if (!m_material->GetShader())
        return;
    m_material->Apply(m_globalModelMatrix);
    m_mesh->Draw();

    if (m_pRigidBody)
    {
        glm::vec3 lowerBound = m_mesh->GetBoxCollision().lowerBound;
        glm::vec3 upperBound = m_mesh->GetBoxCollision().upperBound;

        glm::vec3 relative_position = 0.5f * (upperBound + lowerBound);
        glm::vec3 extent = upperBound - lowerBound;
        
        if (m_bSelected)
        {
            LE3VisualDebug::DrawDebugCube(
                GetModelMatrix() * glm::translate(relative_position) * glm::scale(extent),
                glm::vec3(1.f, 1.f, 1.f)
            );
        }
        else if (LE3VisualDebug::g_bDrawCollision)
        {
            LE3VisualDebug::DrawDebugCube(
                GetModelMatrix() * glm::translate(relative_position) * glm::scale(extent),
                glm::vec3(0.f, 1.f, 0.f)
            );
        }

        if (LE3VisualDebug::g_bDrawBulletCollision)
        {
            // Draw bullet AABB
            btVector3 aabbMin, aabbMax;
            m_pRigidBody->getAabb(aabbMin, aabbMax);
            btVector3 bulletExtent = aabbMax - aabbMin;
            btVector3 bulletPosition = 0.5f * (aabbMin + aabbMax);
            LE3VisualDebug::DrawDebugCube(
                glm::vec3(bulletPosition.x(), bulletPosition.y(), bulletPosition.z()),
                glm::vec3(),
                glm::vec3(bulletExtent.x(), bulletExtent.y(), bulletExtent.z()),
                glm::vec3(1.f, 1.f, 0.f)
            );
        }

    }
}

void LE3StaticMesh::SetMesh(LE3Mesh<LE3Vertex>* mesh)
{
    m_mesh = mesh;    
}
void LE3StaticMesh::SetMaterial(LE3Material* material)
{
    m_material = material;
}

void LE3StaticMesh::RegisterCollision(LE3PhysicsComponent* physics)
{
    btTransform transform;
    transform.setFromOpenGLMatrix(glm::value_ptr(GetModelMatrix()));
    btDefaultMotionState* motionstate = new btDefaultMotionState(transform);

    btCollisionShape* boxCollisionShape = m_mesh->GetBoxCollision().ToBullet();
    boxCollisionShape->setLocalScaling(btVector3(m_scale, m_scale, m_scale));
    btRigidBody::btRigidBodyConstructionInfo rigidBodyCI(
        0, // zero mass
        motionstate,
        boxCollisionShape,
        btVector3(0,0,0)
    );
    m_pRigidBody = new btRigidBody(rigidBodyCI);
    m_pRigidBody->setUserPointer((void*)this);
    physics->GetWorld()->addRigidBody(m_pRigidBody);
    m_bHasCollision = true;
}

void LE3StaticMesh::UpdateAssets(LE3AssetManager& assets)
{
    SetMesh(assets.GetMesh(meshName));
    SetMaterial(assets.GetMaterial(materialName));
}

void LE3StaticMesh::UpdatePhysics(LE3PhysicsComponent& physics)
{
    RegisterCollision(&physics);
}