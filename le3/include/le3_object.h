#pragma once

#include <vector>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/euler_angles.hpp>

// The most basic entity in the framework. Each element in the scene is an object.
// An object has a local transform (which is in relation to its parent).
// Since each object has pointers to its parent and children, they implicitly
// form a scene graph.
class LE3Object
{
public:
    LE3Object(glm::vec3 position = glm::vec3(0.f), glm::vec3 rotation = glm::vec3(0.f), float scale = 1.f);

    virtual void Update(double deltaTime);

    glm::mat4 GetModelMatrix() const;

    // Moves itself from the current parent to a new one
    void Reparent(LE3Object* parent);
    // Appends new child
    void AppendChild(LE3Object* child);
    // Removes an existing child
    void RemoveChild(LE3Object* child);

    void AddRotationX(float rot);
    void AddRotationY(float rot);
    void AddRotationZ(float rot);
    void SetPosition(glm::vec3 position);
    void SetRotation(glm::vec3 rotation);
    void SetScale(float scale);
    glm::vec3 GetPosition() const;
    glm::vec3 GetRotation() const;
    float GetScale() const;

protected:
    
    /////////////////////
    // Transform vectors
    /////////////////////
    
    glm::vec3 m_position;
    glm::vec3 m_rotation;
    float m_scale;

    //////////////////
    // Model Matrices
    //////////////////

    glm::mat4 m_localModelMatrix, m_globalModelMatrix;

    ///////////////
    // Scene Graph
    ///////////////

    LE3Object* m_pParent;
    std::vector<LE3Object*> m_children;

private:
    // Updates the local model matrix of the object (based on the transform vectors)
    void UpdateLocalModelMatrix();
    // Updates the global model matrix, with respect to the parent object
    void UpdateGlobalModelMatrix();
};