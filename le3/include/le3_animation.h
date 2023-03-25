#pragma once

#include <map>
#include <vector>
#include <string>
#include <memory>

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/matrix_decompose.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "le3_skeleton.h"

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

struct LE3AnimationTrack
{
public:
    LE3AnimationTrack(LE3Skeleton* skeleton);

    std::string name;
    float duration;
    int ticksPerSecond;

    LE3Skeleton* skeleton;
    std::map<std::shared_ptr<LE3Bone>, std::vector<LE3PositionKeyframe>> positionKeyframes;
    std::map<std::shared_ptr<LE3Bone>, std::vector<LE3RotationKeyframe>> rotationKeyframes;
    std::map<std::shared_ptr<LE3Bone>, std::vector<LE3ScaleKeyframe>> scaleKeyframes;

    void LoadAnimationTrack(const aiScene* scene, unsigned int trackIdx);
    std::vector<glm::mat4> GetBoneMatrices(float animationTime);
};

