#include "le3_model.h"
using namespace le3;

#include <fmt/core.h>

template<typename LE3VertexType>
LE3Model<LE3VertexType>::LE3Model(LE3MeshPtr<LE3VertexType> pMesh, LE3MaterialPtr pMaterial, LE3DrawPriority priority) :
    LE3DrawableObject(pMaterial), m_pMesh(pMesh) {
        m_drawPriority = priority;
}

template<typename LE3VertexType>
void LE3Model<LE3VertexType>::update(float deltaTime) {
    LE3DrawableObject::update(deltaTime);
    m_animationTime += deltaTime;
    if (m_currentAnimation.size())
    {
        float ticksPerSecond = 25.f;
        if (m_pMesh->getAnimationTracks()[m_currentAnimation].ticksPerSecond)
            ticksPerSecond = (float)m_pMesh->getAnimationTracks()[m_currentAnimation].ticksPerSecond;

        float adjustedAnimationTime = fmodf(m_animationTime * ticksPerSecond, m_pMesh->getAnimationTracks()[m_currentAnimation].duration);
        m_pMesh->getAnimationTracks()[m_currentAnimation].updateBoneMatrices(adjustedAnimationTime);
    }
}

template<typename LE3VertexType>
void LE3Model<LE3VertexType>::draw(LE3ShaderPtr shaderOverride) {
    if (m_pMaterial) m_pMaterial->apply();
    if (m_pMaterial && !shaderOverride) shaderOverride = m_pMaterial->shader;

    // Update animation, if applicable
    std::vector<glm::mat4> boneMatrices;
    if (m_currentAnimation.size())
        boneMatrices = m_pMesh->getAnimationTracks()[m_currentAnimation].getBoneMatrices();
    // else for (int idx = 0; idx < m_pMesh->getSkeleton().m_bones.size(); idx++)
    //     boneMatrices.push_back(glm::mat4(1.f));
    for (int idx = 0; idx < boneMatrices.size(); idx++)
        shaderOverride->uniform(fmt::format("boneMatrices[{}]", idx), boneMatrices[idx]);
    
    shaderOverride->uniform("bIsSkeletal", (uint32_t)(m_currentAnimation.size() > 0));
    if (m_pMesh) m_pMesh->draw();
    shaderOverride->uniform("bIsSkeletal", (uint32_t)false);
}

namespace le3 {
    template class LE3Model<LE3Vertex3p>;
    template class LE3Model<LE3Vertex3p3c>;
    template class LE3Model<LE3Vertex3p2t3n>;
    template class LE3Model<LE3Vertex3p2t3n3c>;
    template class LE3Model<LE3Vertex3p2t3n3tn3b>;
    template class LE3Model<LE3Vertex3p2t3n3tn3b4b4w>;
}