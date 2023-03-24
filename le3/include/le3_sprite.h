#pragma once

#include "le3_static_mesh.h"

class LE3Sprite : public LE3Object
{
public:
    LE3Sprite(std::string name="", LE3Material* material=nullptr, LE3Texture* spriteTexture=nullptr);

    virtual void Draw();
    virtual void UpdateAssets(LE3AssetManager& assets);

    virtual std::shared_ptr<LE3Object> Duplicate(std::string newName);

    template <typename Archive>
    void serialize( Archive & ar )
    {
        LE3Object::serialize(ar);
        ar(CEREAL_NVP(m_spriteTextureName));
        ar(CEREAL_NVP(m_materialName));
    }

    LE3Material* GetMaterial();

    std::string m_spriteTextureName;
    std::string m_materialName;
protected:
    LE3Texture* m_spriteTexture;
    LE3Material* m_material;
    LE3Mesh<LE3Vertex>* m_mesh;
};
CEREAL_REGISTER_TYPE(LE3Sprite);
CEREAL_REGISTER_POLYMORPHIC_RELATION(LE3Object, LE3Sprite);