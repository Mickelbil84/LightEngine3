#include "le3_animation.h"

LE3AnimationTrack::LE3AnimationTrack(LE3Skeleton* skeleton) : skeleton(skeleton)
{

}

void LE3AnimationTrack::LoadAnimationTrack(const aiScene* scene, unsigned int trackIdx)
{    
    aiAnimation* animation = scene->mAnimations[trackIdx];
    this->name = std::string(animation->mName.C_Str());
    this->duration = animation->mDuration;
    this->ticksPerSecond = animation->mTicksPerSecond;

    for (int i = 0; i < animation->mNumChannels; ++i)
    {
        aiNodeAnim* nodeAnim = animation->mChannels[i];
        std::string boneName = std::string(nodeAnim->mNodeName.C_Str());
        std::shared_ptr<LE3Bone> bone = this->skeleton->GetBone(boneName);
        if (!bone) continue;

        for (int j = 0; j < nodeAnim->mNumPositionKeys; ++j)
        {
            LE3PositionKeyframe key;
            key.position.x = nodeAnim->mPositionKeys[j].mValue.x;
            key.position.y = nodeAnim->mPositionKeys[j].mValue.y;
            key.position.z = nodeAnim->mPositionKeys[j].mValue.z;
            key.timestamp = nodeAnim->mPositionKeys[j].mTime;
            positionKeyframes[bone].push_back(key);
        }

        for (int j = 0; j < nodeAnim->mNumRotationKeys; ++j)
        {
            LE3RotationKeyframe key;
            key.rotation.x = nodeAnim->mRotationKeys[j].mValue.x;
            key.rotation.y = nodeAnim->mRotationKeys[j].mValue.y;
            key.rotation.z = nodeAnim->mRotationKeys[j].mValue.z;
            key.rotation.w = nodeAnim->mRotationKeys[j].mValue.w;
            key.timestamp = nodeAnim->mRotationKeys[j].mTime;
            rotationKeyframes[bone].push_back(key);
        }

        for (int j = 0; j < nodeAnim->mNumScalingKeys; ++j)
        {
            LE3ScaleKeyframe key;
            key.scale.x = nodeAnim->mScalingKeys[j].mValue.x;
            key.scale.y = nodeAnim->mScalingKeys[j].mValue.y;
            key.scale.z = nodeAnim->mScalingKeys[j].mValue.z;
            key.timestamp = nodeAnim->mScalingKeys[j].mTime;
            scaleKeyframes[bone].push_back(key);
        }
    }
}

std::vector<glm::mat4> LE3AnimationTrack::GetBoneMatrices(float animationTime)
{
    std::vector<glm::mat4> res;

    // Set the local keyframe matrices
    for (auto bone : skeleton->m_bones)
    {
        if (!positionKeyframes[bone].size() || !rotationKeyframes[bone].size() || !scaleKeyframes[bone].size())
        {
            bone->transform = glm::mat4(1.f);
            continue;
        }
        glm::mat4 translation = glm::translate(positionKeyframes[bone][0].position);
        glm::mat4 rotation = glm::toMat4(rotationKeyframes[bone][0].rotation);
        glm::mat4 scale = glm::scale(scaleKeyframes[bone][0].scale);
        bone->transform = translation * rotation * scale;
    }

    // Get the bone matrices
    for (auto bone : skeleton->m_bones)
        res.push_back(bone->GetTransform() * bone->offset);

    return res;
}