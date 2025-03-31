#include "graphics/le3_model.h"
#include "core/le3_engine_systems.h"
using namespace le3;

#include <fmt/core.h>


// TODO: Outsource this to a seperate render engine
#ifdef __linux__
#include <GL/glew.h>
#else
#include <gl/glew.h>
#endif


template<typename LE3VertexType>
LE3Model<LE3VertexType>::LE3Model(LE3MeshPtr<LE3VertexType> pMesh, LE3MaterialPtr pMaterial, LE3DrawPriority priority) :
    LE3DrawableObject(pMaterial), m_pMesh(pMesh) {
        m_drawPriority = priority;
        
        if (!m_pMesh.lock()) return;
        getPhysicsComponent().setupRigidBody(m_pMesh.lock()->getColliderInfo(), 0.f); // TODO: Don't setup a rigid body if not needed
        getPhysicsComponent().enable();

}

template<typename LE3VertexType>
void LE3Model<LE3VertexType>::update(float deltaTime) {
    LE3DrawableObject::update(deltaTime);
    if (m_pMesh.expired()) return;
    if (m_animationPlaying) m_animationTime += deltaTime;
    if (m_currentAnimation.size() && (m_currentAnimation != DEFAULT_EMPTY_ANIMATION_NAME) &&
        !m_pMesh.expired() && (m_pMesh.lock()->getAnimationTracks().contains(m_currentAnimation)))
    {
        float ticksPerSecond = 25.f;
        if (m_pMesh.lock()->getAnimationTracks()[m_currentAnimation].ticksPerSecond)
            ticksPerSecond = (float)m_pMesh.lock()->getAnimationTracks()[m_currentAnimation].ticksPerSecond;

        float adjustedAnimationTime = fmodf(m_animationTime * ticksPerSecond, m_pMesh.lock()->getAnimationTracks()[m_currentAnimation].duration);
        m_pMesh.lock()->getAnimationTracks()[m_currentAnimation].updateBoneMatrices(adjustedAnimationTime);
    }
}

template<typename LE3VertexType>
void LE3Model<LE3VertexType>::draw(LE3ShaderPtr shaderOverride) {
    if (m_pMesh.expired()) return;
    if (m_pMaterial.lock()) m_pMaterial.lock()->apply();
    if (m_pMaterial.lock() && !shaderOverride.lock()) {
        shaderOverride = m_pMaterial.lock()->shader;
        // if (shaderOverride.expired()) {
        //     shaderOverride = LE3GetAssetManager().getErrorShader(); // In case of missing shader
        //     shaderOverride.lock()->use();
        // }
    }

    // Update animation, if applicable
    std::vector<glm::mat4> boneMatrices;
    bool shouldAnimate = (m_currentAnimation.size() > 0) && (m_currentAnimation != DEFAULT_EMPTY_ANIMATION_NAME);
    if (!m_pMesh.lock()->getAnimationTracks().contains(m_currentAnimation)) {
        shouldAnimate = false;
        m_currentAnimation = DEFAULT_EMPTY_ANIMATION_NAME;
    }
    if (shouldAnimate)
        boneMatrices = m_pMesh.lock()->getAnimationTracks()[m_currentAnimation].getBoneMatrices();
    else for (int idx = 0; idx < m_pMesh.lock()->getSkeleton().m_bones.size(); idx++)
        boneMatrices.push_back(glm::mat4(1.f));
    for (int idx = 0; idx < boneMatrices.size(); idx++)
        shaderOverride.lock()->uniform(fmt::format("boneMatrices[{}]", idx), boneMatrices[idx]);
    
    shaderOverride.lock()->uniform("bIsSkeletal", (uint32_t)(shouldAnimate));
    if (m_pMesh.lock()) m_pMesh.lock()->draw();
    shaderOverride.lock()->uniform("bIsSkeletal", (uint32_t)false);

    if (LE3GetVisualDebug().getDrawDebugSkeletons()) drawDebugSkeleton(boneMatrices);
}

template<typename LE3VertexType>
void LE3Model<LE3VertexType>::drawDebugSkeleton(std::vector<glm::mat4> boneMatrices) {
    if (m_pMesh.expired()) return;
    glDisable(GL_DEPTH_TEST);
    for (LE3BonePtr bone : m_pMesh.lock()->getSkeleton().getBones()) {
        glm::mat4 modelBone = getWorldMatrix() * boneMatrices[bone->id] * glm::inverse(bone->offset);
        LE3GetVisualDebug().drawDebugBox(modelBone[3], glm::quat(1.f, 0.f, 0.f, 0.f), glm::vec3(0.01f), glm::vec3(0.f, 1.f, 0.f));
        if (bone->parent) {
            glm::mat4 parentBone = getWorldMatrix() * boneMatrices[bone->parent->id] * glm::inverse(bone->parent->offset);
            LE3GetVisualDebug().drawDebugLine(modelBone[3], parentBone[3], glm::vec3(0.f, 1.f, 0.f));
        }
    }
    glEnable(GL_DEPTH_TEST);
}

namespace le3 {
    template class LE3Model<LE3Vertex3p>;
    template class LE3Model<LE3Vertex3p3c>;
    template class LE3Model<LE3Vertex3p2t3n>;
    template class LE3Model<LE3Vertex3p2t3n3c>;
    template class LE3Model<LE3Vertex3p2t3n3tn3b>;
    template class LE3Model<LE3Vertex3p2t3n3tn3b4b4w>;
}