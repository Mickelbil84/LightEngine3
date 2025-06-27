#pragma once

#include <string>
#include <vector>

#include <glm/glm.hpp>

namespace le3 {

    enum class LE3ColliderType {
        LE3ColliderType_Box,
        LE3ColliderType_Sphere,
        LE3ColliderType_Cone,
        LE3ColliderType_Cylinder,
        LE3ColliderType_Capsule, // DOES NOT SUPPORT NON-UNIFORM SCALING
        LE3ColliderType_ConvexHull,
    };
    std::string LE3ColliderType_toString(LE3ColliderType type);
    LE3ColliderType LE3ColliderType_fromString(const std::string& str);

    /*
    * When loading a mesh, we calculate its bounding volumes for collisions.
    * We also store the colldier type, so that it can be adjusted in editor.
    */
    struct LE3ColliderInfo {
        // Controllable settings
        LE3ColliderType colliderType = LE3ColliderType::LE3ColliderType_Box; // Default is box
        int decimationResolution = 7; // TODO: control this as a property of the mesh

        // Computed values
        glm::vec3 centroid = glm::vec3(0.f); // Bounding box, sphere
        glm::vec3 extent = glm::vec3(1.f); // Bounding box
        float radius = 1.f; // Bounding sphere
        std::vector<glm::vec3> decimatedVertices; // Convex hull
        std::vector<std::pair<glm::vec3, glm::vec3>> hullEdges;

        inline bool operator==(const LE3ColliderInfo& other) const {
            return colliderType == other.colliderType &&
                centroid == other.centroid &&
                extent == other.extent &&
                radius == other.radius;
        }
        inline bool operator!=(const LE3ColliderInfo& other) const {
            return !(*this == other);
        }
    };

}