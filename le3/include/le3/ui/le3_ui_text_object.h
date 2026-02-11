#pragma once

#include <vector>
#include "ui/le3_ui_object.h"
#include "ui/le3_font.h"

namespace le3 {

    struct LE3CharQuad {
        glm::vec2 offset;   // center offset from text origin (normalized by fontSize)
        glm::vec2 size;     // width/height (normalized by fontSize)
        glm::vec2 uvMin;    // top-left UV in atlas
        glm::vec2 uvMax;    // bottom-right UV in atlas
    };

    class LE3UITextObject : public LE3UIObject {
    public:
        LE3UITextObject(LE3FontPtr pFont);
        LE3_TYPE_RETURN(LE3UITextObject)

        void draw(LE3ShaderPtr shaderOverride = LE3ShaderPtr()) override;

        void setText(std::string text);
        inline std::string getText() const { return m_text; }

        inline void setTextColor(glm::vec4 color) { m_textColor = color; }
        inline glm::vec4 getTextColor() const { return m_textColor; }

    private:
        LE3FontPtr m_pFont;
        std::string m_text;
        glm::vec4 m_textColor = glm::vec4(1.f);
        std::vector<LE3CharQuad> m_charQuads;

        void rebuildLayout();
    };
    using LE3UITextObjectPtr = std::shared_ptr<LE3UITextObject>;
}
