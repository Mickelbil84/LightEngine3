#pragma once

#include <map>
#include <vector>
#include <string>
#include <memory>

#ifndef GLM_ENABLE_EXPERIMENTAL
#define GLM_ENABLE_EXPERIMENTAL
#endif

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/matrix_decompose.hpp>

// TODO: Move to *.cpp
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "le3_skeleton.h"

namespace le3 {
    struct LE3PositionKeyframe
    {
        float timestamp;
        glm::vec3 position;
    };
    struct LE3RotationKeyframe
    {
        float timestamp;
        glm::quat rotation;
    };
    struct LE3ScaleKeyframe
    {
        float timestamp;
        glm::vec3 scale;
    };

    struct LE3AnimationTrack {
    public:
        LE3AnimationTrack();

        std::string name;
        float duration;
        int ticksPerSecond;

        LE3Skeleton* skeleton;
        std::map<LE3BonePtr, std::vector<LE3PositionKeyframe>> positionKeyframes;
        std::map<LE3BonePtr, std::vector<LE3RotationKeyframe>> rotationKeyframes;
        std::map<LE3BonePtr, std::vector<LE3ScaleKeyframe>> scaleKeyframes;
        std::vector<glm::mat4> boneMatrices;

        void loadAnimationTrack(const aiScene* scene, unsigned int trackIdx);
        void updateBoneMatrices(float animationTime);
        std::vector<glm::mat4> getBoneMatrices();

    protected:
        glm::mat4 positionKeyframeInterpolation(LE3BonePtr bone, float animationTime);
        glm::mat4 rotationKeyframeInterpolation(LE3BonePtr bone, float animationTime);
        glm::mat4 scaleKeyframeInterpolation(LE3BonePtr bone, float animationTime);
    };

}