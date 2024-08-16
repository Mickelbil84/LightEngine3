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
    glDisable(GL_CULL_FACE);
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
    if (!m_bIsDynamicScale) gizmoScale = glm::mat4(1.f);

    return gizmoAxisRot * gizmoScale;
}

void LE3Gizmo::preUpdate() {
    m_hoveredCnt = 0;
}

void LE3Gizmo::update(float deltaTime) {
    if (!m_bIsHoverable) return;
    if (LE3GetEditorManager().isEditBlocked()) return;

    glm::vec3 cursorRaw = LE3GetActiveScene()->getCursorLocation();
    if (cursorRaw.z < 0) return;
    glm::vec2 cursor(cursorRaw);

    float threshold = 0.05f; // TODO: Move to constants

    if (!m_bIsDragging) { // If we already dragging, don't update hovered axis
        if (distanceToLineAxis(cursor, LE3_GIZMO_AXIS_X) < threshold) { m_hoveredAxis = LE3_GIZMO_AXIS_X; m_hoveredCnt++; }
        if (distanceToLineAxis(cursor, LE3_GIZMO_AXIS_Y) < threshold) { m_hoveredAxis = LE3_GIZMO_AXIS_Y; m_hoveredCnt++; }
        if (distanceToLineAxis(cursor, LE3_GIZMO_AXIS_Z) < threshold) { m_hoveredAxis = LE3_GIZMO_AXIS_Z; m_hoveredCnt++; }
        if (m_hoveredCnt == 3) m_hoveredAxis = LE3_GIZMO_AXIS_ALL;
    }
    else {
        m_hoveredCnt++;
    }

    // Gizmo drag
    bool isDragging = LE3GetEditorManager().isMouseDown() && (m_hoveredAxis != LE3_GIZMO_AXIS_NONE) || m_bIsDragging;
    if (isDragging && !m_bIsDragging) {
        m_dragStartX = LE3GetEditorManager().getMouseRelX();
        m_dragStartY = LE3GetEditorManager().getMouseRelY();
        m_dragStartPos = m_transform.getPosition();
    }
    m_bIsDragging = isDragging;
    if (!LE3GetEditorManager().isMouseDown()) m_bIsDragging = false; // Stop dragging when mouse is released

    LE3GetEditorManager().setActiveEdit(m_bIsDragging);
    if (m_bIsDragging) {
        glm::vec2 base, tip;
        getAxisScreen(m_hoveredAxis, base, tip);

        int xrel = LE3GetEditorManager().getMouseRelX();
        int yrel = LE3GetEditorManager().getMouseRelY();
        float dx = xrel - m_dragStartX;
        float dy = yrel - m_dragStartY;

        float gizmoDragSpeed = 0.010f;
        float t = glm::dot(glm::vec2(dx, dy), tip - base);
        glm::vec3 projection = gizmoDragSpeed * t * getAxisLine(m_hoveredAxis);

        m_transform.setPosition(m_transform.getPosition() + projection);

        // Update the selected object
        if (LE3ObjectPtr pObject = LE3GetEditorManager().getSelectedObject()) {
            // glm::vec3 delta = m_transform.getPosition() - m_dragStartPos;
            // pObject->getTransform().setPosition(pObject->getTransform().getPosition() + projection);

            // Object global = parent * local == gizmo global
            // local == parent^-1 * gizmo global
            glm::mat4 parentMatrix(1.f);
            if (pObject->getParent()) parentMatrix = pObject->getParent()->getWorldMatrix();
            glm::mat4 local = glm::inverse(parentMatrix) * glm::translate(m_transform.getPosition());
            pObject->getTransform().setPosition(glm::vec3(local[3]));
        }
        m_dragStartPos = m_transform.getPosition();
    }
    else if (LE3GetEditorManager().isMouseDown()) { // If we click to select
        LE3GetEditorManager().setSelectedObject();
    }
    
    LE3DrawableObject::update(deltaTime);
}

void LE3Gizmo::postUpdate() {
    if (m_hoveredCnt == 0) m_hoveredAxis = LE3_GIZMO_AXIS_NONE;
}

void LE3Gizmo::getAxisScreen(LE3GizmoAxis axis, glm::vec2& base, glm::vec2& tip) {
    glm::mat4 PVM = 
        LE3GetActiveScene()->getMainCamera()->getProjectionMatrix() *
        LE3GetActiveScene()->getMainCamera()->getViewMatrix() *
        getWorldMatrix() * gizmoTransform(axis);
    glm::vec4 worldBase = PVM * glm::vec4(0.f, 0.f, 0.f, 1.f);
    glm::vec4 worldTip = PVM * glm::vec4(0.f, 0.565f, 0.f, 1.f);
    worldBase /= worldBase.w; worldBase /= worldBase.z;
    worldTip /= worldTip.w; worldTip /= worldTip.z;

    base = glm::vec2(worldBase);
    tip = glm::vec2(worldTip);
}

float LE3Gizmo::distanceToLineAxis(glm::vec2 point, LE3GizmoAxis axis) {
    glm::vec2 screenBase, screenTip;
    getAxisScreen(axis, screenBase, screenTip);
    return distancePointLineSegment(screenBase, screenTip, point);
}

glm::vec3 LE3Gizmo::getAxisLine(LE3GizmoAxis axis) {
    if (axis == LE3_GIZMO_AXIS_X) return glm::vec3(1.f, 0.f, 0.f);
    if (axis == LE3_GIZMO_AXIS_Y) return glm::vec3(0.f, -1.f, 0.f);
    if (axis == LE3_GIZMO_AXIS_Z) return glm::vec3(0.f, 0.f, 1.f);
    return glm::vec3(0.f);
}

void LE3Gizmo::onObjectSelected(LE3ObjectPtr pObject) {
    if (!pObject) {
        setHidden(true);
        return;
    }
    setHidden(false);
    m_transform.setPosition(pObject->getWorldPosition());
    m_selectGizmoInitialTransform = getWorldMatrix();
    m_selectObjectInitialTransform = pObject->getTransform().getTransformMatrix();
    m_pSelectedObject = pObject;
}