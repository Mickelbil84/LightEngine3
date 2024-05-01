#include "le3_gizmo.h"
#include "le3_engine_systems.h"
using namespace le3;

#include <GL/glew.h>

#include <fmt/core.h>

LE3Gizmo::LE3Gizmo() :
    LE3DrawableObject(LE3GetAssetManager().getMaterial(DEFAULT_GIZMO_MATERIAL)),
    m_hoveredAxis(LE3_GIZMO_AXIS_NONE)
{
    setDrawPriority(DRAW_PRIORITY_UI);
}
void LE3Gizmo::draw(LE3ShaderPtr shaderOverride) {
    if (shaderOverride) return;

    m_pMaterial->apply();

    m_pMaterial->shader->uniform("gizmoPos", m_transform.getPosition());
    m_pMaterial->shader->uniform("cameraPos", LE3GetActiveScene()->getMainCamera()->getPosition());
    m_pMaterial->shader->uniform("gizmoScale", 0.3f); // TODO: move to engine config
    m_pMaterial->shader->uniform("hoveredAxis", (unsigned int)m_hoveredAxis);

    // glDisable(GL_DEPTH_TEST);
    glClear(GL_DEPTH_BUFFER_BIT); // since we draw at UI level, clearing the depth bit should be fine
    m_pMaterial->shader->uniform("gizmoAxis", (unsigned int)LE3_GIZMO_AXIS_X);
    LE3GetAssetManager().getGizmoArrowMesh()->draw();
    m_pMaterial->shader->uniform("gizmoAxis", (unsigned int)LE3_GIZMO_AXIS_Y);
    LE3GetAssetManager().getGizmoArrowMesh()->draw();
    m_pMaterial->shader->uniform("gizmoAxis", (unsigned int)LE3_GIZMO_AXIS_Z);
    LE3GetAssetManager().getGizmoArrowMesh()->draw();
    m_pMaterial->shader->uniform("gizmoAxis", (unsigned int)LE3_GIZMO_AXIS_ALL);
    LE3GetAssetManager().getGizmoCenterMesh()->draw();
    // glEnable(GL_DEPTH_TEST);
} 

void LE3Gizmo::update(float deltaTime) {
    LE3DrawableObject::update(deltaTime);

    glm::vec3 cursor = LE3GetActiveScene()->getCursorLocation();
    if (cursor.z <= 0.f) {
        fmt::print("{}: none\n", LE3GetActiveScene()->getName());
        return;
    }
    if (cursor.x >= 0.f) fmt::print("{}: x >= 0\n", LE3GetActiveScene()->getName());
    else fmt::print("{}: x < 0\n", LE3GetActiveScene()->getName());
}