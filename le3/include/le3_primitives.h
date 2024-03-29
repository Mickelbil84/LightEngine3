#pragma once

#include "le3_model.h"
#include "le3_geometry.h"

namespace le3 {
    LE3MeshPtr<LE3Vertex3p3c> createHelloOpenGLTriangle();
    LE3ScreenRectPtr createScreenRect();
    LE3MeshPtr<LE3Vertex> createBox(float x0, float y0, float z0, float width, float height, float depth);

    LE3MeshPtr<LE3Vertex3p> createDebugLine();
    LE3MeshPtr<LE3Vertex3p> createDebugBox();

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
};