#pragma once

#include "graphics/le3_model.h"
#include "graphics/le3_geometry.h"

#include <iterator>
#include <algorithm>

#include <fmt/core.h>

namespace le3 {
    std::shared_ptr<LE3Mesh<LE3Vertex3p3c>> createHelloOpenGLTriangle();
    std::shared_ptr<LE3ScreenRect> createScreenRect();
    std::shared_ptr<LE3Mesh<LE3Vertex>> createPlane(float x0, float y0, float z0, float width, float height);
    std::shared_ptr<LE3Mesh<LE3Vertex>> createBox(float x0, float y0, float z0, float width, float height, float depth);
    std::shared_ptr<LE3Mesh<LE3Vertex>> createCylinder(float x0, float y0, float z0, float radius, float height, int resolution, bool withCaps = true);
    std::shared_ptr<LE3Mesh<LE3Vertex>> createCone(float x0, float y0, float z0, float radius, float height, int resolution, bool withCaps = true);
    std::shared_ptr<LE3Mesh<LE3Vertex>> createTorus(float x0, float y0, float z0, float majorRadius, float minorRadius, int resolution);
    std::shared_ptr<LE3Mesh<LE3Vertex>> createSphere(float x0, float y0, float z0, float radius, int resolution);
    
    std::shared_ptr<LE3Mesh<LE3Vertex>> createGizmoArrow();
    std::shared_ptr<LE3Mesh<LE3Vertex>> createGizmoScaleArrow();
    std::shared_ptr<LE3Mesh<LE3Vertex>> createGizmoCircle();
    std::shared_ptr<LE3Mesh<LE3Vertex>> createGizmoPlane();
    std::shared_ptr<LE3Mesh<LE3Vertex>> createGizmoCenter();

    std::shared_ptr<LE3Mesh<LE3Vertex3p>> createDebugLine();
    std::shared_ptr<LE3Mesh<LE3Vertex3p>> createDebugBox();
    std::shared_ptr<LE3Mesh<LE3Vertex3p>> createDebugBoxDiagonals();
    std::shared_ptr<LE3Mesh<LE3Vertex3p>> createDebugCylinder();
    std::shared_ptr<LE3Mesh<LE3Vertex3p>> createDebugCone();
    std::shared_ptr<LE3Mesh<LE3Vertex3p>> createDebugSphere();
    std::shared_ptr<LE3Mesh<LE3Vertex3p>> createDebugCapsule();

    std::vector<LE3Vertex> _createPlaneBuffer(float x0, float y0, float z0, float width, float height);
    std::vector<LE3Vertex> _createBoxBuffer(float x0, float y0, float z0, float width, float height, float depth);
    std::vector<LE3Vertex> _createCylinderBuffer(float x0, float y0, float z0, float radius, float height, int resolution, bool withCaps);
    std::vector<LE3Vertex> _createConeBuffer(float x0, float y0, float z0, float radius, float height, int resolution, bool withCaps);
    std::vector<LE3Vertex> _createTorusBuffer(float x0, float y0, float z0, float majorRadius, float minorRadius, int resolution);
    std::vector<LE3Vertex> _createSphereBuffer(float x0, float y0, float z0, float radius, int resolution, int hemisphere=0);


    class LE3Box : public LE3StaticModel {
    public:
        LE3Box(float x0, float y0, float z0, float width, float height, float depth, LE3MaterialPtr pMaterial) : 
            LE3StaticModel(LE3StaticMeshPtr(), pMaterial) {
            rebuild(x0, y0, z0, width, height, depth);
        }
        LE3_TYPE_RETURN(LE3Box)

        inline float getX0() const { return x0; }
        inline float getY0() const { return y0; }
        inline float getZ0() const { return z0; }
        inline float getWidth() const { return width; }
        inline float getHeight() const { return height; }
        inline float getDepth() const { return depth; }

        inline glm::vec3 getBoxPosition() const { return glm::vec3(x0, y0, z0); } 
        inline glm::vec3 getBoxExtent() const { return glm::vec3(width, height, depth); }

        void rebuild(float x0, float y0, float z0, float width, float height, float depth) {
            this->x0 = x0; this->y0 = y0; this->z0 = z0;
            this->width = width; this->height = height; this->depth = depth;
            m_pMeshData = createBox(x0, y0, z0, width, height, depth);
            m_pMesh = m_pMeshData;
        }

    protected:
        float x0, y0, z0;
        float width, height, depth;
        std::shared_ptr<LE3Mesh<LE3Vertex>> m_pMeshData; // At least one object needs to point to the mesh data
    };
    using LE3BoxPtr = std::shared_ptr<LE3Box>;

    class LE3Cylinder : public LE3StaticModel {
    public:
        LE3Cylinder(float x0, float y0, float z0, float radius, float height, int resolution, bool withCaps, LE3MaterialPtr pMaterial) :
            LE3StaticModel(LE3StaticMeshPtr(), pMaterial) {
            rebuild(x0, y0, z0, radius, height, resolution, withCaps);
        }
        LE3_TYPE_RETURN(LE3Cylinder)

        inline float getX0() const { return x0; }
        inline float getY0() const { return y0; }
        inline float getZ0() const { return z0; }
        inline float getHeight() const { return height; }
        inline float getRadius() const { return radius; }
        inline int getResolution() const { return resolution; }
        inline bool getWithCaps() const { return withCaps; }

        void rebuild(float x0, float y0, float z0, float radius, float height, int resolution, bool withCaps) {
            this->x0 = x0; this->y0 = y0; this->z0 = z0;
            this->radius = radius; this->height = height; this->resolution = resolution; this->withCaps = withCaps;
            m_pMeshData = createCylinder(x0, y0, z0, radius, height, resolution, withCaps);
            m_pMesh = m_pMeshData;
        }
    
    protected:
        float x0, y0, z0;
        float radius, height;
        int resolution;
        bool withCaps;
        std::shared_ptr<LE3Mesh<LE3Vertex>> m_pMeshData;
    };
    using LE3CylinderPtr = std::shared_ptr<LE3Cylinder>;

    class LE3Cone : public LE3StaticModel {
    public:
        LE3Cone(float x0, float y0, float z0, float radius, float height, int resolution, bool withCaps, LE3MaterialPtr pMaterial) :
            LE3StaticModel(LE3StaticMeshPtr(), pMaterial) {
            rebuild(x0, y0, z0, radius, height, resolution, withCaps);
        }
        LE3_TYPE_RETURN(LE3Cone)

        inline float getX0() const { return x0; }
        inline float getY0() const { return y0; }
        inline float getZ0() const { return z0; }
        inline float getHeight() const { return height; }
        inline float getRadius() const { return radius; }
        inline int getResolution() const { return resolution; }
        inline bool getWithCaps() const { return withCaps; }

        void rebuild(float x0, float y0, float z0, float radius, float height, int resolution, bool withCaps) {
            this->x0 = x0; this->y0 = y0; this->z0 = z0;
            this->radius = radius; this->height = height; this->resolution = resolution; this->withCaps = withCaps;
            m_pMeshData = createCone(x0, y0, z0, radius, height, resolution, withCaps);
            m_pMesh = m_pMeshData;
        }
    
    protected:
        float x0, y0, z0;
        float radius, height;
        int resolution;
        bool withCaps;
        std::shared_ptr<LE3Mesh<LE3Vertex>> m_pMeshData;
    };
    using LE3ConePtr = std::shared_ptr<LE3Cone>;

    class LE3Torus : public LE3StaticModel {
    public:
        LE3Torus(float x0, float y0, float z0, float majorRadius, float minorRadius, int resolution, LE3MaterialPtr pMaterial) :
            LE3StaticModel(LE3StaticMeshPtr(), pMaterial) {
            rebuild(x0, y0, z0, majorRadius, minorRadius, resolution);
        }
        LE3_TYPE_RETURN(LE3Torus)

        inline float getX0() const { return x0; }
        inline float getY0() const { return y0; }
        inline float getZ0() const { return z0; }
        inline float getMajorRadius() const { return majorRadius; }
        inline float getMinorRadius() const { return minorRadius; }
        inline int getResolution() const { return resolution; }

        void rebuild(float x0, float y0, float z0, float majorRadius, float minorRadius, int resolution) {
            this->x0 = x0; this->y0 = y0; this->z0 = z0;
            this->majorRadius = majorRadius; this->minorRadius = minorRadius; this->resolution = resolution;
            m_pMeshData = createTorus(x0, y0, z0, majorRadius, minorRadius, resolution);
            m_pMesh = m_pMeshData;
        }

    protected:
        float x0, y0, z0;
        float majorRadius, minorRadius;
        int resolution;
        std::shared_ptr<LE3Mesh<LE3Vertex>> m_pMeshData;
    };
    using LE3TorusPtr = std::shared_ptr<LE3Torus>;

    class LE3Sphere : public LE3StaticModel {
    public:
        LE3Sphere(float x0, float y0, float z0, float radius, int resolution, LE3MaterialPtr pMaterial) :
            LE3StaticModel(LE3StaticMeshPtr(), pMaterial) {
            rebuild(x0, y0, z0, radius, resolution);
        }
        LE3_TYPE_RETURN(LE3Sphere)

        inline float getX0() const { return x0; }
        inline float getY0() const { return y0; }
        inline float getZ0() const { return z0; }
        inline float getRadius() const { return radius; }
        inline int getResolution() const { return resolution; }

        void rebuild(float x0, float y0, float z0, float radius, int resolution) {
            this->x0 = x0; this->y0 = y0; this->z0 = z0;
            this->radius = radius; this->resolution = resolution;
            m_pMeshData = createSphere(x0, y0, z0, radius, resolution);
            m_pMesh = m_pMeshData;
        }
    
    protected:
        float x0, y0, z0;
        float radius;
        int resolution;
        std::shared_ptr<LE3Mesh<LE3Vertex>> m_pMeshData;
    };
    using LE3SpherePtr = std::shared_ptr<LE3Sphere>;
};