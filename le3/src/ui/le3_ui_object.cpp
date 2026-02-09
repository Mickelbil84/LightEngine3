#include "ui/le3_ui_object.h"
#include "core/le3_engine_systems.h"
using namespace le3;

LE3UIObject::LE3UIObject() : 
    LE3StaticModel(LE3StaticMeshPtr(), LE3MaterialPtr()),
    m_baseColor(glm::vec4(1.f)), m_hoveredColor(glm::vec4(1.f)), m_selectedColor(glm::vec4(1.)),
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
    m_pMaterial.lock()->bUseDiffuseTexture = false;

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

    LE3StaticModel::draw(shaderOverride);

}
