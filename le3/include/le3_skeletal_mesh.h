#pragma once

#include <cereal/cereal.hpp>

#include "le3_mesh.h"
#include "le3_animation.h"
#include "le3_material.h"
#include "le3_object.h"
#include "le3_physics.h"

class LE3SkeletalMesh : public LE3Object
{
public:
    LE3SkeletalMesh(std::string name = "", glm::vec3 position = glm::vec3(0.f), glm::vec3 rotation = glm::vec3(0.f), float scale = 1.f);

    virtual void Update(double deltaTime);
    virtual void Draw();
    virtual void Draw(LE3Shader* shader);

    virtual std::shared_ptr<LE3Object> Duplicate(std::string newName);
    virtual void Delete();

    void SetMesh(LE3Mesh<LE3VertexSkeletal>* mesh);
    void SetMaterial(LE3Material* material);
    void RegisterCollision(LE3PhysicsComponent* physics);

    virtual void UpdateAssets(LE3AssetManager& assets);
    virtual void UpdatePhysics(LE3PhysicsComponent& physics);

    std::string meshName, materialName;

    template <typename Archive>
    void serialize( Archive & ar )
    {
        LE3Object::serialize(ar);
        ar(CEREAL_NVP(meshName), CEREAL_NVP(materialName), CEREAL_NVP(m_bHasCollision));
    }

protected:
    LE3Mesh<LE3VertexSkeletal>* m_mesh;
    LE3Material* m_material;
    btRigidBody* m_pRigidBody;
    LE3PhysicsComponent* m_pPhysics;
    float m_animationTime = 0.f;
public:
    bool m_bHasCollision;
};

CEREAL_REGISTER_TYPE(LE3SkeletalMesh);
CEREAL_REGISTER_POLYMORPHIC_RELATION(LE3Object, LE3SkeletalMesh);