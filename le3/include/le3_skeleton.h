#pragma once 

#include <map>
#include <memory>
#include <string>
#include <vector>

#include <glm/glm.hpp>

namespace le3 {
    struct LE3Bone {
        glm::mat4 transform;
        glm::mat4 offset;
        
        std::string name;
        uint32_t id;

        std::shared_ptr<LE3Bone> parent = nullptr;

        glm::mat4 getTransform();
    };
    using LE3BonePtr = std::shared_ptr<LE3Bone>;

    struct LE3Skeleton {
        void addBone(std::string name);
        LE3BonePtr getBone(std::string boneName);

        glm::mat4 m_globalInverseTransform;
        std::vector<LE3BonePtr> m_bones;
        std::map<std::string, LE3BonePtr> m_boneMapping;
    };
}