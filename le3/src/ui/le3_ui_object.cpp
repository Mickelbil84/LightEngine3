#include "ui/le3_ui_object.h"
#include "core/le3_engine_systems.h"
using namespace le3;

LE3UIObject::LE3UIObject() : 
    LE3StaticModel(LE3StaticMeshPtr(), LE3MaterialPtr()) {
    setMaterial(LE3GetAssetManager().getMaterial(DEFAULT_UI_MATERIAL));
    setCastShadow(false);
    getPhysicsComponent().setIsRigidBody(false);
    m_pMesh = LE3GetAssetManager().getUIMesh();
    setDrawPriority(DRAW_PRIORITY_UI);
}

void LE3UIObject::draw(LE3ShaderPtr shaderOverride) {
    if (shaderOverride.lock()) return;
    m_pMaterial.lock()->bUseDiffuseTexture = false;

    shaderOverride = m_pMaterial.lock()->shader;

    if (shaderOverride.lock()) {
        shaderOverride.lock()->use();
    }
    LE3StaticModel::draw(shaderOverride);
    if (shaderOverride.lock()) {
        shaderOverride.lock()->use();
    }
}
