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
    enum LE3GizmoState {
        LE3_GIZMO_STATE_DISABLED = 0,
        LE3_GIZMO_STATE_IDLE = 1,
        LE3_GIZMO_STATE_DRAGGING = 2,
        LE3_GIZMO_STATE_RELEASE = 3,
    };
    enum LE3GizmoMode {
        LE3_GIZMO_MODE_SELECT = 0,
        LE3_GIZMO_MODE_TRANSLATE = 1,
        LE3_GIZMO_MODE_ROTATE = 2,
        LE3_GIZMO_MODE_SCALE = 3,
    };

    class LE3Gizmo : public LE3DrawableObject {
    public:
        LE3Gizmo();
        LE3_TYPE_RETURN(LE3Gizmo)
        
        void draw(LE3ShaderPtr shaderOverride);    
        void update(float deltaTime);
        void preUpdate();
        void postUpdate();

        void setHoverable(bool hoverable) { m_bIsHoverable = hoverable; }  
        void setDynamicScale(bool dynamicScale) { m_bIsDynamicScale = dynamicScale; } 

        void onObjectSelected(LE3ObjectWeakPtr pObject);

        void setMode(LE3GizmoMode mode) { m_mode = mode; m_state = LE3_GIZMO_STATE_IDLE; }

    private:

        void drawModeSelect(LE3ShaderPtr shaderOverride);
        void drawModeTranslate(LE3ShaderPtr shaderOverride);
        void drawModeRotate(LE3ShaderPtr shaderOverride);
        void drawModeScale(LE3ShaderPtr shaderOverride);

        void updateStateDisabled(float deltaTime);
        void updateStateIdle(float deltaTime);
        void updateStateDragging(float deltaTime);
        void updateStateRelease(float deltaTime);

        bool isMouseDown();
        LE3GizmoAxis getHoveredAxis();
        LE3GizmoAxis getHoveredAxisTranslateScale(glm::mat4 projViewMatrix, glm::vec2 cursorPosition);
        LE3GizmoAxis getHoveredAxisRotate(glm::mat4 projViewMatrix, glm::vec2 cursorPosition);

        LE3GizmoMode m_mode;
        LE3GizmoState m_state;
        LE3GizmoAxis m_hoveredAxis;
        
        bool m_bIsHoverable = true, m_bIsDynamicScale = true;
        
        glm::mat4 m_selectObjectInitialTransform, m_selectGizmoInitialTransform;
        LE3ObjectWeakPtr m_pSelectedObject; // To verify that we track the correct object

        int m_dragFrames = 0;
        glm::vec3 m_dragDelta;

        glm::vec3 getAxisLine(LE3GizmoAxis axis);
        void getAxisScreen(LE3GizmoAxis axis, glm::vec2& base, glm::vec2& tip);
        float distanceToLineAxis(glm::vec2 point, LE3GizmoAxis axis);

        glm::mat4 gizmoTransform(LE3GizmoAxis gizmoAxis);
    };
    using LE3GizmoPtr = std::shared_ptr<LE3Gizmo>;
}