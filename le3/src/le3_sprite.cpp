#include "le3_sprite.h"
#include "le3_engine_systems.h"
using namespace le3;

LE3Sprite::LE3Sprite(LE3TexturePtr pTexture) : 
    LE3StaticModel(nullptr, nullptr), m_pTexture(pTexture) {
    setMaterial(LE3GetAssetManager().getMaterial(DEFAULT_SPRITE_MATERIAL));
    setMaterialName(DEFAULT_SPRITE_MATERIAL);
    m_pMesh = createPlane(0.f, 0.f, 0.f, 1.f, 1.f);
}