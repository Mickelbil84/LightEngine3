#pragma once

#include <string>

#include <glm/glm.hpp>

namespace le3 {

    enum class LE3ColliderType {
        LE3ColliderType_Box,
        LE3ColliderType_Sphere,
        LE3ColliderType_Ellipsoid,
        LE3ColliderType_ConvexHull,
    };
    std::string LE3ColliderType_toString(LE3ColliderType type);
    LE3ColliderType LE3ColliderType_fromString(const std::string& str);

    /*
    * When loading a mesh, we calculate its bounding volumes for collisions.
    * We also store the colldier type, so that it can be adjusted in editor.
    */
    struct LE3ColliderInfo {
        LE3ColliderType colliderType;

        glm::vec3 centroid = glm::vec3(0.f); // Bounding box, sphere, ellipsoid
        glm::vec3 extent = glm::vec3(1.f); // Bounding box, ellipsoid
        float radius = 1.f; // Bounding sphere
        // TODO: Implement convex hull collisions
    };

}