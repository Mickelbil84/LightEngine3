#include "le3_skeletal_mesh.h"
#include "le3_visual_debug.h"
#include "le3_print.h"

#include <fmt/core.h>
using fmt::format;

LE3SkeletalMesh::LE3SkeletalMesh(std::string name, glm::vec3 position, glm::vec3 rotation, float scale) :
    LE3Object(name, position, rotation, scale),
    m_pRigidBody(nullptr)
{

}

void LE3SkeletalMesh::Update(double deltaTime)
{
    LE3Object::Update(deltaTime);

    m_animationTime += deltaTime;

    float ticksPerSecond = 25.f;
    if (m_mesh->m_animationTracks[0].ticksPerSecond)
        ticksPerSecond = (float)m_mesh->m_animationTracks[0].ticksPerSecond;

    float adjustedAnimationTime = fmodf(m_animationTime * ticksPerSecond, m_mesh->m_animationTracks[0].duration);
    m_mesh->m_animationTracks[0].UpdateBoneMatrices(adjustedAnimationTime);

    if (m_pRigidBody)
    {
        btTransform transform;
        transform.setFromOpenGLMatrix(glm::value_ptr(GetModelMatrix() * glm::scale(glm::vec3(1/m_scale))));
        m_pRigidBody->setCenterOfMassTransform(transform);
    }
}
void LE3SkeletalMesh::Draw(LE3Shader* shader)
{
    if (!shader)
        return;
    shader->Use();
    shader->Uniform("model", m_globalModelMatrix);
    // Update animation
    std::vector<glm::mat4> boneMatrices = m_mesh->m_animationTracks[0].GetBoneMatrices();
    for (int idx = 0; idx < boneMatrices.size(); idx++)
        shader->Uniform(format("boneMatrices[{}]", idx), boneMatrices[idx]);
    shader->Uniform("bIsSkeletal", (GLuint)true);
    m_mesh->Draw();
    shader->Uniform("bIsSkeletal", (GLuint)false);
}
void LE3SkeletalMesh::Draw()
{
    if (!m_material->GetShader())
        return;
    m_material->Apply();
    m_material->GetShader()->Use();
    m_material->GetShader()->Uniform("model", m_globalModelMatrix);
    
    // Update animation
    std::vector<glm::mat4> boneMatrices = m_mesh->m_animationTracks[0].GetBoneMatrices();
    for (int idx = 0; idx < boneMatrices.size(); idx++)
        m_material->GetShader()->Uniform(format("boneMatrices[{}]", idx), boneMatrices[idx]);
    m_material->GetShader()->Uniform("bIsSkeletal", (GLuint)true);
    m_mesh->Draw();
    m_material->GetShader()->Uniform("bIsSkeletal", (GLuint)false);

    int i = 0;

    // glm::mat4 mixamoArmature = glm::rotate(glm::radians(180.f), glm::vec3(1.f, 0.f, 0.f));
    glm::mat4 mixamoArmature = glm::rotate(glm::radians(0.f), glm::vec3(1.f, 0.f, 0.f));
    // mixamoArmature = mixamoArmature * glm::scale(glm::vec3(0.1f));
    // glm::mat4 mixamoArmature = glm::identity<glm::mat4>();

    glClear(GL_DEPTH_BUFFER_BIT);
    for (auto bone : m_mesh->m_skeleton.m_bones)
    {
        // glm::mat4 model_bone = GetModelMatrix() * mixamoArmature * m_mesh->m_skeleton.m_globalInverseTransform *  bone->GetTransform();
        glm::mat4 model_bone = GetModelMatrix() * glm::inverse(bone->GetTransform()) * glm::inverse(bone->offset);
        glm::vec3 pos(model_bone[3]);
        // LE3VisualDebug::DrawDebugCube(pos, glm::vec3(0.f), glm::vec3(0.01f, .01f, 0.01f), glm::vec3(0.f, 1.f, 0.f));
        if (bone->parent)
        {   
            glm::mat4 parent_model_bone = GetModelMatrix() * glm::inverse(bone->parent->offset) * bone->parent->GetTransform();
            glm::vec3 parent_pos(parent_model_bone[3]);
            // LE3VisualDebug::DrawDebugLine(parent_pos, pos, glm::vec3(0.f, 1.f, 0.f));
        }
    }
    
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

void LE3SkeletalMesh::SetMesh(LE3Mesh<LE3VertexSkeletal>* mesh)
{
    m_mesh = mesh;    
}
void LE3SkeletalMesh::SetMaterial(LE3Material* material)
{
    m_material = material;
}

void LE3SkeletalMesh::RegisterCollision(LE3PhysicsComponent* physics)
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
    m_pPhysics = physics;
    m_pPhysics->GetWorld()->addRigidBody(m_pRigidBody);
    m_bHasCollision = true;
}

void LE3SkeletalMesh::UpdateAssets(LE3AssetManager& assets)
{
    SetMesh(assets.GetSkeletalMesh(meshName));
    SetMaterial(assets.GetMaterial(materialName));
}

void LE3SkeletalMesh::UpdatePhysics(LE3PhysicsComponent& physics)
{
    RegisterCollision(&physics);
}

std::shared_ptr<LE3Object> LE3SkeletalMesh::Duplicate(std::string newName)
{
    std::shared_ptr<LE3SkeletalMesh> newObj(new LE3SkeletalMesh());
    newObj->SetName(newName);
    newObj->CopyDataFromOther((LE3Object*)this);
    newObj->meshName = meshName;
    newObj->materialName = materialName;
    newObj->m_bHasCollision = m_bHasCollision;
    return std::dynamic_pointer_cast<LE3Object>(newObj);
}

void LE3SkeletalMesh::Delete()
{
    if (m_pRigidBody)
        m_pPhysics->GetWorld()->removeRigidBody(m_pRigidBody);
}