#pragma once 

#include "le3_object.h"
#include "le3_gizmo.h"

namespace le3 {
    struct LE3EditorSelection {
        enum LE3SelectionType {
            LE3_SELECTION_NONE,
            LE3_SELECTION_OBJECT,
            LE3_SELECTION_ASSET_SHADER,
            LE3_SELECTION_ASSET_MATERIAL,
            LE3_SELECTION_ASSET_TEXTURE,
            LE3_SELECTION_ASSET_MODEL,
        };

        LE3SelectionType type;
        LE3ObjectWeakPtr pObject;
        LE3ShaderPtr pShader;
        LE3MaterialPtr pMaterial;
        LE3TexturePtr pTexture;
        LE3StaticModelPtr pStaticModel;
        LE3SkeletalModelPtr pSkeletalModel;

        LE3EditorSelection();
        void reset();

        void deselect();
        void selectObject(LE3ObjectWeakPtr pObject);
        void selectAsset(LE3ShaderPtr pShader);
        void selectAsset(LE3MaterialPtr pMaterial);
        void selectAsset(LE3TexturePtr pTexture);
        void selectAsset(LE3StaticModelPtr pStaticModel);
        void selectAsset(LE3SkeletalModelPtr pSkeletalModel);

        // On select callback
        std::function<void(LE3EditorSelection&)> onSelect;
    };

    class LE3EditorManager {
    public:
        LE3EditorManager() {
            m_selection.onSelect = [this](LE3EditorSelection& selection) {
                if (m_pGizmo) m_pGizmo->onObjectSelected(selection.pObject);
            };
        }

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

        LE3ObjectWeakPtr getHoveredObject() { return m_pHoveredObject; }
        void setHoveredObject(LE3ObjectWeakPtr hoveredObject) { m_pHoveredObject = hoveredObject; }

        // LE3ObjectWeakPtr getSelectedObject() { return m_pSelectedObject; }
        // void setSelectedObject() { 
        //     setSelectedObject(m_pHoveredObject); 
        // }
        // void setSelectedObject(LE3ObjectWeakPtr selectedObject) { 
        //     m_pSelectedObject = selectedObject; 
        //     m_pHoveredObject.reset();
        //     if (m_pGizmo) m_pGizmo->onObjectSelected(m_pSelectedObject); 
        // }

        LE3EditorSelection& getSelection() { return m_selection; }

        std::string getSelectedFile() const { return m_selectedFile; }
        void setSelectedFile(std::string path) { m_selectedFile = path; }

        void registerGizmo(LE3GizmoPtr pGizmo) { m_pGizmo = pGizmo; }

    private:
        bool m_bMouseDown = false;
        bool m_bActiveEdit = false, m_bEditBlocked = false;
        int m_xrel, m_yrel;

        LE3ObjectWeakPtr m_pHoveredObject;
        LE3GizmoPtr m_pGizmo;
        LE3EditorSelection m_selection;

        // Note that this is different than the selected object/asset
        // Can be used for simpler asset creation/loading
        std::string m_selectedFile = ""; 
    };
}