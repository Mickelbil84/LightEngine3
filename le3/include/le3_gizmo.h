#pragma once

#include "le3_model.h"
#include "le3_drawable_object.h"

namespace le3 {
    enum LE3GizmoAxis {
        LE3_GIZMO_AXIS_X = 0,
        LE3_GIZMO_AXIS_Y = 1,
        LE3_GIZMO_AXIS_Z = 2,
        LE3_GIZMO_AXIS_ALL = 3,
        LE3_GIZMO_AXIS_NONE = 4,
    };

    class LE3Gizmo : public LE3DrawableObject {
    public:
        LE3Gizmo();
        void draw(LE3ShaderPtr shaderOverride);    
        void update(float deltaTime);

    private:
        LE3GizmoAxis m_hoveredAxis;
    };
    using LE3GizmoPtr = std::shared_ptr<LE3Gizmo>;
}