#pragma once

#include <map>
#include <string>
#include <vector>
#include <memory>

#include <gl/glew.h>
#include <glm/glm.hpp>

struct LE3Bone
{
public:
    glm::mat4 transform;
    glm::mat4 offset;
    std::string name;
    GLuint id;

    std::shared_ptr<LE3Bone> parent = nullptr;

    glm::mat4 GetTransform();
};
struct LE3Skeleton
{
public:
    void AddBone(std::string boneName);
    std::shared_ptr<LE3Bone> GetBone(std::string boneName);

    glm::mat4 m_globalInverseTransform;
    std::vector<std::shared_ptr<LE3Bone>> m_bones;
    std::map<std::string, std::shared_ptr<LE3Bone>> m_boneMapping;
};