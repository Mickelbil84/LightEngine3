#include "le3_sprite.h"
using namespace le3;

LE3Sprite::LE3Sprite(LE3MaterialPtr pMaterial) : 
    LE3StaticModel(nullptr, pMaterial) {
    m_pMesh = createPlane(0.f, 0.f, 0.f, 1.f, 1.f);
}