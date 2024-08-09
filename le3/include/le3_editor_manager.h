#pragma once 

namespace le3 {
    class LE3EditorManager {
    public:
        bool isMouseDown() { return m_bMouseDown; }
        void setMouseDown(bool mouseDown) { m_bMouseDown = mouseDown; }

        // Active edit is when something is being modified, and animations/camera movement/etc. should be frozen
        bool isActiveEdit() { return m_bActiveEdit; }
        void setActiveEdit(bool activeEdit) { m_bActiveEdit = activeEdit; }

    private:
        bool m_bMouseDown = false;
        bool m_bActiveEdit = false;
    };
}