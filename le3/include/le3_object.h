#pragma once

#include <string>
#include <vector>
#include <memory>

#include <cereal/cereal.hpp>
#include <cereal/types/polymorphic.hpp>
#include <cereal/archives/binary.hpp>
#include <cereal/archives/xml.hpp>
#include <cereal/archives/json.hpp>

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/matrix_decompose.hpp>

#include "le3_physics.h"
#include "le3_asset_manager.h"

// The most basic entity in the framework. Each element in the scene is an object.
// An object has a local transform (which is in relation to its parent).
// Since each object has pointers to its parent and children, they implicitly
// form a scene graph.
class LE3Object
{
public:
    LE3Object(std::string name = "", glm::vec3 position = glm::vec3(0.f), glm::vec3 rotation = glm::vec3(0.f), float scale = 1.f);

    virtual void Update(double deltaTime);
    virtual void Draw();

    glm::mat4 GetModelMatrix() const;

    // Moves itself from the current parent to a new one
    void Reparent(LE3Object* parent);
    // Appends new child
    void AppendChild(LE3Object* child);
    // Removes an existing child
    void RemoveChild(LE3Object* child);
    std::vector<LE3Object*> GetChildren() const;
    LE3Object* GetParent() const;

    void AddRotationX(float rot);
    void AddRotationY(float rot);
    void AddRotationZ(float rot);
    void SetPosition(glm::vec3 position);
    void SetPositionX(float x);
    void SetPositionY(float y);
    void SetPositionZ(float z);
    void SetRotation(glm::vec3 rotation);
    void SetRotationX(float x);
    void SetRotationY(float y);
    void SetRotationZ(float z);
    void SetScale(float scale);
    glm::vec3 GetPosition() const;
    glm::vec3 GetRotation() const;
    float GetScale() const;
    void SetName(std::string name);
    std::string GetName() const;
    void SetHiddenInSceneGraph(bool hidden);
    bool GetHiddenInSceneGraph() const;
    void SetHidden(bool hidden);
    bool GetHidden() const;
    void SetSelected(bool selected);
    bool GetSelected() const;

    glm::vec3 GetGlobalPosition() const;
    glm::vec3 GetGlobalRotation() const;

    virtual void UpdateAssets(LE3AssetManager& assets);
    virtual void UpdatePhysics(LE3PhysicsComponent& physics);

    template <class Archive>
    void serialize( Archive & ar )
    {
        ar(CEREAL_NVP(m_position), CEREAL_NVP(m_rotation), CEREAL_NVP(m_scale));
        ar(CEREAL_NVP(m_globalPosition), CEREAL_NVP(m_globalRotation));
        ar(CEREAL_NVP(m_localModelMatrix), CEREAL_NVP(m_globalModelMatrix));
        ar(CEREAL_NVP(m_name), CEREAL_NVP(m_bHiddenInSceneGraph), CEREAL_NVP(m_bHidden));

    }

protected:
    
    /////////////////////
    // Transform vectors
    /////////////////////
    
    glm::vec3 m_position;
    glm::vec3 m_rotation;
    float m_scale;

    glm::vec3 m_globalPosition;
    glm::vec3 m_globalRotation;

    //////////////////
    // Model Matrices
    //////////////////

    glm::mat4 m_localModelMatrix, m_globalModelMatrix;

    ///////////////
    // Scene Graph
    ///////////////

    LE3Object* m_pParent;
    std::vector<LE3Object*> m_children;
    std::string m_name;
    bool m_bHiddenInSceneGraph;
    bool m_bHidden;
    bool m_bSelected; // Used to draw debug outline

protected:
    // Updates the local model matrix of the object (based on the transform vectors)
    virtual void UpdateLocalModelMatrix();
    // Updates the global model matrix, with respect to the parent object
    virtual void UpdateGlobalModelMatrix();
};

CEREAL_REGISTER_TYPE(LE3Object);