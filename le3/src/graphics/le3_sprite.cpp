#include "graphics/le3_sprite.h"
#include "core/le3_engine_systems.h"
using namespace le3;

LE3Sprite::LE3Sprite(LE3TexturePtr pTexture) : 
    LE3StaticModel(LE3StaticMeshPtr(), LE3MaterialPtr()), m_pTexture(pTexture) {
    setMaterial(LE3GetAssetManager().getMaterial(DEFAULT_SPRITE_MATERIAL));
    setCastShadow(false);
    setHidden(true);
    getPhysicsComponent().setIsRigidBody(false);
    m_pMeshData = createPlane(0.f, 0.f, 0.f, 1.f, 1.f);
    m_pMesh = m_pMeshData;
}

void LE3Sprite::draw(LE3ShaderPtr shaderOverride) {
    if (shaderOverride.lock()) return;

    m_pMaterial.lock()->diffuseTexture = m_pTexture;
    m_pMaterial.lock()->bUseDiffuseTexture = true;

    if (!shaderOverride.lock()) shaderOverride = m_pMaterial.lock()->shader;

    if (shaderOverride.lock()) {
        shaderOverride.lock()->use();
        shaderOverride.lock()->uniform("isBillboard", (unsigned int)1);
    }
    LE3StaticModel::draw(shaderOverride);
    if (shaderOverride.lock()) {
        shaderOverride.lock()->use();
        shaderOverride.lock()->uniform("isBillboard", (unsigned int)0);
    }
}