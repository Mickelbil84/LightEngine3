#include "le3_gizmo.h"
#include "le3_engine_systems.h"
using namespace le3;

#include <GL/glew.h>

LE3Gizmo::LE3Gizmo() :
    LE3DrawableObject(LE3GetAssetManager().getMaterial(DEFAULT_GIZMO_MATERIAL))
{
    setDrawPriority(DRAW_PRIORITY_UI);
}
void LE3Gizmo::draw(LE3ShaderPtr shaderOverride) {
    if (shaderOverride) return;
    m_pMaterial->apply();
    
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

void LE3Gizmo::updateScale(glm::vec3 cameraPos) {
    float dist = glm::l2Norm(cameraPos - m_transform.getPosition());
    m_transform.setScale(dist * 0.3f); // TODO: move to engine config
}