#pragma once

#include "le3_model.h"
#include "le3_geometry.h"

#include <fmt/core.h>

namespace le3 {
    LE3MeshPtr<LE3Vertex3p3c> createHelloOpenGLTriangle();
    LE3ScreenRectPtr createScreenRect();
    LE3MeshPtr<LE3Vertex> createBox(float x0, float y0, float z0, float width, float height, float depth);
    LE3MeshPtr<LE3Vertex> createCylinder(float x0, float y0, float z0, float radius, float height, int resolution, bool withCaps = true);
    LE3MeshPtr<LE3Vertex> createCone(float x0, float y0, float z0, float radius, float height, int resolution, bool withCaps = true);
    
    LE3MeshPtr<LE3Vertex> createGizmoArrow();
    LE3MeshPtr<LE3Vertex> createGizmoCenter();

    LE3MeshPtr<LE3Vertex3p> createDebugLine();
    LE3MeshPtr<LE3Vertex3p> createDebugBox();
    LE3MeshPtr<LE3Vertex3p> createDebugCylinder();
    LE3MeshPtr<LE3Vertex3p> createDebugCone();


    std::vector<LE3Vertex> _createCylinderBuffer(float x0, float y0, float z0, float radius, float height, int resolution, bool withCaps);
    std::vector<LE3Vertex> _createConeBuffer(float x0, float y0, float z0, float radius, float height, int resolution, bool withCaps);


    class LE3Box : public LE3StaticModel {
    public:
        LE3Box(float x0, float y0, float z0, float width, float height, float depth, LE3MaterialPtr pMaterial) : 
            LE3StaticModel(nullptr, pMaterial) {
            rebuild(x0, y0, z0, width, height, depth);
        }

        inline float getX0() const { return x0; }
        inline float getY0() const { return y0; }
        inline float getZ0() const { return z0; }
        inline float getWidth() const { return width; }
        inline float getHeight() const { return height; }
        inline float getDepth() const { return depth; }

        void rebuild(float x0, float y0, float z0, float width, float height, float depth) {
            this->x0 = x0; this->y0 = y0; this->z0 = z0;
            this->width = width; this->height = height; this->depth = depth;
            m_pMesh = createBox(x0, y0, z0, width, height, depth);
        }

    protected:
        float x0, y0, z0;
        float width, height, depth;
    };
    using LE3BoxPtr = std::shared_ptr<LE3Box>;

    class LE3Cylinder : public LE3StaticModel {
    public:
        LE3Cylinder(float x0, float y0, float z0, float radius, float height, int resolution, bool withCaps, LE3MaterialPtr pMaterial) :
            LE3StaticModel(nullptr, pMaterial) {
            fmt::print("radius {} | height {} | resolution {}\n", radius, height, resolution);
            rebuild(x0, y0, z0, radius, height, resolution, withCaps);
        }

        inline float getX0() const { return x0; }
        inline float getY0() const { return y0; }
        inline float getZ0() const { return z0; }
        inline float getHeight() const { return height; }
        inline float getRadius() const { return radius; }
        inline int getResolution() const { return resolution; }
        inline bool getWithCaps() const { return withCaps; }

        void rebuild(float x0, float y0, float z0, float radius, float height, int resolution, bool withCaps) {
            this->x0 = x0; this->y0 = y0; this->z0 = z0;
            this->radius = radius; this->height = height; this->resolution = resolution;
            m_pMesh = createCylinder(x0, y0, z0, radius, height, resolution, withCaps);
        }
    
    protected:
        float x0, y0, z0;
        float radius, height;
        int resolution;
        bool withCaps;
    };
    using LE3CylinderPtr = std::shared_ptr<LE3Cylinder>;

    class LE3Cone : public LE3StaticModel {
    public:
        LE3Cone(float x0, float y0, float z0, float radius, float height, int resolution, bool withCaps, LE3MaterialPtr pMaterial) :
            LE3StaticModel(nullptr, pMaterial) {
            fmt::print("radius {} | height {} | resolution {}\n", radius, height, resolution);
            rebuild(x0, y0, z0, radius, height, resolution, withCaps);
        }

        inline float getX0() const { return x0; }
        inline float getY0() const { return y0; }
        inline float getZ0() const { return z0; }
        inline float getHeight() const { return height; }
        inline float getRadius() const { return radius; }
        inline int getResolution() const { return resolution; }
        inline bool getWithCaps() const { return withCaps; }

        void rebuild(float x0, float y0, float z0, float radius, float height, int resolution, bool withCaps) {
            this->x0 = x0; this->y0 = y0; this->z0 = z0;
            this->radius = radius; this->height = height; this->resolution = resolution;
            m_pMesh = createCone(x0, y0, z0, radius, height, resolution, withCaps);
        }
    
    protected:
        float x0, y0, z0;
        float radius, height;
        int resolution;
        bool withCaps;
    };
    using LE3ConePtr = std::shared_ptr<LE3Cone>;
};