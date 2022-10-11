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

void LE3StaticMesh::RegisterCollision(LE3PhysicsComponent* physics)
{
    btQuaternion bulletRotation;
    std::cout << m_rotation[0] << " " << m_rotation[1] << " " << m_rotation[2] << std::endl;
    bulletRotation.setEuler(m_rotation[1], m_rotation[0], m_rotation[2]);
    btDefaultMotionState* motionstate = new btDefaultMotionState(btTransform(
        bulletRotation, 
        btVector3(m_position[0], m_position[1], m_position[2])
    ));

    btCollisionShape* boxCollisionShape = m_mesh->GetBoxCollision().ToBullet();
    // boxCollisionShape->setLocalScaling(btVector3(m_scale, m_scale, m_scale));
    btRigidBody::btRigidBodyConstructionInfo rigidBodyCI(
        0, // zero mass
        motionstate,
        boxCollisionShape,
        btVector3(0,0,0)
    );
    m_pRigidBody = new btRigidBody(rigidBodyCI);
    m_pRigidBody->setUserPointer((void*)this);
    physics->GetWorld()->addRigidBody(m_pRigidBody);
}
