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
        LE3Model(LE3MeshPtr<LE3VertexType> pMesh, LE3MaterialPtr pMaterial);

        virtual void draw();

    private:
        LE3MeshPtr<LE3VertexType> m_pMesh;
    };

    using LE3StaticModel =LE3Model<LE3Vertex>;
    using LE3SkeletalModel =LE3Model<LE3VertexSkeletal>;
    using LE3StaticModelPtr = std::shared_ptr<LE3StaticModel>;
    using LE3SkeletalModelPtr = std::shared_ptr<LE3SkeletalModel>;
}