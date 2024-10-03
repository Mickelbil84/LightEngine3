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
        LE3_TYPE_RETURN(LE3Model)

        virtual void update(float deltaTime);
        virtual void draw(LE3ShaderPtr shaderOverride = nullptr);

        LE3MeshPtr<LE3VertexType> getMesh() { return m_pMesh; }
        void setMesh(LE3MeshPtr<LE3VertexType> pMesh) { m_pMesh = pMesh; }

        void setCurrentAnimation(std::string animationName) { m_currentAnimation = animationName; }

        std::string getMeshName() const { return m_meshName; }
        void setMeshName(std::string meshName) { m_meshName = meshName; }
        
        std::string getMaterialName() const { return m_materialName; }
        void setMaterialName(std::string materialName) { m_materialName = materialName; }

    protected:
        LE3MeshPtr<LE3VertexType> m_pMesh;

        std::string m_meshName, m_materialName;

        // If skeletal
        std::string m_currentAnimation; 
        float m_animationTime = 0.f;
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