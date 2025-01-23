#pragma once

#include <vector>
#include <memory>

#include "le3_geometry.h"
#include "le3_drawable_object.h"

namespace le3 {
    /*
    * Represents a 3D point cloud (useful for various visualizations and effects).
    * NOTE: LE3PointCloud may not be serialized in Lua. Although, it can be created from within a script object.
    */
    class LE3PointCloud : public LE3DrawableObject {
    public:
        LE3PointCloud(LE3MaterialPtr pMaterial);
        LE3_TYPE_RETURN(LE3PointCloud)

        virtual void update(float deltaTime);
        virtual void draw(LE3ShaderPtr shaderOverride = LE3ShaderPtr());

        void addPoint(glm::vec3 position);
        void addPoint(glm::vec3 position, glm::vec3 normal);
        void addPoint(glm::vec3 position, glm::vec3 normal, glm::vec3 color);
        void addPoints(std::vector<glm::vec3> positions);
        void addPoints(std::vector<glm::vec3> positions, glm::vec3 normal);
        void addPoints(std::vector<glm::vec3> positions, glm::vec3 normal, glm::vec3 color);
        void addPoints(std::vector<glm::vec3> positions, std::vector<glm::vec3> normals);
        void addPoints(std::vector<glm::vec3> positions, std::vector<glm::vec3> normals, std::vector<glm::vec3> colors);
        void clear();

        void create();

        inline void setPointSize(float pointSize) { m_pointSize = pointSize; }
        inline float getPointSize() const { return m_pointSize; }

    protected:
        std::vector<LE3Vertex3p2t3n3c> m_points;
        LE3MeshPtr<LE3Vertex3p2t3n3c> m_pMesh;
        float m_pointSize;
    };
    using LE3PointCloudPtr = std::shared_ptr<LE3PointCloud>;
}