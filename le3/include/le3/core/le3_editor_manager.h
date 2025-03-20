#pragma once 

#include <functional>

#include "core/le3_object.h"
#include "utils/le3_gizmo.h"

/*
* The editor manager is integrated into the engine systems since some of its methods might also be useful for the game/apps themselves.
*/

namespace le3 {
    struct LE3EditorSelection {
        enum LE3SelectionType {
            LE3_SELECTION_NONE,
            LE3_SELECTION_OBJECT,
            LE3_SELECTION_ASSET_SHADER,
            LE3_SELECTION_ASSET_MATERIAL,
            LE3_SELECTION_ASSET_TEXTURE,
            LE3_SELECTION_ASSET_MESH,
            LE3_SELECTION_ASSET_ANIMATION,
        };

        LE3SelectionType type;
        std::vector<LE3ObjectWeakPtr> pObjects;
        LE3ShaderPtr pShader;
        LE3MaterialPtr pMaterial;
        LE3TexturePtr pTexture;
        LE3StaticMeshPtr pStaticMesh;
        LE3SkeletalMeshPtr pSkeletalMesh;
        std::string animationTrack;

        LE3EditorSelection();
        void reset();

        void deselect();
        void selectObject(LE3ObjectWeakPtr pObject, bool bReset = true);
        void selectAsset(LE3ShaderPtr pShader);
        void selectAsset(LE3MaterialPtr pMaterial);
        void selectAsset(LE3TexturePtr pTexture);
        void selectAsset(LE3StaticMeshPtr pStaticMesh);
        void selectAsset(LE3SkeletalMeshPtr pSkeletalMesh);
        void selectAsset(LE3SkeletalMeshPtr pSkeletalMesh, std::string animationTrack);

        LE3ObjectWeakPtr getLastSelectedObject() {
            if (pObjects.size() == 0) return LE3ObjectWeakPtr();
            return pObjects.back();
        }
        std::vector<std::string> getSelectedObjectsNames() const {
            std::vector<std::string> names;
            for (auto pObjectWeak : pObjects) {
                LE3ObjectPtr pObject = pObjectWeak.lock();
                if (pObject) names.push_back(pObject->getName());
            }
            return names;
        }

        // On select callback
        std::function<void(LE3EditorSelection&)> onSelect;
    };

    class LE3EditorCommand {
    public:
        virtual ~LE3EditorCommand() {}
        virtual void execute() = 0;
        virtual void undo() = 0;
    };
    using LE3EditorCommandPtr = std::unique_ptr<LE3EditorCommand>;

    class LE3EditorCommandStack {
    public:
        void execute(LE3EditorCommandPtr pCommand);
        void undo();
        void redo();
        void reset() {
            m_pCommands.clear();
            m_stackTop = 0;
        }

    private:
        std::vector<LE3EditorCommandPtr> m_pCommands;
        uint16_t m_stackTop = 0;
    };

    struct LE3EditorSnap {
        bool enabled = false;
        float snapTranslation = 0.5f, snapRotation = 15.f, snapScale = 0.1f;
    };

    class LE3EditorManager {
    public:
        LE3EditorManager() {
            reset();
        }
        void reset();

        bool isMouseDown() { return m_bMouseDown; }
        void setMouseDown(bool mouseDown) { m_bMouseDown = mouseDown; }
        bool isCtrlDown() { return m_bCtrlDown; }
        void setCtrlDown(bool ctrlDown) { m_bCtrlDown = ctrlDown; }
        bool isShiftDown() { return m_bShiftDown; }
        void setShiftDown(bool shiftDown) { m_bShiftDown = shiftDown; }
        bool isAltDown() { return m_bAltDown; }
        void setAltDown(bool altDown) { m_bAltDown = altDown; }

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

        LE3EditorSelection& getSelection() { return m_selection; }
        LE3EditorCommandStack& getCommandStack() { return m_commandStack; }

        std::string getSelectedFile() const { return m_selectedFile; }
        void setSelectedFile(std::string path) { m_selectedFile = path; }

        void registerGizmo(LE3GizmoPtr pGizmo) { m_pGizmo = pGizmo; }
        LE3GizmoPtr& getGizmo() { return m_pGizmo; }

        LE3EditorSnap& getSnap() { return m_snap; }

        bool isPauseSceneUpdates() { return m_bPauseSceneUpdates; }
        void setPauseSceneUpdates(bool pauseSceneUpdates) { m_bPauseSceneUpdates = pauseSceneUpdates; }

    private:
        bool m_bMouseDown = false, m_bCtrlDown = false, m_bShiftDown = false, m_bAltDown = false;
        bool m_bActiveEdit = false, m_bEditBlocked = false;
        int m_xrel, m_yrel;

        LE3ObjectWeakPtr m_pHoveredObject;
        LE3GizmoPtr m_pGizmo;
        LE3EditorSelection m_selection;
        LE3EditorSnap m_snap;

        LE3EditorCommandStack m_commandStack;

        bool m_bPauseSceneUpdates = false;

        // Note that this is different than the selected object/asset
        // Can be used for simpler asset creation/loading
        std::string m_selectedFile = ""; 
    };
}