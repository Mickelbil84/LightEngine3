#pragma once 

#include "le3_model.h"
#include "le3_primitives.h"

namespace le3 {
    class LE3Sprite : public LE3StaticModel {
    public:
        LE3Sprite(LE3TexturePtr pTexture);
        LE3_TYPE_RETURN(LE3Sprite)

        virtual void draw(LE3ShaderPtr shaderOverride = LE3ShaderPtr());

    private:
        LE3TexturePtr m_pTexture;
        std::shared_ptr<LE3Mesh<LE3Vertex>> m_pMeshData; // See comment in primitives.h (LE3Box)
    };
    using LE3SpritePtr = std::shared_ptr<LE3Sprite>;
}