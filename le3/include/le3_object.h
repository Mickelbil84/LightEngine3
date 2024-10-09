#pragma once

#include <string>
#include <memory>
#include <vector>
#include <algorithm>

#include "le3_transform.h"

#define LE3_TYPE_RETURN(cls) virtual std::string getObjectType() const { return #cls; }

namespace le3 {
    class LE3Object : public std::enable_shared_from_this<LE3Object> {
    public:
        LE3_TYPE_RETURN(LE3Object)

        inline LE3Transform& getTransform() { return m_transform; }

        inline glm::mat4 getWorldMatrix() const { return m_worldMatrix; }
        inline glm::vec3 getWorldPosition() const { return glm::vec3(m_worldMatrix[3]); }

        virtual void update(float deltaTime);

        // Are called before and after the update method, only for non inspector scenes
        virtual void preUpdate() {}
        virtual void postUpdate() {}

        std::shared_ptr<LE3Object> getParent() { return m_pParent; }
        std::vector<std::shared_ptr<LE3Object>> getChildren() const { return m_pChildren; }

        void reparent(std::shared_ptr<LE3Object> newParent);
        void appendChild(std::shared_ptr<LE3Object> pChild);

        void setName(const std::string& name) { m_name = name; } // Use with causion, renaming should be done via scene
        std::string getName() const { return m_name; }

        // A delegate object is an object whose sole purpose is to represent (usually visually) another object,
        // its parent. For example when selecting a light sprite, we mean to select the light itself.
        bool isDelegate() const { return m_bIsDelegate; }
        void setIsDelegate(bool isDelegate) { m_bIsDelegate = isDelegate; }

    protected:
        LE3Transform m_transform;

    private:
        // Graph structure
        std::shared_ptr<LE3Object> m_pParent = nullptr;
        std::vector<std::shared_ptr<LE3Object>> m_pChildren;

        std::string m_name = "";
        glm::mat4 m_worldMatrix = glm::mat4(1.f);
        bool m_bIsDelegate = false;
    };
    using LE3ObjectPtr = std::shared_ptr<LE3Object>;
    using LE3ObjectWeakPtr = std::weak_ptr<LE3Object>;
}