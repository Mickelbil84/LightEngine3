#pragma once

#include <memory>
#include <vector>

#include "le3_transform.h"

namespace le3 {
    class LE3Object : public std::enable_shared_from_this<LE3Object> {
    public:
        inline LE3Transform& getTransform() { return m_transform; }

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
    };
    using LE3ObjectPtr = std::shared_ptr<LE3Object>;
}