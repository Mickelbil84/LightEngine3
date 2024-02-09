#include "le3_animation.h"
using namespace le3;

LE3AnimationTrack::LE3AnimationTrack() {
}

void LE3AnimationTrack::loadAnimationTrack(const aiScene* scene, unsigned int trackIdx)
{    
    aiAnimation* animation = scene->mAnimations[trackIdx];
    this->name = std::string(animation->mName.C_Str());
    this->duration = animation->mDuration;
    this->ticksPerSecond = animation->mTicksPerSecond;

    for (int i = 0; i < animation->mNumChannels; ++i)
    {
        aiNodeAnim* nodeAnim = animation->mChannels[i];
        std::string boneName = std::string(nodeAnim->mNodeName.C_Str());
        std::shared_ptr<LE3Bone> bone = this->skeleton->getBone(boneName);
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

void LE3AnimationTrack::updateBoneMatrices(float animationTime)
{
    boneMatrices.clear();
    // Set the local keyframe matrices
    for (auto bone : skeleton->m_bones)
    {
        if (!positionKeyframes[bone].size() || !rotationKeyframes[bone].size() || !scaleKeyframes[bone].size())
        {
            bone->transform = glm::mat4(1.f);
            continue;
        }
        glm::mat4 translation = positionKeyframeInterpolation(bone, animationTime);
        glm::mat4 rotation = rotationKeyframeInterpolation(bone, animationTime);
        glm::mat4 scale = scaleKeyframeInterpolation(bone, animationTime);
        bone->transform = translation * rotation * scale;
    }

    // Get the bone matrices
    for (auto bone : skeleton->m_bones)
        boneMatrices.push_back(bone->getTransform() * bone->offset);
}

std::vector<glm::mat4> LE3AnimationTrack::getBoneMatrices()
{
    return boneMatrices;
}


glm::mat4 LE3AnimationTrack::positionKeyframeInterpolation(std::shared_ptr<LE3Bone> bone, float animationTime)
{
    if (!positionKeyframes[bone].size())
        return glm::mat4(1.f);
    int keyframeIdx = 0;
    for (; keyframeIdx < positionKeyframes[bone].size() - 1; keyframeIdx++)
        if (animationTime < positionKeyframes[bone][keyframeIdx+1].timestamp) break; 

    float alpha =  (positionKeyframes[bone][keyframeIdx+1].timestamp - animationTime) / 
        (positionKeyframes[bone][keyframeIdx+1].timestamp - positionKeyframes[bone][keyframeIdx].timestamp);

    glm::vec3 interpolatedPosition = alpha * positionKeyframes[bone][keyframeIdx].position + 
        (1 - alpha) * positionKeyframes[bone][keyframeIdx+1].position;

    return glm::translate(interpolatedPosition);
}
glm::mat4 LE3AnimationTrack::rotationKeyframeInterpolation(std::shared_ptr<LE3Bone> bone, float animationTime)
{
    if (!rotationKeyframes[bone].size())
        return glm::mat4(1.f);
    int keyframeIdx = 0;
    for (; keyframeIdx < rotationKeyframes[bone].size() - 1; keyframeIdx++)
        if (animationTime < rotationKeyframes[bone][keyframeIdx+1].timestamp) break; 

    float alpha =  (scaleKeyframes[bone][keyframeIdx+1].timestamp - animationTime) / 
        (scaleKeyframes[bone][keyframeIdx+1].timestamp - scaleKeyframes[bone][keyframeIdx].timestamp);

    glm::quat interpolatedRotation = glm::slerp(
        rotationKeyframes[bone][keyframeIdx].rotation , 
        rotationKeyframes[bone][keyframeIdx+1].rotation, 1.f - alpha);
    interpolatedRotation = glm::normalize(interpolatedRotation);

    return glm::toMat4(interpolatedRotation);
}
glm::mat4 LE3AnimationTrack::scaleKeyframeInterpolation(std::shared_ptr<LE3Bone> bone, float animationTime)
{
    if (!scaleKeyframes[bone].size())
        return glm::mat4(1.f);
    int keyframeIdx = 0;
    for (; keyframeIdx < scaleKeyframes[bone].size() - 1; keyframeIdx++)
        if (animationTime < scaleKeyframes[bone][keyframeIdx+1].timestamp) break; 


    float alpha =  (scaleKeyframes[bone][keyframeIdx+1].timestamp - animationTime) / 
        (scaleKeyframes[bone][keyframeIdx+1].timestamp - scaleKeyframes[bone][keyframeIdx].timestamp);
        
    glm::vec3 interpolatedScale = alpha * scaleKeyframes[bone][keyframeIdx].scale + 
        (1 - alpha) * scaleKeyframes[bone][keyframeIdx+1].scale;

    return glm::scale(interpolatedScale);
}