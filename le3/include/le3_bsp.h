#pragma once

#include <map>
#include <set>
#include <vector>
#include <memory>

#include "le3_geometry.h"
#include "le3_drawable_object.h"


namespace le3 {

    const std::string LE3_BSP_MESH_NAME = "__#BSP#";

    enum LE3BSPBrushType {
        LE3_BRUSH_ADDITIVE = 0, LE3_BRUSH_SUBTRACTIVE = 1
    };

    class LE3BSPBrush : public LE3DrawableObject {
    public:
        LE3BSPBrush() : LE3DrawableObject(nullptr), m_brushType(LE3_BRUSH_ADDITIVE) {}

        LE3BSPBrushType getBrushType() const { return m_brushType; }
        void setBrushType(LE3BSPBrushType brushType) { m_brushType = brushType; }

        virtual void draw(LE3ShaderPtr shaderOverride);

    protected:
        LE3BSPBrushType m_brushType;
    };
    using LE3BSPBrushPtr = std::shared_ptr<LE3BSPBrush>;

    struct LE3BSPManager {
    public:
        LE3BSPManager();

        void build();
        void setShowBrushes(bool showBrushes);
        void addBrush(std::weak_ptr<LE3BSPBrush> brush);

        inline std::vector<LE3Vertex> getGeometry() const { return m_geometry; }

    private:
        std::vector<std::weak_ptr<LE3BSPBrush>> m_brushes;   
        std::vector<LE3Vertex> m_geometry; 
    };


    constexpr double LE3_BSP_EPS = 1e-5;
    enum LE3BSP_Side {
        IN = -1, ON = 0, OUT = 1
    };

    using LE3BSP_Triangle = std::vector<glm::dvec3>;

    struct LE3BSP_SplitResult {
        std::vector<LE3BSP_Triangle> F_in, F_out, F_on;
    };

    struct LE3BSP_Hyperplane {
    public:
        glm::dvec3 normal;
        double offset;

        LE3BSP_Hyperplane(glm::dvec3 normal, double offset);

        static LE3BSP_Hyperplane fromTriangle(LE3BSP_Triangle triangle);
        static glm::dvec3 getTriangleNormal(LE3BSP_Triangle triangle);

        LE3BSP_Side determinePoint(glm::dvec3 point);
        LE3BSP_SplitResult splitTriangle(LE3BSP_Triangle triangle);
        LE3BSP_SplitResult splitTriangles(std::vector<LE3BSP_Triangle> triangles);
    
    private:
        static LE3BSP_SplitResult _trianglePlaneIsect(LE3BSP_Hyperplane plane, LE3BSP_Triangle triangle);
    };

    class LE3BSP_Node {
    public:
        LE3BSP_Hyperplane plane;
        std::vector<LE3BSP_Triangle> faces;
        std::shared_ptr<LE3BSP_Node> left, right;
        LE3BSP_Side leftVal, rightVal; // "Pointers" to leaves
        
        LE3BSP_Node(LE3BSP_Hyperplane plane, std::vector<LE3BSP_Triangle> faces);

        void getChildHyperplanes(std::vector<LE3BSP_Hyperplane>& res);
        void toTriangleSoup(std::vector<LE3BSP_Triangle>& res);

        static std::vector<LE3BSP_Triangle> toMesh(std::shared_ptr<LE3BSP_Node> root);
    };

    // Note: face normals should point *inwards*
    std::shared_ptr<LE3BSP_Node> buildBSPT(std::vector<LE3BSP_Triangle> faces);

    LE3BSP_Side classifyPoint(std::shared_ptr<LE3BSP_Node> root, glm::dvec3 point, LE3BSP_Side val = IN);
    LE3BSP_Side classifyTriangle(std::shared_ptr<LE3BSP_Node> root, LE3BSP_Triangle triangle, double epsilon = 0.01);

    enum LE3BSP_CSG_Op {
        UNION, ISECT, DIFF
    };

    std::vector<LE3BSP_Triangle> negateFaces(std::vector<LE3BSP_Triangle> faces);
    std::shared_ptr<LE3BSP_Node> CSGOP(LE3BSP_CSG_Op op, std::shared_ptr<LE3BSP_Node> root, std::vector<LE3BSP_Triangle> faces, LE3BSP_Side val = IN);

    std::vector<LE3BSP_Triangle> getCubeFaces(glm::dvec3 offset, glm::dvec3 extent);
    std::string toSTL(std::vector<LE3BSP_Triangle> soup);
}