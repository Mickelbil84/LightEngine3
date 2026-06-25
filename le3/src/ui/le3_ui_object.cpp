#include "ui/le3_ui_object.h"
#include "core/le3_engine_systems.h"
using namespace le3;

LE3UIObject::LE3UIObject(LE3TexturePtr pTexture) : 
    LE3StaticModel(LE3StaticMeshPtr(), LE3MaterialPtr()),
    m_baseColor(glm::vec4(1.f)), m_hoveredColor(glm::vec4(1.f)), m_selectedColor(glm::vec4(1.f)),
    m_pTexture(pTexture), m_textureCropBottomLeft(glm::vec2(0.f)), m_textureCropTopRight(glm::vec2(1.f)),
    m_uiState(LE3UIObjectState::UI_OBJECT_BASE)
    {
    setMaterial(LE3GetAssetManager().getMaterial(DEFAULT_UI_MATERIAL));
    setCastShadow(false);
    getPhysicsComponent().setIsRigidBody(false);
    m_pMesh = LE3GetAssetManager().getUIMesh();
    setDrawPriority(DRAW_PRIORITY_UI);
}

void LE3UIObject::draw(LE3ShaderPtr shaderOverride) {
    if (shaderOverride.lock()) return;
    m_pMaterial.lock()->bUseDiffuseTexture = !m_pTexture.expired();
    if (m_pMaterial.lock()->bUseDiffuseTexture)
        m_pMaterial.lock()->diffuseTexture = m_pTexture;

    std::shared_ptr<LE3Shader> shader = m_pMaterial.lock()->shader.lock();
    shader->use();

    // vs
    shader->uniform("position", m_transform.getPosition());
    shader->uniform("scale", glm::vec2(m_transform.getScale()));
    
    //fs
    shader->uniform("baseColor", getBaseColor());
    shader->uniform("hoveredColor", getHoveredColor());
    shader->uniform("selectedColor", getSelectedColor());
    shader->uniform("state", (unsigned int)m_uiState);
    shader->uniform("cropBottomLeft", m_textureCropBottomLeft);
    shader->uniform("cropTopRight", m_textureCropTopRight);

    LE3StaticModel::draw(shaderOverride);

}

void LE3UIObject::update(float deltaTime) {
    if (isSelected())
        m_uiState = UI_OBJECT_SELECTED;
    else if (isHovered())
        m_uiState = UI_OBJECT_HOVERED;
    else
        m_uiState = UI_OBJECT_BASE;
}

inline float LE3UIObject::getBoundRight() const {
    return m_transform.getPosition().x + 0.5f * m_transform.getScale().x;
}
inline float LE3UIObject::getBoundLeft() const {
    return m_transform.getPosition().x - 0.5f * m_transform.getScale().x;
}
inline float LE3UIObject::getBoundTop() const {
    return m_transform.getPosition().y + 0.5f * m_transform.getScale().y;
}
inline float LE3UIObject::getBoundBottom() const {
    return m_transform.getPosition().y - 0.5f * m_transform.getScale().y;
}

bool LE3UIObject::isHovered() {
    LE3Input input = LE3GetInput();
    float x = input.mouseScreenX, y = input.mouseScreenY;

    // fmt::print("x:{}, [{},{}] --> {}\n", x, getBoundLeft(), getBoundRight(), (getBoundLeft() <= x) && (x <= getBoundRight()));

    return getBoundLeft() <= x && x <= getBoundRight() &&
        getBoundBottom() <= y && y <= getBoundTop();
}
bool LE3UIObject::isSelected() {
    return isHovered() && LE3GetInput().bLeftMouseDown;
}