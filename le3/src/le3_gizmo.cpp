#include "le3_gizmo.h"
#include "le3_math_utils.h"
#include "le3_engine_systems.h"
using namespace le3;

#include <GL/glew.h>

#include <fmt/core.h>

namespace le3 {
    class LE3GizmoReleaseCommand : public LE3EditorCommand {
    public:
        LE3GizmoReleaseCommand(std::string objectName, glm::mat4 matrix) : m_objectName(objectName), m_matrix(matrix) {}

        virtual void execute() {
            LE3ObjectPtr pObject = LE3GetSceneManager().getActiveScene()->getObject(m_objectName);
            glm::mat4 newTransform = m_matrix * pObject->getTransform().getTransformMatrix();
            pObject->getTransform().fromTransformMatrix(newTransform);
        }

        virtual void undo() {
            LE3ObjectPtr pObject = LE3GetSceneManager().getActiveScene()->getObject(m_objectName);
            glm::mat4 newTransform = glm::inverse(m_matrix) * pObject->getTransform().getTransformMatrix();
            pObject->getTransform().fromTransformMatrix(newTransform);
        }

    private:
        std::string m_objectName;
        glm::mat4 m_matrix;
    };
}

LE3Gizmo::LE3Gizmo() :
    LE3DrawableObject(LE3GetAssetManager().getMaterial(DEFAULT_GIZMO_MATERIAL)),
    m_hoveredAxis(LE3_GIZMO_AXIS_NONE)
{
    setDrawPriority(DRAW_PRIORITY_UI);
}
void LE3Gizmo::draw(LE3ShaderPtr shaderOverride) {
    if (shaderOverride) return;
    if (m_state == LE3_GIZMO_STATE_DISABLED) return;

    m_pMaterial->apply();
    m_pMaterial->shader->uniform("hoveredAxis", (unsigned int)m_hoveredAxis);

    glClear(GL_DEPTH_BUFFER_BIT); // since we draw at UI level, clearing the depth bit should be fine
    glDisable(GL_CULL_FACE);

    switch (m_mode)
    {
    case LE3_GIZMO_MODE_SELECT: drawModeSelect(shaderOverride); break;
    case LE3_GIZMO_MODE_TRANSLATE: drawModeTranslate(shaderOverride); break;
    case LE3_GIZMO_MODE_ROTATE: drawModeRotate(shaderOverride); break;
    case LE3_GIZMO_MODE_SCALE: drawModeScale(shaderOverride); break;
    }
} 

void LE3Gizmo::update(float deltaTime) {
    switch (m_state)
    {
    case LE3_GIZMO_STATE_DISABLED: updateStateDisabled(deltaTime); break;
    case LE3_GIZMO_STATE_IDLE: updateStateIdle(deltaTime); break;
    case LE3_GIZMO_STATE_DRAGGING: updateStateDragging(deltaTime); break;
    case LE3_GIZMO_STATE_RELEASE: updateStateRelease(deltaTime); break;
    }

    LE3DrawableObject::update(deltaTime);
}

void LE3Gizmo::preUpdate() {
}

void LE3Gizmo::postUpdate() {
}


// void LE3Gizmo::update(float deltaTime) {
//     if (!m_bIsHoverable) return;
//     if (LE3GetEditorManager().isEditBlocked()) return;


//     // Gizmo drag
//     bool isDragging = LE3GetEditorManager().isMouseDown() && (m_hoveredAxis != LE3_GIZMO_AXIS_NONE) || m_bIsDragging;
//     if (isDragging && !m_bIsDragging) {
//         m_dragStartX = LE3GetEditorManager().getMouseRelX();
//         m_dragStartY = LE3GetEditorManager().getMouseRelY();
//         m_dragStartPos = m_transform.getPosition();
//     }
//     m_bIsDragging = isDragging;

//     // We check that the drag is long enough, so that we don't register a drag event when clicking
//     if (m_bIsDragging && !LE3GetEditorManager().isMouseDown() && (m_dragFrames > 10)) { // Drag release event
//         if (LE3ObjectPtr pObject = LE3GetEditorManager().getSelection().pObject.lock()) {
//             glm::mat4 objectTargetTransform = pObject->getTransform().getTransformMatrix();
//             glm::mat4 deltaTransform = objectTargetTransform * glm::inverse(m_selectObjectInitialTransform);
            
//             pObject->getTransform().fromTransformMatrix(m_selectObjectInitialTransform);
//             LE3GetEditorManager().getCommandStack().execute(std::make_unique<LE3GizmoReleaseCommand>(pObject->getName(), deltaTransform));
//             m_selectObjectInitialTransform = pObject->getTransform().getTransformMatrix();
//         }
//     }

//     if (!LE3GetEditorManager().isMouseDown()) m_bIsDragging = false; // Stop dragging when mouse is released

//     LE3GetEditorManager().setActiveEdit(m_bIsDragging);
//     if (m_bIsDragging) {
//         glm::vec2 base, tip;
//         getAxisScreen(m_hoveredAxis, base, tip);

//         int xrel = LE3GetEditorManager().getMouseRelX();
//         int yrel = LE3GetEditorManager().getMouseRelY();
//         float dx = xrel - m_dragStartX;
//         float dy = yrel - m_dragStartY;

//         float gizmoDragSpeed = 0.010f;
//         float t = glm::dot(glm::vec2(dx, dy), tip - base);
//         glm::vec3 projection = gizmoDragSpeed * t * getAxisLine(m_hoveredAxis);

//         m_transform.setPosition(m_transform.getPosition() + projection);

//         // Update the selected object
//         if (LE3ObjectPtr pObject = LE3GetEditorManager().getSelection().pObject.lock()) {
//             // glm::vec3 delta = m_transform.getPosition() - m_dragStartPos;
//             // pObject->getTransform().setPosition(pObject->getTransform().getPosition() + projection);

//             // Object global = parent * local == gizmo global
//             // local == parent^-1 * gizmo global
//             glm::mat4 parentMatrix(1.f);
//             if (pObject->getParent()) parentMatrix = pObject->getParent()->getWorldMatrix();
//             glm::mat4 local = glm::inverse(parentMatrix) * glm::translate(m_transform.getPosition());
//             pObject->getTransform().setPosition(glm::vec3(local[3]));
//         }
//         m_dragStartPos = m_transform.getPosition();
//     }
//     else if (LE3GetEditorManager().isMouseDown()) { // If we click to select
//         LE3GetEditorManager().getSelection().selectObject(LE3GetEditorManager().getHoveredObject());
//     }
    
//     LE3DrawableObject::update(deltaTime);
// }


void LE3Gizmo::getAxisScreen(LE3GizmoAxis axis, glm::vec2& base, glm::vec2& tip) {
    glm::mat4 PVM = 
        LE3GetActiveScene()->getMainCamera()->getProjectionMatrix() *
        LE3GetActiveScene()->getMainCamera()->getViewMatrix() *
        getWorldMatrix() * gizmoTransform(axis);
    glm::vec4 worldBase = PVM * glm::vec4(0.f, 0.f, 0.f, 1.f);
    glm::vec4 worldTip = PVM * glm::vec4(0.f, 0.565f, 0.f, 1.f);
    // worldBase /= worldBase.w; worldBase /= worldBase.z;
    // worldTip /= worldTip.w; worldTip /= worldTip.z;

    base = glm::vec2(worldBase / worldBase.z);
    tip = glm::vec2(worldTip / worldBase.z);
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

void LE3Gizmo::onObjectSelected(LE3ObjectWeakPtr wpObject) {
    // LE3ObjectPtr pObject = wpObject.lock();
    // if (!pObject) {
    //     setHidden(true);
    //     return;
    // }
    // setHidden(false);
    // m_transform.setPosition(pObject->getWorldPosition());
    // m_selectGizmoInitialTransform = getWorldMatrix();
    // m_selectObjectInitialTransform = pObject->getTransform().getTransformMatrix();
    // m_pSelectedObject = pObject;
}


// --------------------------------------------------------------------------------------------
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

void LE3Gizmo::drawModeSelect(LE3ShaderPtr shaderOverride) {
    float scaleFactor = 0.33f; // TODO: Move to constants
    glm::mat4 transform = scaleFactor * gizmoTransform(LE3_GIZMO_AXIS_ALL);
    transform[3] *= 1 / scaleFactor;

    m_pMaterial->shader->uniform("gizmoAxis", (unsigned int)LE3_GIZMO_AXIS_ALL);
    m_pMaterial->shader->uniform("gizmoTransform", transform);
    LE3GetAssetManager().getGizmoCenterMesh()->draw();
}
void LE3Gizmo::drawModeTranslate(LE3ShaderPtr shaderOverride) {
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
}
void LE3Gizmo::drawModeRotate(LE3ShaderPtr shaderOverride) {
}
void LE3Gizmo::drawModeScale(LE3ShaderPtr shaderOverride) {
    m_pMaterial->shader->uniform("gizmoAxis", (unsigned int)LE3_GIZMO_AXIS_X);
    m_pMaterial->shader->uniform("gizmoTransform", gizmoTransform(LE3_GIZMO_AXIS_X));
    LE3GetAssetManager().getGizmoScaleArrowMesh()->draw();

    m_pMaterial->shader->uniform("gizmoAxis", (unsigned int)LE3_GIZMO_AXIS_Y);
    m_pMaterial->shader->uniform("gizmoTransform", gizmoTransform(LE3_GIZMO_AXIS_Y));
    LE3GetAssetManager().getGizmoScaleArrowMesh()->draw();

    m_pMaterial->shader->uniform("gizmoAxis", (unsigned int)LE3_GIZMO_AXIS_Z);
    m_pMaterial->shader->uniform("gizmoTransform", gizmoTransform(LE3_GIZMO_AXIS_Z));
    LE3GetAssetManager().getGizmoScaleArrowMesh()->draw();

    m_pMaterial->shader->uniform("gizmoAxis", (unsigned int)LE3_GIZMO_AXIS_ALL);
    m_pMaterial->shader->uniform("gizmoTransform", gizmoTransform(LE3_GIZMO_AXIS_ALL));
    LE3GetAssetManager().getGizmoCenterMesh()->draw();
}
// --------------------------------------------------------------------------------------------

void LE3Gizmo::updateStateDisabled(float deltaTime) {
    if (LE3GetEditorManager().getSelection().type == LE3EditorSelection::LE3_SELECTION_OBJECT) {
        m_state = LE3_GIZMO_STATE_IDLE;
        return;
    }
    
    if (LE3GetEditorManager().getHoveredObject().lock() && isMouseDown()) {
        LE3GetEditorManager().getSelection().selectObject(LE3GetEditorManager().getHoveredObject());
        m_state = LE3_GIZMO_STATE_IDLE;
    }

}
void LE3Gizmo::updateStateIdle(float deltaTime) {
    if (LE3GetEditorManager().getSelection().type != LE3EditorSelection::LE3_SELECTION_OBJECT) {
        m_state = LE3_GIZMO_STATE_DISABLED;
        return;
    }
    // When updaing position outside of scene view, update gizmo position
    if (LE3ObjectPtr pObject = LE3GetEditorManager().getSelection().pObject.lock()) {
        m_transform.setPosition(pObject->getWorldPosition());
    }

    // Gizmo hover update
    m_hoveredAxis = getHoveredAxis();


    // Re-select (if no hover)
    if (
        isMouseDown() &&
        m_hoveredAxis == LE3_GIZMO_AXIS_NONE) {
        LE3GetEditorManager().getSelection().selectObject(LE3GetEditorManager().getHoveredObject());
    }

    // Gizmo drag initialization handling (if hover)
    if (isMouseDown() && m_hoveredAxis != LE3_GIZMO_AXIS_NONE) {
        m_dragFrames++;
        if (m_dragFrames > 10) {
            m_state = LE3_GIZMO_STATE_DRAGGING;    
            m_dragDelta = glm::vec3(0.f);
            m_selectObjectInitialTransform = LE3GetEditorManager().getSelection().pObject.lock()->getTransform().getTransformMatrix();
        }
    }
    if (!isMouseDown()) {
        m_dragFrames = 0;
    }
}
void LE3Gizmo::updateStateDragging(float deltaTime) {
    if (!isMouseDown()) {
        m_state = LE3_GIZMO_STATE_RELEASE;
        return;
    }

    if (LE3ObjectPtr pObject = LE3GetEditorManager().getSelection().pObject.lock()) {
        m_transform.setPosition(pObject->getWorldPosition());
    }

    const float gizmoAxisLength = 0.565f;
    float gizmoDragSpeed = 0.010f;

    glm::mat4 projViewMatrix = LE3GetActiveScene()->getMainCamera()->getProjectionMatrix() * LE3GetActiveScene()->getMainCamera()->getViewMatrix();
    glm::mat4 modelMatrix = getWorldMatrix() * gizmoTransform(m_hoveredAxis);
    glm::vec3 pWorld = glm::vec3(modelMatrix * glm::vec4(0.f, 0.f, 0.f, 1.f));
    glm::vec3 qWorld = glm::vec3(modelMatrix * glm::vec4(0.f, 0.565f, 0.f, 1.f));
    glm::vec2 pScreen = worldToScreen(projViewMatrix, pWorld);
    glm::vec2 qScreen = worldToScreen(projViewMatrix, qWorld);

    float dx = LE3GetEditorManager().getMouseRelX(); 
    float dy = LE3GetEditorManager().getMouseRelY();

    LE3ObjectPtr pObject = LE3GetEditorManager().getSelection().pObject.lock();

    if (m_mode == LE3_GIZMO_MODE_TRANSLATE) {
        float t = glm::dot(glm::vec2(dx, dy), qScreen - pScreen);
        glm::vec3 projection = t * getAxisLine(m_hoveredAxis);
        m_dragDelta += gizmoDragSpeed * projection;
        pObject->getTransform().setPosition(glm::vec3(m_selectObjectInitialTransform[3]) + m_dragDelta);
    }
    if (m_mode == LE3_GIZMO_MODE_SCALE) {
        float t = glm::dot(glm::vec2(dx, dy), qScreen - pScreen);
        glm::vec3 projection = t * getAxisLine(m_hoveredAxis);
        m_dragDelta += gizmoDragSpeed * projection;
        glm::vec3 originalScale = glm::vec3(
            glm::length(m_selectObjectInitialTransform[0]),
            glm::length(m_selectObjectInitialTransform[1]),
            glm::length(m_selectObjectInitialTransform[2]));
        pObject->getTransform().setScale(originalScale + m_dragDelta);
    }


}
void LE3Gizmo::updateStateRelease(float deltaTime) {



    m_state = LE3_GIZMO_STATE_IDLE;
}

bool LE3Gizmo::isMouseDown() {
    // Ignore when cursor is outside!
    if (LE3GetActiveScene()->getCursorLocation().z < 0) return false;
    return LE3GetEditorManager().isMouseDown();
}

LE3GizmoAxis LE3Gizmo::getHoveredAxis() {
    glm::mat4 projViewMatrix = LE3GetActiveScene()->getMainCamera()->getProjectionMatrix() * LE3GetActiveScene()->getMainCamera()->getViewMatrix();
    glm::vec3 rawCursorPosition = LE3GetActiveScene()->getCursorLocation();
    if (rawCursorPosition.z < 0) return LE3_GIZMO_AXIS_NONE;
    glm::vec2 cursorPosition = glm::vec2(LE3GetActiveScene()->getCursorLocation());

    if (m_mode == LE3_GIZMO_MODE_SELECT || m_mode == LE3_GIZMO_MODE_SCALE || m_mode == LE3_GIZMO_MODE_TRANSLATE)
        return getHoveredAxisTranslateScale(projViewMatrix, cursorPosition);
    if (m_mode == LE3_GIZMO_MODE_ROTATE)
        return getHoveredAxisRotate(projViewMatrix, cursorPosition);

    return LE3_GIZMO_AXIS_NONE;
}
LE3GizmoAxis LE3Gizmo::getHoveredAxisTranslateScale(glm::mat4 projViewMatrix, glm::vec2 cursorPosition) {
    const LE3GizmoAxis axes[] = { LE3_GIZMO_AXIS_X, LE3_GIZMO_AXIS_Y, LE3_GIZMO_AXIS_Z };
    const float gizmoAxisLength = 0.565f;
    const float gizmoSelectionThreshold = 0.05f;

    for (LE3GizmoAxis axis : axes) {
        glm::mat4 modelMatrix = getWorldMatrix() * gizmoTransform(axis);
        glm::vec3 pWorld = glm::vec3(modelMatrix * glm::vec4(0.f, 0.f, 0.f, 1.f));
        glm::vec3 qWorld = glm::vec3(modelMatrix * glm::vec4(0.f, gizmoAxisLength, 0.f, 1.f));
        glm::vec2 pScreen = worldToScreen(projViewMatrix, pWorld);
        glm::vec2 qScreen = worldToScreen(projViewMatrix, qWorld);

        float dist = distancePointLineSegment(pScreen, qScreen, cursorPosition);
        if (dist < gizmoSelectionThreshold)
            return axis;
    }
    return LE3_GIZMO_AXIS_NONE;
}
LE3GizmoAxis LE3Gizmo::getHoveredAxisRotate(glm::mat4 projViewMatrix, glm::vec2 cursorPosition) {
    return LE3_GIZMO_AXIS_NONE;
}