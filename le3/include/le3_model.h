#pragma once

#include <map>
#include <string>

#include <glm/glm.hpp>

#include "le3_object.h"
#include "le3_geometry.h"
#include "le3_material.h"

namespace le3 {
    template<typename LE3VertexType>
    struct LE3MeshNode {
        LE3MeshPtr<LE3VertexType> pMesh = nullptr;
        LE3MaterialPtr pMaterial = nullptr;
    };

    template<typename LE3VertexType>
    class LE3Model : LE3Object {
    public:
        LE3Model(LE3MeshPtr<LE3VertexType> pMesh, LE3MaterialPtr pMaterial);

    private:
        LE3MeshPtr<LE3VertexType> m_pMesh;
        LE3MaterialPtr m_pMaterial;
    };


}