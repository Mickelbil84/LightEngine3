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
        void preUpdate();
        void postUpdate();

        void setHoverable(bool hoverable) { m_bIsHoverable = hoverable; }  
        void setDynamicScale(bool dynamicScale) { m_bIsDynamicScale = dynamicScale; } 

        void onObjectSelected(LE3ObjectPtr pObject);

    private:
        LE3GizmoAxis m_hoveredAxis;
        int m_hoveredCnt;
        bool m_bIsHoverable = true, m_bIsDynamicScale = true;
        
        glm::mat4 m_selectObjectInitialTransform, m_selectGizmoInitialTransform;
        LE3ObjectPtr m_pSelectedObject; // To verify that we track the correct object


        bool m_bIsDragging = false;
        int m_dragStartX, m_dragStartY;
        glm::vec3 m_dragStartPos;

        glm::vec3 getAxisLine(LE3GizmoAxis axis);
        void getAxisScreen(LE3GizmoAxis axis, glm::vec2& base, glm::vec2& tip);
        float distanceToLineAxis(glm::vec2 point, LE3GizmoAxis axis);

        glm::mat4 gizmoTransform(LE3GizmoAxis gizmoAxis);
    };
    using LE3GizmoPtr = std::shared_ptr<LE3Gizmo>;
}