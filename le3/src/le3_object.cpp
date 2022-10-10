#include "le3_object.h"

LE3Object::LE3Object(std::string name, glm::vec3 position, glm::vec3 rotation, float scale):
    m_name(name),
    m_position(position), m_rotation(rotation), m_scale(scale),
    m_pParent(nullptr),
    m_bHiddenInSceneGraph(false),
    m_bHidden(false)
{
    UpdateLocalModelMatrix();
    UpdateGlobalModelMatrix();
}

void LE3Object::Update(double deltaTime)
{
    UpdateLocalModelMatrix();
    UpdateGlobalModelMatrix();
}

void LE3Object::Draw()
{

}

void LE3Object::UpdateLocalModelMatrix()
{
    m_localModelMatrix = 
    glm::translate(m_position) *
    glm::eulerAngleXYZ(m_rotation.x, m_rotation.y, m_rotation.z) * 
    glm::scale(glm::vec3(m_scale));
}
void LE3Object::UpdateGlobalModelMatrix()
{
    glm::mat4 parentMatrix = glm::mat4(1.f);
    if (m_pParent) parentMatrix = m_pParent->m_globalModelMatrix;
    m_globalModelMatrix = parentMatrix * m_localModelMatrix;
}

glm::mat4 LE3Object::GetModelMatrix() const
{
    return m_globalModelMatrix;
}

void LE3Object::Reparent(LE3Object* parent)
{
    // if (m_pParent == parent)
    //     return;
    if (m_pParent)
    {
        m_pParent->RemoveChild(this);
        m_pParent = nullptr;
    }
    if (parent)
    {
        parent->AppendChild(this);
        m_pParent = parent;
    }
}

std::vector<LE3Object*> LE3Object::GetChildren() const
{
    return m_children;
}

void LE3Object::AppendChild(LE3Object* child)
{
    m_children.push_back(child);
    child->m_pParent = this;
}

void LE3Object::RemoveChild(LE3Object* child)
{
    std::erase(m_children, child);
    child->m_pParent = nullptr;
}

void LE3Object::AddRotationX(float rot)
{
    m_rotation.x += rot;
}
void LE3Object::AddRotationY(float rot)
{
    m_rotation.y += rot;
}
void LE3Object::AddRotationZ(float rot)
{
    m_rotation.z += rot;
}


void LE3Object::SetPosition(glm::vec3 position)
{
    m_position = position;
}
void LE3Object::SetRotation(glm::vec3 rotation)
{
    m_rotation = rotation;
}
void LE3Object::SetScale(float scale)
{
    m_scale = scale;
}
glm::vec3 LE3Object::GetPosition() const
{
    return m_position;
}
glm::vec3 LE3Object::GetRotation() const
{
    return m_rotation;
}
float LE3Object::GetScale() const
{
    return m_scale;
}

void LE3Object::SetName(std::string name)
{
    m_name = name;
}
std::string LE3Object::GetName() const
{
    return m_name;
}

void LE3Object::SetHiddenInSceneGraph(bool hidden)
{
    m_bHiddenInSceneGraph = hidden;
}
bool LE3Object::GetHiddenInSceneGraph() const
{
    return m_bHiddenInSceneGraph;
}

void LE3Object::SetHidden(bool hidden)
{
    m_bHidden = hidden;
}
bool LE3Object::GetHidden() const
{
    return m_bHidden;
}

glm::vec3 LE3Object::GetGlobalPosition() const
{
    glm::vec3 scale;
    glm::quat rotation;
    glm::vec3 translation;
    glm::vec3 skew;
    glm::vec4 perspective;
    glm::decompose(m_globalModelMatrix, scale, rotation, translation, skew, perspective);
    return translation;
}

