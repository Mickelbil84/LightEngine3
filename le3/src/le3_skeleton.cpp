#include "le3_skeleton.h"

glm::mat4 LE3Bone::GetTransform()
{
    glm::mat4 res = transform;
    if (parent)
        res = parent->GetTransform() * res;
    return res;
}

void LE3Skeleton::AddBone(std::string boneName)
{
    if (GetBone(boneName)) return;
    std::shared_ptr<LE3Bone> pBone = std::make_shared<LE3Bone>();
    pBone->name = boneName;
    pBone->id = (GLuint)m_bones.size();
    m_bones.push_back(pBone);
    m_boneMapping[boneName] = pBone;
}
std::shared_ptr<LE3Bone> LE3Skeleton::GetBone(std::string boneName)
{
    if (m_boneMapping.find(boneName) == m_boneMapping.end()) return nullptr;
    return m_boneMapping[boneName];
}