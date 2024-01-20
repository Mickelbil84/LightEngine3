#pragma once

#include <memory>
#include <vector>

#include "le3_transform.h"

namespace le3 {
    // TODO: add hidden, add selected(?)
    class LE3Object : public std::enable_shared_from_this<LE3Object> {
    public:
        inline LE3Transform& getTransform() { return m_transform; }

        inline glm::mat4 getWorldMatrix() const { return m_worldMatrix; }

        virtual void update(float deltaTime);
        virtual void draw();

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