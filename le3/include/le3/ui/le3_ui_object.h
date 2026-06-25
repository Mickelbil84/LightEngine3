#pragma once

#include "graphics/le3_model.h"
#include "graphics/le3_primitives.h"

namespace le3 {
    enum LE3UIObjectState {
        UI_OBJECT_BASE = 0,
        UI_OBJECT_HOVERED = 1,
        UI_OBJECT_SELECTED = 2
    };

    class LE3UIObject : public LE3StaticModel {
    public:
        LE3UIObject(LE3TexturePtr pTexture = LE3TexturePtr());
        LE3_TYPE_RETURN(LE3UIObject)

        virtual void draw(LE3ShaderPtr shaderOverride = LE3ShaderPtr());
        virtual void update(float deltaTime);

        inline void setBaseColor(glm::vec4 color) { m_baseColor = color; }
        inline void setHoveredColor(glm::vec4 color) { m_hoveredColor = color; }
        inline void setSelectedColor(glm::vec4 color) { m_selectedColor = color; }
        inline glm::vec4 getBaseColor() const { return m_baseColor; }
        inline glm::vec4 getHoveredColor() const { return m_hoveredColor; }
        inline glm::vec4 getSelectedColor() const { return m_selectedColor; }

        inline void setTextureCropBottomLeft(glm::vec2 crop) { m_textureCropBottomLeft = crop; }
        inline void setTextureCropTopRight(glm::vec2 crop) { m_textureCropTopRight = crop; }
        inline glm::vec2 getTextureCropBottomLeft() const { return m_textureCropBottomLeft; }
        inline glm::vec2 getTextureCropTopRight() const { return m_textureCropTopRight; }

        inline float getBoundRight() const;
        inline float getBoundLeft() const;
        inline float getBoundTop() const;
        inline float getBoundBottom() const;

        virtual bool isHovered();
        virtual bool isSelected();

    protected:
        glm::vec4 m_baseColor, m_hoveredColor, m_selectedColor;
        LE3UIObjectState m_uiState;

        LE3TexturePtr m_pTexture;
        glm::vec2 m_textureCropBottomLeft, m_textureCropTopRight;
    };
    using LE3UIObjectPtr = std::shared_ptr<LE3UIObject>;
}