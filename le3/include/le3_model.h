#pragma once

#include <map>
#include <string>

#include <glm/glm.hpp>

#include "le3_geometry.h"
#include "le3_material.h"
#include "le3_drawable_object.h"

namespace le3 {
    template<typename LE3VertexType>
    class LE3Model : public LE3DrawableObject {
    public:
        LE3Model(LE3MeshPtr<LE3VertexType> pMesh, LE3MaterialPtr pMaterial, LE3DrawPriority priority = DRAW_PRIORITY_LOW);

        virtual void update(float deltaTime);
        virtual void draw(LE3ShaderPtr shaderOverride = nullptr);

        LE3MeshPtr<LE3VertexType> getMesh() { return m_pMesh; }
        void setMesh(LE3MeshPtr<LE3VertexType> pMesh) { m_pMesh = pMesh; }

        void setCurrentAnimation(std::string animationName) { m_currentAnimation = animationName; }

    protected:
        LE3MeshPtr<LE3VertexType> m_pMesh;

        // If skeletal
        std::string m_currentAnimation; 
        float m_animationTime = 0.f;
    };

    using LE3StaticModel = LE3Model<LE3Vertex>;
    using LE3SkeletalModel = LE3Model<LE3VertexSkeletal>;
    using LE3StaticModelPtr = std::shared_ptr<LE3StaticModel>;
    using LE3SkeletalModelPtr = std::shared_ptr<LE3SkeletalModel>;
}