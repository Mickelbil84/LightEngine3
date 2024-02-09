#include "le3_skeleton.h"
using namespace le3;


glm::mat4 LE3Bone::getTransform()
{
    glm::mat4 res = transform;
    if (parent) res = parent->getTransform() * res;
    return res;
}


void LE3Skeleton::addBone(std::string name)
{
    if (getBone(name)) return;
    LE3BonePtr bone = std::make_shared<LE3Bone>();
    bone->name = name;
    bone->id = (uint32_t)m_bones.size();
    m_bones.push_back(bone);
    m_boneMapping[name] = bone;
}


LE3BonePtr LE3Skeleton::getBone(std::string boneName)
{
    if (!m_boneMapping.contains(boneName)) return nullptr;
    return m_boneMapping[boneName];
}
