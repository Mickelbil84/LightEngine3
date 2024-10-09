#pragma once 

#include "le3_model.h"
#include "le3_primitives.h"

namespace le3 {
    class LE3Sprite : public LE3StaticModel {
    public:
        LE3Sprite(LE3TexturePtr pTexture);
        LE3_TYPE_RETURN(LE3Sprite)

    private:
        LE3TexturePtr m_pTexture;
    };
    using LE3SpritePtr = std::shared_ptr<LE3Sprite>;
}