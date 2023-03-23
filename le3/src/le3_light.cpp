#include "le3_light.h"

#include <fmt/core.h>

const char* gLightSpriteSuffix = "_sprite";

LE3AmbientLight::LE3AmbientLight(glm::vec3 color, float intensity) : 
    LE3Object("ambient_light"), color(color), intensity(intensity), m_pRigidBody(nullptr)
{
}
void LE3AmbientLight::Update(double deltaTime)
{
    LE3Object::Update(deltaTime);

    if (m_pRigidBody)
    {
        btTransform transform;
        transform.setFromOpenGLMatrix(glm::value_ptr(GetModelMatrix() * glm::scale(glm::vec3(1/m_scale))));
        m_pRigidBody->setCenterOfMassTransform(transform);
    }
}
void LE3AmbientLight::Draw()
{
    if (GetSprite())
        GetSprite()->GetMaterial()->diffuseColor = glm::vec4(GetColor(), 1.f);
}
glm::vec3 LE3AmbientLight::GetColor() const
{
    return this->color;
}
void LE3AmbientLight::SetColor(glm::vec3 color)
{
    this->color = color;
}

float LE3AmbientLight::GetIntensity() const
{
    return this->intensity;
}
void LE3AmbientLight::SetIntensity(float intensity)
{
    this->intensity = intensity;
}
LE3Sprite* LE3AmbientLight::GetSprite()
{
    for (auto child : m_children)
        if (dynamic_cast<LE3Sprite*>(child) && 
            (child->GetName() == GetName() + gLightSpriteSuffix))
            return dynamic_cast<LE3Sprite*>(child);
    
    return nullptr;
}
void LE3AmbientLight::SetName(std::string name)
{
    LE3Object::SetName(name);

    LE3Sprite* sprite = GetSprite();
    if (sprite)
        sprite->SetName(GetName() + gLightSpriteSuffix);
}


LE3DirectionalLight::LE3DirectionalLight(std::string name, glm::vec3 color, float intensity) : 
    LE3Object(name), color(color), intensity(intensity), bEnableShadows(false), m_pRigidBody(nullptr), bDebugLine(false)
{
}
void LE3DirectionalLight::Update(double deltaTime)
{
    LE3Object::Update(deltaTime);

    if (m_pRigidBody)
    {
        btTransform transform;
        transform.setFromOpenGLMatrix(glm::value_ptr(GetModelMatrix() * glm::scale(glm::vec3(1/m_scale))));
        m_pRigidBody->setCenterOfMassTransform(transform);
    }
}
void LE3DirectionalLight::Draw()
{
    if (GetSprite())
        GetSprite()->GetMaterial()->diffuseColor = glm::vec4(GetColor(), 1.f);

    if (bDebugLine)
        LE3VisualDebug::DrawDebugLine(
            GetGlobalPosition(), 
            GetGlobalPosition() + gLightDebugRayLength * GetDirection(), 
            GetColor());
}
glm::vec3 LE3DirectionalLight::GetColor() const
{
    return this->color;
}
void LE3DirectionalLight::SetColor(glm::vec3 color)
{
    this->color = color;
}

float LE3DirectionalLight::GetIntensity() const
{
    return this->intensity;
}
void LE3DirectionalLight::SetIntensity(float intensity)
{
    this->intensity = intensity;
}
glm::vec3 LE3DirectionalLight::GetDirection() const
{
    glm::vec3 dir = this->GetModelMatrix() * glm::vec4(gDefaultLightDirection, 0.f);
    return dir;
}
glm::mat4 LE3DirectionalLight::GetViewMatrix(glm::vec3 pos) const
{
    float delta_plane = 10.f;
    glm::mat4 lightProjection = glm::ortho(
        pos.x - delta_plane, pos.x + delta_plane, 
        pos.y - delta_plane, pos.y + delta_plane, 
        pos.z - 2.f, pos.z + 100.f);
    // To combat linearly dependant columns in look-at matrix, we add a very small noise to the up vector
    // glm::mat4 lightView = glm::lookAt(pos, pos + GetDirection(), glm::vec3(0.f, .999f, 0.04471017781f));
    glm::mat4 lightView = glm::lookAt(-delta_plane * GetDirection(), glm::vec3(0.f), glm::vec3(0.f, .999f, 0.04471017781f));
    return lightProjection * lightView;
}
bool LE3DirectionalLight::IsShadowsEnabled() const
{
    return bEnableShadows;
}
void LE3DirectionalLight::SetShadowsEnabled(bool enabled)
{
    bEnableShadows = enabled;
}
LE3ShadowMap& LE3DirectionalLight::GetShadowMap()
{
    return shadowMap;
}
LE3Sprite* LE3DirectionalLight::GetSprite()
{
    for (auto child : m_children)
        if (dynamic_cast<LE3Sprite*>(child) && 
            (child->GetName() == GetName() + gLightSpriteSuffix))
            return dynamic_cast<LE3Sprite*>(child);
    
    return nullptr;
}
void LE3DirectionalLight::SetName(std::string name)
{
    LE3Object::SetName(name);

    LE3Sprite* sprite = GetSprite();
    if (sprite)
        sprite->SetName(GetName() + gLightSpriteSuffix);
}


LE3PointLight::LE3PointLight(std::string name, glm::vec3 color, float intensity, float attn_const, float attn_linear, float attn_exp) : 
    LE3Object(name), color(color), intensity(intensity), attn_const(attn_const), attn_linear(attn_linear), attn_exp(attn_exp), m_pRigidBody(nullptr)
{
}
void LE3PointLight::Update(double deltaTime)
{
    LE3Object::Update(deltaTime);

    if (m_pRigidBody)
    {
        btTransform transform;
        transform.setFromOpenGLMatrix(glm::value_ptr(GetModelMatrix() * glm::scale(glm::vec3(1/m_scale))));
        m_pRigidBody->setCenterOfMassTransform(transform);
    }
}
void LE3PointLight::Draw()
{
    if (GetSprite())
        GetSprite()->GetMaterial()->diffuseColor = glm::vec4(GetColor(), 1.f);
}
glm::vec3 LE3PointLight::GetColor() const
{
    return this->color;
}
void LE3PointLight::SetColor(glm::vec3 color)
{
    this->color = color;
}

float LE3PointLight::GetIntensity() const
{
    return this->intensity;
}
void LE3PointLight::SetIntensity(float intensity)
{
    this->intensity = intensity;
}
float LE3PointLight::GetAttenuationConst() const
{
    return this->attn_const;
}
float LE3PointLight::GetAttenuationLinear() const
{
    return this->attn_linear;
}
float LE3PointLight::GetAttenuationExp() const
{
    return this->attn_exp;
}
void LE3PointLight::SetAttenuationConst(float attn_const)
{
    this->attn_const = attn_const;
}
void LE3PointLight::SetAttenuationLinear(float attn_linear)
{
    this->attn_linear = attn_linear;
}
void LE3PointLight::SetAttenuationExp(float attn_exp)
{
    this->attn_exp = attn_exp;
}
LE3Sprite* LE3PointLight::GetSprite()
{
    for (auto child : m_children)
        if (dynamic_cast<LE3Sprite*>(child) && 
            (child->GetName() == GetName() + gLightSpriteSuffix))
            return dynamic_cast<LE3Sprite*>(child);
    
    return nullptr;
}
void LE3PointLight::SetName(std::string name)
{
    LE3Object::SetName(name);

    LE3Sprite* sprite = GetSprite();
    if (sprite)
        sprite->SetName(GetName() + gLightSpriteSuffix);
}

LE3SpotLight::LE3SpotLight(std::string name, glm::vec3 color, float intensity, 
        float cutoff, float outer_cutoff) :
    LE3Object(name), color(color), intensity(intensity), cutoff(cutoff), outer_cutoff(outer_cutoff), 
    bEnableShadows(false), m_pRigidBody(nullptr), bDebugLine(false)
{
}

void LE3SpotLight::Update(double deltaTime)
{
    LE3Object::Update(deltaTime);

    if (m_pRigidBody)
    {
        btTransform transform;
        transform.setFromOpenGLMatrix(glm::value_ptr(GetModelMatrix() * glm::scale(glm::vec3(1/m_scale))));
        m_pRigidBody->setCenterOfMassTransform(transform);
    }
}
void LE3SpotLight::Draw()
{
    if (GetSprite())
        GetSprite()->GetMaterial()->diffuseColor = glm::vec4(GetColor(), 1.f);
    if (bDebugLine)
        LE3VisualDebug::DrawDebugLine(
            GetGlobalPosition(), 
            GetGlobalPosition() + gLightDebugRayLength * GetDirection(), 
            GetColor());
}
glm::vec3 LE3SpotLight::GetColor() const
{
    return this->color;
}
void LE3SpotLight::SetColor(glm::vec3 color)
{
    this->color = color;
}

float LE3SpotLight::GetIntensity() const
{
    return this->intensity;
}
void LE3SpotLight::SetIntensity(float intensity)
{
    this->intensity = intensity;
}

float LE3SpotLight::GetCutoff() const
{
    return this->cutoff;
}
float LE3SpotLight::GetOuterCutoff() const
{
    return this->outer_cutoff;
}
void LE3SpotLight::SetCutoff(float cutoff)
{
    this->cutoff = cutoff;
}
void LE3SpotLight::SetOuterCutoff(float outer_cutoff)
{
    this->outer_cutoff = cutoff;
}

glm::vec3 LE3SpotLight::GetDirection() const
{
    glm::vec3 dir = this->GetModelMatrix() * glm::vec4(gDefaultLightDirection, 0.f);
    return dir;
}
glm::mat4 LE3SpotLight::GetViewMatrix() const
{
    float delta_plane = 15.f;
    glm::vec3 pos = GetGlobalPosition();
    glm::mat4 lightProjection = glm::perspective(glm::radians(45.f), 1.f, .5f, 40.f);
    // To combat linearly dependant columns in look-at matrix, we add a very small noise to the up vector
    glm::mat4 lightView = glm::lookAt(pos, pos + GetDirection(), glm::vec3(0.f, .999f, 0.04471017781f));
    return lightProjection * lightView;
}
bool LE3SpotLight::IsShadowsEnabled() const
{
    return bEnableShadows;
}
void LE3SpotLight::SetShadowsEnabled(bool enabled)
{
    bEnableShadows = enabled;
}
LE3ShadowMap& LE3SpotLight::GetShadowMap()
{
    return shadowMap;
}
LE3Sprite* LE3SpotLight::GetSprite()
{
    for (auto child : m_children)
        if (dynamic_cast<LE3Sprite*>(child) && 
            (child->GetName() == GetName() + gLightSpriteSuffix))
            return dynamic_cast<LE3Sprite*>(child);
    
    return nullptr;
}
void LE3SpotLight::SetName(std::string name)
{
    LE3Object::SetName(name);

    LE3Sprite* sprite = GetSprite();
    if (sprite)
        sprite->SetName(GetName() + gLightSpriteSuffix);
}
