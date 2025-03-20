#pragma once

#include <map>
#include <string>

#include <glm/glm.hpp>

#include "graphics/le3_geometry.h"
#include "graphics/le3_material.h"
#include "graphics/le3_drawable_object.h"

namespace le3 {
    const std::string DEFAULT_EMPTY_ANIMATION_NAME = "[None]";

    template<typename LE3VertexType>
    class LE3Model : public LE3DrawableObject {
    public:
        LE3Model(LE3MeshPtr<LE3VertexType> pMesh, LE3MaterialPtr pMaterial, LE3DrawPriority priority = DRAW_PRIORITY_LOW);
        LE3_TYPE_RETURN(LE3Model)

        virtual void update(float deltaTime);
        virtual void draw(LE3ShaderPtr shaderOverride = LE3ShaderPtr());

        LE3MeshPtr<LE3VertexType> getMesh() { return m_pMesh; }
        void setMesh(LE3MeshPtr<LE3VertexType> pMesh) { m_pMesh = pMesh; }

        void setCurrentAnimation(std::string animationName) { m_currentAnimation = animationName;  resetAnimation(); }
        std::string getCurrentAnimation() const { return m_currentAnimation; }
        void setAnimationPlaying(bool playing) { m_animationPlaying = playing; }
        bool isAnimationPlaying() const { return m_animationPlaying; }
        void resetAnimation() { m_animationTime = 0.f; }
        void discardAnimation() { setCurrentAnimation(DEFAULT_EMPTY_ANIMATION_NAME); }

    protected:
        LE3MeshPtr<LE3VertexType> m_pMesh;

        // If skeletal
        void drawDebugSkeleton(std::vector<glm::mat4> boneMatrices);
        std::string m_currentAnimation = DEFAULT_EMPTY_ANIMATION_NAME; 
        float m_animationTime = 0.f;
        bool m_animationPlaying = false;
    };

    class LE3StaticModel : public LE3Model<LE3Vertex> {
    public:
        LE3StaticModel(LE3MeshPtr<LE3Vertex> pMesh, LE3MaterialPtr pMaterial, LE3DrawPriority priority = DRAW_PRIORITY_LOW) :
            LE3Model<LE3Vertex>(pMesh, pMaterial, priority) {}
        LE3_TYPE_RETURN(LE3StaticModel);
    };
    using LE3StaticModelPtr = std::shared_ptr<LE3StaticModel>;

    class LE3SkeletalModel : public LE3Model<LE3VertexSkeletal> {
    public:
        LE3SkeletalModel(LE3MeshPtr<LE3VertexSkeletal> pMesh, LE3MaterialPtr pMaterial, LE3DrawPriority priority = DRAW_PRIORITY_LOW) :
            LE3Model<LE3VertexSkeletal>(pMesh, pMaterial, priority) {}
        LE3_TYPE_RETURN(LE3SkeletalModel);
    };
    using LE3SkeletalModelPtr = std::shared_ptr<LE3SkeletalModel>;
}