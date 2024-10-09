#include "le3_editor_manager.h"
using namespace le3;


LE3EditorSelection::LE3EditorSelection() {
    reset();
}
void LE3EditorSelection::reset() {
    type = LE3SelectionType::LE3_SELECTION_NONE;
    pObject.reset();
    pShader = nullptr;
    pMaterial = nullptr;
    pTexture = nullptr;
    pStaticMesh = nullptr;
    pSkeletalMesh = nullptr;
    animationTrack = "";
}

void LE3EditorSelection::deselect() {
    reset();
}
void LE3EditorSelection::selectObject(LE3ObjectWeakPtr pObjectWeak) {
    reset();
    LE3ObjectPtr pObject = pObjectWeak.lock();
    if (!pObject) return;

    while (pObject->isDelegate()) {
        pObject = pObject->getParent();
    }

    type = LE3SelectionType::LE3_SELECTION_OBJECT;
    this->pObject = pObject;
    this->onSelect(*this);
}
void LE3EditorSelection::selectAsset(LE3ShaderPtr pShader) {
    reset();
    if (!pShader) return;
    type = LE3SelectionType::LE3_SELECTION_ASSET_SHADER;
    this->pShader = pShader;
    this->onSelect(*this);
}
void LE3EditorSelection::selectAsset(LE3MaterialPtr pMaterial) {
    reset();
    if (!pMaterial) return;
    type = LE3SelectionType::LE3_SELECTION_ASSET_MATERIAL;
    this->pMaterial = pMaterial;
    this->onSelect(*this);
}
void LE3EditorSelection::selectAsset(LE3TexturePtr pTexture) {
    reset();
    if (!pTexture) return;
    type = LE3SelectionType::LE3_SELECTION_ASSET_TEXTURE;
    this->pTexture = pTexture;
    this->onSelect(*this);
}
void LE3EditorSelection::selectAsset(LE3StaticMeshPtr pStaticMesh) {
    reset();
    if (!pStaticMesh) return;
    type = LE3SelectionType::LE3_SELECTION_ASSET_MESH;
    this->pStaticMesh = pStaticMesh;
    this->onSelect(*this);
}
void LE3EditorSelection::selectAsset(LE3SkeletalMeshPtr pSkeletalMesh) {
    reset();
    if (!pSkeletalMesh) return;
    type = LE3SelectionType::LE3_SELECTION_ASSET_MESH;
    this->pSkeletalMesh = pSkeletalMesh;
    this->onSelect(*this);
}

void LE3EditorSelection::selectAsset(LE3SkeletalMeshPtr pSkeletalMesh, std::string animationTrack) {
    reset();
    if (!pSkeletalMesh) return;
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
}
void LE3EditorCommandStack::undo() {
    if (m_stackTop == 0) return;
    m_pCommands[m_stackTop - 1]->undo();
    m_stackTop--;
}
void LE3EditorCommandStack::redo() {
    if (m_stackTop == m_pCommands.size()) return;
    m_pCommands[m_stackTop]->execute();
    m_stackTop++;
}