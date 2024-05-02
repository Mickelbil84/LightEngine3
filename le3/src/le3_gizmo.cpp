#include "le3_gizmo.h"
#include "le3_math_utils.h"
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
    m_pMaterial->shader->uniform("hoveredAxis", (unsigned int)m_hoveredAxis);

    // glDisable(GL_DEPTH_TEST);
    glClear(GL_DEPTH_BUFFER_BIT); // since we draw at UI level, clearing the depth bit should be fine
    m_pMaterial->shader->uniform("gizmoAxis", (unsigned int)LE3_GIZMO_AXIS_X);
    m_pMaterial->shader->uniform("gizmoTransform", gizmoTransform(LE3_GIZMO_AXIS_X));
    LE3GetAssetManager().getGizmoArrowMesh()->draw();

    m_pMaterial->shader->uniform("gizmoAxis", (unsigned int)LE3_GIZMO_AXIS_Y);
    m_pMaterial->shader->uniform("gizmoTransform", gizmoTransform(LE3_GIZMO_AXIS_Y));
    LE3GetAssetManager().getGizmoArrowMesh()->draw();

    m_pMaterial->shader->uniform("gizmoAxis", (unsigned int)LE3_GIZMO_AXIS_Z);
    m_pMaterial->shader->uniform("gizmoTransform", gizmoTransform(LE3_GIZMO_AXIS_Z));
    LE3GetAssetManager().getGizmoArrowMesh()->draw();

    m_pMaterial->shader->uniform("gizmoAxis", (unsigned int)LE3_GIZMO_AXIS_ALL);
    m_pMaterial->shader->uniform("gizmoTransform", gizmoTransform(LE3_GIZMO_AXIS_ALL));
    LE3GetAssetManager().getGizmoCenterMesh()->draw();
    // glEnable(GL_DEPTH_TEST);
} 

glm::mat4 LE3Gizmo::gizmoTransform(LE3GizmoAxis gizmoAxis) {
    glm::mat4 gizmoAxisRot(1.f);
    if (gizmoAxis == LE3_GIZMO_AXIS_X) {
        gizmoAxisRot = glm::mat4(
            0, 1, 0, 0,
            1, 0, 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1
        );
    }
    if (gizmoAxis == LE3_GIZMO_AXIS_Z) {
        gizmoAxisRot = glm::mat4(
            1, 0, 0, 0,
            0, 0, 1, 0,
            0, 1, 0, 0,
            0, 0, 0, 1
        );
    }

    glm::vec3 cameraPos = LE3GetActiveScene()->getMainCamera()->getPosition();
    float scale = glm::length(m_transform.getPosition() - cameraPos) * 0.3f;
    glm::mat4 gizmoScale = glm::scale(glm::mat4(1.f), glm::vec3(scale));

    return gizmoAxisRot * gizmoScale;
}

void LE3Gizmo::update(float deltaTime) {
    LE3DrawableObject::update(deltaTime);

    m_hoveredAxis = LE3_GIZMO_AXIS_NONE;
    glm::vec3 cursorRaw = LE3GetActiveScene()->getCursorLocation();
    if (cursorRaw.z < 0) return;
    glm::vec2 cursor(cursorRaw);

    float threshold = 0.02f; // TODO: Move to constants
    int cnt = 0;

    if (distanceToLineAxis(cursor, LE3_GIZMO_AXIS_X) < threshold) { m_hoveredAxis = LE3_GIZMO_AXIS_X; cnt++; }
    if (distanceToLineAxis(cursor, LE3_GIZMO_AXIS_Y) < threshold) { m_hoveredAxis = LE3_GIZMO_AXIS_Y; cnt++; }
    if (distanceToLineAxis(cursor, LE3_GIZMO_AXIS_Z) < threshold) { m_hoveredAxis = LE3_GIZMO_AXIS_Z; cnt++; }
    if (cnt == 3) m_hoveredAxis = LE3_GIZMO_AXIS_ALL;
}

float LE3Gizmo::distanceToLineAxis(glm::vec2 point, LE3GizmoAxis axis) {
    glm::mat4 PVM = 
        LE3GetActiveScene()->getMainCamera()->getProjectionMatrix() *
        LE3GetActiveScene()->getMainCamera()->getViewMatrix() *
        getWorldMatrix() * gizmoTransform(axis);
    glm::vec4 base = PVM * glm::vec4(0.f, 0.f, 0.f, 1.f);
    glm::vec4 tip = PVM * glm::vec4(0.f, 0.565f, 0.f, 1.f);
    base /= base.w; base /= base.z;
    tip /= tip.w; tip /= tip.z;

    glm::vec2 screenBase = glm::vec2(base);
    glm::vec2 screenTip = glm::vec2(tip);
    

    // fmt::print("base: ({}, {}), tip: ({}, {}), point: ({}, {})\n", 
    //     screenBase.x, screenBase.y, screenTip.x, screenTip.y, point.x, point.y);

    return distancePointLineSegment(screenBase, screenTip, point);
}
