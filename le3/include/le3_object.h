#pragma once

#include <memory>
#include <vector>
#include <algorithm>

#include "le3_transform.h"

namespace le3 {
    class LE3Object : public std::enable_shared_from_this<LE3Object> {
    public:
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

    protected:
        LE3Transform m_transform;

    private:
        // Graph structure
        std::shared_ptr<LE3Object> m_pParent = nullptr;
        std::vector<std::shared_ptr<LE3Object>> m_pChildren;

        glm::mat4 m_worldMatrix = glm::mat4(1.f);
    };
    using LE3ObjectPtr = std::shared_ptr<LE3Object>;
}