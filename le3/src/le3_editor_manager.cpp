#include "le3_editor_manager.h"
#include "le3_engine_systems.h"
using namespace le3;


LE3EditorSelection::LE3EditorSelection() {
    reset();
}
void LE3EditorSelection::reset() {
    type = LE3SelectionType::LE3_SELECTION_NONE;
    pObjects.clear();
    pShader.reset();
    pMaterial.reset();
    pTexture.reset();
    pStaticMesh.reset();
    pSkeletalMesh.reset();
    animationTrack = "";
}

void LE3EditorSelection::deselect() {
    reset();
}
void LE3EditorSelection::selectObject(LE3ObjectWeakPtr pObjectWeak, bool bReset) {
    if (bReset) reset();
    else {
        std::vector<LE3ObjectWeakPtr> tmp(pObjects);
        reset();
        pObjects = tmp;
    }
    LE3ObjectPtr pObject = pObjectWeak.lock();
    if (!pObject) return;

    while (pObject->isDelegate()) {
        pObject = pObject->getParent();
    }

    type = LE3SelectionType::LE3_SELECTION_OBJECT;
    bool shouldPush = true;
    for (auto pObjectWeak : pObjects) {
        if (pObjectWeak.lock() == pObject) {
            shouldPush = false;
            break;
        }
    }
    if (shouldPush) pObjects.push_back(pObject);
    this->onSelect(*this);
}
void LE3EditorSelection::selectAsset(LE3ShaderPtr pShader) {
    reset();
    if (!pShader.lock()) return;
    type = LE3SelectionType::LE3_SELECTION_ASSET_SHADER;
    this->pShader = pShader;
    this->onSelect(*this);
}
void LE3EditorSelection::selectAsset(LE3MaterialPtr pMaterial) {
    reset();
    if (!pMaterial.lock()) return;
    type = LE3SelectionType::LE3_SELECTION_ASSET_MATERIAL;
    this->pMaterial = pMaterial;
    this->onSelect(*this);
}
void LE3EditorSelection::selectAsset(LE3TexturePtr pTexture) {
    reset();
    if (!pTexture.lock()) return;
    type = LE3SelectionType::LE3_SELECTION_ASSET_TEXTURE;
    this->pTexture = pTexture;
    this->onSelect(*this);
}
void LE3EditorSelection::selectAsset(LE3StaticMeshPtr pStaticMesh) {
    reset();
    if (!pStaticMesh.lock()) return;
    type = LE3SelectionType::LE3_SELECTION_ASSET_MESH;
    this->pStaticMesh = pStaticMesh;
    this->onSelect(*this);
}
void LE3EditorSelection::selectAsset(LE3SkeletalMeshPtr pSkeletalMesh) {
    reset();
    if (!pSkeletalMesh.lock()) return;
    type = LE3SelectionType::LE3_SELECTION_ASSET_MESH;
    this->pSkeletalMesh = pSkeletalMesh;
    this->onSelect(*this);
}

void LE3EditorSelection::selectAsset(LE3SkeletalMeshPtr pSkeletalMesh, std::string animationTrack) {
    reset();
    if (!pSkeletalMesh.lock()) return;
    type = LE3SelectionType::LE3_SELECTION_ASSET_ANIMATION;
    this->pSkeletalMesh = pSkeletalMesh;
    this->animationTrack = animationTrack;
    this->onSelect(*this);
}

void LE3EditorCommandStack::execute(LE3EditorCommandPtr pCommand) {
    if (m_stackTop < m_pCommands.size()) m_pCommands.resize(m_stackTop);
    m_pCommands.push_back(std::move(pCommand));
    m_pCommands.back()->execute();
    m_stackTop++;
    LE3GetEventManager().notify("OnSceneChange", nullptr);
}
void LE3EditorCommandStack::undo() {
    if (m_stackTop == 0) return;
    m_pCommands[m_stackTop - 1]->undo();
    m_stackTop--;
    LE3GetEventManager().notify("OnSceneChange", nullptr);
}
void LE3EditorCommandStack::redo() {
    if (m_stackTop == m_pCommands.size()) return;
    m_pCommands[m_stackTop]->execute();
    m_stackTop++;
    LE3GetEventManager().notify("OnSceneChange", nullptr);
}

void LE3EditorManager::reset() {
    m_selection.onSelect = [this](LE3EditorSelection& selection) {
    };

    m_bMouseDown = false; m_bCtrlDown = false; m_bShiftDown = false; m_bAltDown = false;
    m_bActiveEdit = false; m_bEditBlocked = false;
    m_xrel = 0; m_yrel = 0;

    m_pHoveredObject.reset();
    m_pGizmo = nullptr;
    m_selection.reset();
    m_snap = LE3EditorSnap();
    m_commandStack.reset();
    m_bPauseSceneUpdates = false;
    m_selectedFile = "";
}