#include "ui/le3_ui_text_object.h"
#include "core/le3_engine_systems.h"
using namespace le3;

#ifdef __linux__
#include <GL/glew.h>
#else
#include <gl/glew.h>
#endif

#include "stb_truetype.h"

LE3UITextObject::LE3UITextObject(LE3FontPtr pFont) :
    LE3UIObject(), m_pFont(pFont)
{
    setMaterial(LE3GetAssetManager().getMaterial(DEFAULT_UI_TEXT_MATERIAL));
}

void LE3UITextObject::setText(std::string text) {
    if (m_text == text) return;
    m_text = text;
    rebuildLayout();
}

void LE3UITextObject::draw(LE3ShaderPtr shaderOverride) {
    if (shaderOverride.lock()) return;
    if (m_pFont.expired() || m_charQuads.empty()) return;

    auto font = m_pFont.lock();
    auto shader = m_pMaterial.lock()->shader.lock();
    shader->use();

    // Bind font atlas
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, font->getAtlasTextureID());
    shader->uniform("fontAtlas", 0u);
    shader->uniform("textColor", m_textColor);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glm::vec3 basePos = m_transform.getPosition();
    float textHeight = m_transform.getScale().y;
    float aspectRatio = LE3GetEngineState()->getAspectRatio();

    auto uiMesh = LE3GetAssetManager().getUIMesh().lock();

    for (const auto& cq : m_charQuads) {
        glm::vec3 charPos = basePos + glm::vec3(
            cq.offset.x * textHeight / aspectRatio,
            cq.offset.y * textHeight,
            0.f
        );
        glm::vec2 charScale(
            cq.size.x * textHeight / aspectRatio,
            cq.size.y * textHeight
        );

        shader->uniform("position", charPos);
        shader->uniform("scale", charScale);
        shader->uniform("cropBottomLeft", cq.uvMin);
        shader->uniform("cropTopRight", cq.uvMax);

        uiMesh->draw();
    }

    glDisable(GL_BLEND);
}

void LE3UITextObject::rebuildLayout() {
    m_charQuads.clear();

    auto font = m_pFont.lock();
    if (!font || m_text.empty()) return;

    const stbtt_packedchar* chardata = font->getPackedChars();
    float fontSize = font->getFontSize();
    int pw = font->getAtlasWidth();
    int ph = font->getAtlasHeight();

    float xpos = 0.0f, ypos = 0.0f;

    for (unsigned char c : m_text) {
        if (c < LE3_FONT_FIRST_CHAR || c >= LE3_FONT_FIRST_CHAR + LE3_FONT_NUM_CHARS)
            continue;

        stbtt_aligned_quad q;
        stbtt_GetPackedQuad(chardata, pw, ph, c - LE3_FONT_FIRST_CHAR, &xpos, &ypos, &q, 0);

        LE3CharQuad cq;
        // Center offset, normalized by fontSize. Flip y (stb y-down -> screen y-up)
        cq.offset.x = (q.x0 + q.x1) * 0.5f / fontSize;
        cq.offset.y = -(q.y0 + q.y1) * 0.5f / fontSize;
        cq.size.x = (q.x1 - q.x0) / fontSize;
        cq.size.y = (q.y1 - q.y0) / fontSize;
        cq.uvMin = glm::vec2(q.s0, q.t1);
        cq.uvMax = glm::vec2(q.s1, q.t0);

        m_charQuads.push_back(cq);
    }
}
