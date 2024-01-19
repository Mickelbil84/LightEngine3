#pragma once

#include <map>
#include <string>

#include <glm/glm.hpp>

#include "le3_geometry.h"
#include "le3_material.h"

namespace le3 {
    template<typename LE3VertexType>
    struct LE3MeshNode {
        LE3MeshPtr<LE3VertexType> pMesh = nullptr;
        LE3MaterialPtr pMaterial = nullptr;
        glm::mat4 offset = glm::mat4(1.f);
    };

    class LE3Model {
    public:

    private:
        
    };


}