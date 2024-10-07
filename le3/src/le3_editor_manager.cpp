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
    pStaticModel = nullptr;
    pSkeletalModel = nullptr;
}

void LE3EditorSelection::deselect() {
    reset();
}
void LE3EditorSelection::selectObject(LE3ObjectWeakPtr pObject) {
    reset();
    type = LE3SelectionType::LE3_SELECTION_OBJECT;
    this->pObject = pObject;
    this->onSelect(*this);
}
void LE3EditorSelection::selectAsset(LE3ShaderPtr pShader) {
    reset();
    type = LE3SelectionType::LE3_SELECTION_ASSET_SHADER;
    this->pShader = pShader;
    this->onSelect(*this);
}
void LE3EditorSelection::selectAsset(LE3MaterialPtr pMaterial) {
    reset();
    type = LE3SelectionType::LE3_SELECTION_ASSET_MATERIAL;
    this->pMaterial = pMaterial;
    this->onSelect(*this);
}
void LE3EditorSelection::selectAsset(LE3TexturePtr pTexture) {
    reset();
    type = LE3SelectionType::LE3_SELECTION_ASSET_TEXTURE;
    this->pTexture = pTexture;
    this->onSelect(*this);
}
void LE3EditorSelection::selectAsset(LE3StaticModelPtr pStaticModel) {
    reset();
    type = LE3SelectionType::LE3_SELECTION_ASSET_MODEL;
    this->pStaticModel = pStaticModel;
    this->onSelect(*this);
}
void LE3EditorSelection::selectAsset(LE3SkeletalModelPtr pSkeletalModel) {
    reset();
    type = LE3SelectionType::LE3_SELECTION_ASSET_MODEL;
    this->pSkeletalModel = pSkeletalModel;
    this->onSelect(*this);
}