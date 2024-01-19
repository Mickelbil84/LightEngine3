#pragma once

#include "le3_geometry.h"

namespace le3 {
    LE3MeshPtr<LE3Vertex3p3c> CreateHelloOpenGLTriangle();

    LE3MeshPtr<LE3Vertex> CreateBox(float x0, float y0, float z0, float width, float height, float depth);
};