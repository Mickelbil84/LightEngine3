#pragma once

#include <cereal/cereal.hpp>

#include "le3_mesh.h"
#include "le3_material.h"
#include "le3_object.h"
#include "le3_physics.h"

class LE3StaticMesh : public LE3Object
{
public:
    LE3StaticMesh(std::string name = "", glm::vec3 position = glm::vec3(0.f), glm::vec3 rotation = glm::vec3(0.f), float scale = 1.f);

    virtual void Update(double deltaTime);
    virtual void Draw();

    void SetMesh(LE3Mesh<LE3Vertex>* mesh);
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
    LE3Mesh<LE3Vertex>* m_mesh;
    LE3Material* m_material;
    btRigidBody* m_pRigidBody;
    bool m_bHasCollision;
};

CEREAL_REGISTER_TYPE(LE3StaticMesh);
CEREAL_REGISTER_POLYMORPHIC_RELATION(LE3Object, LE3StaticMesh);