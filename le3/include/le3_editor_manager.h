#pragma once 

#include "le3_object.h"
#include "le3_gizmo.h"

namespace le3 {
    class LE3EditorManager {
    public:
        bool isMouseDown() { return m_bMouseDown; }
        void setMouseDown(bool mouseDown) { m_bMouseDown = mouseDown; }

        // Active edit is when something is being modified, and animations/camera movement/etc. should be frozen
        bool isActiveEdit() { return m_bActiveEdit; }
        void setActiveEdit(bool activeEdit) { m_bActiveEdit = activeEdit; }
        bool isEditBlocked() { return m_bEditBlocked; }
        void setEditBlocked(bool editBlocked) { m_bEditBlocked = editBlocked; }

        void setMouseRel(int xrel, int yrel) { m_xrel = xrel; m_yrel = yrel; }
        int getMouseRelX() { return m_xrel; }
        int getMouseRelY() { return m_yrel; }

        LE3ObjectPtr getHoveredObject() { return m_pHoveredObject; }
        void setHoveredObject(LE3ObjectPtr hoveredObject) { m_pHoveredObject = hoveredObject; }

        LE3ObjectPtr getSelectedObject() { return m_pSelectedObject; }
        void setSelectedObject() { 
            m_pSelectedObject = m_pHoveredObject; 
            if (m_pGizmo) m_pGizmo->onObjectSelected(m_pSelectedObject); 
        }

        void registerGizmo(LE3GizmoPtr pGizmo) { m_pGizmo = pGizmo; }

    private:
        bool m_bMouseDown = false;
        bool m_bActiveEdit = false, m_bEditBlocked = false;
        int m_xrel, m_yrel;

        LE3ObjectPtr m_pHoveredObject = nullptr, m_pSelectedObject = nullptr;
        LE3GizmoPtr m_pGizmo;
    };
}