#pragma once

#include "le3_geometry.h"

namespace le3 {
    LE3MeshPtr<LE3Vertex3p3c> createHelloOpenGLTriangle();

    LE3MeshPtr<LE3Vertex> createBox(float x0, float y0, float z0, float width, float height, float depth);
};