#pragma once

#include <glm/glm.hpp>

namespace le3 {
    struct LE3Transform {
    public:
        LE3Transform();

        inline glm::mat4 getTransformMatrix() const { return m_transform; }

        inline void invalidate() { m_bInvalidated = true; }
        inline void validate() { m_bInvalidated = false; }
        inline bool isInvalidated() const { return m_bInvalidated; }

    private:
        glm::mat4 m_transform;

        bool m_bInvalidated = false;
    };
};