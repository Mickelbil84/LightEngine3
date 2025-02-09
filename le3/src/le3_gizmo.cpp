#include "le3_gizmo.h"
#include "le3_math_utils.h"
#include "le3_engine_systems.h"
using namespace le3;

#include <GL/glew.h>

#include <fmt/core.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// TODO: Move to constants throughot the entire file..

namespace le3 {
    class LE3GizmoReleaseCommand : public LE3EditorCommand {
    public:
        LE3GizmoReleaseCommand(std::vector<std::string> objectNames, std::map<std::string, glm::mat4> matrix) : m_objectNames(objectNames), m_matrix(matrix) {}

        virtual void execute() {
            for (std::string objectName : m_objectNames) {
                LE3ObjectPtr pObject = LE3GetSceneManager().getActiveScene()->getObject(objectName);
                glm::mat4 newTransform = m_matrix[objectName] * pObject->getTransform().getTransformMatrix();
                pObject->getTransform().fromTransformMatrix(newTransform);
            }
        }

        virtual void undo() {
            for (std::string objectName : m_objectNames) {
                LE3ObjectPtr pObject = LE3GetSceneManager().getActiveScene()->getObject(objectName);
                glm::mat4 newTransform = glm::inverse(m_matrix[objectName]) * pObject->getTransform().getTransformMatrix();
                pObject->getTransform().fromTransformMatrix(newTransform);
            }
        }

    private:
        std::vector<std::string> m_objectNames;
        std::map<std::string, glm::mat4> m_matrix;
    };
}

LE3Gizmo::LE3Gizmo() :
    LE3DrawableObject(LE3GetAssetManager().getMaterial(DEFAULT_GIZMO_MATERIAL)),
    m_hoveredAxis(LE3_GIZMO_AXIS_NONE),
    m_state(LE3_GIZMO_STATE_DISABLED),
    m_mode(LE3_GIZMO_MODE_TRANSLATE)
{
    setDrawPriority(DRAW_PRIORITY_UI);
}
void LE3Gizmo::init() {
    LE3GetEventManager().subscribe(LE3SceneEvents::LE3_EVENT_OBJECT_RENAME, std::dynamic_pointer_cast<LE3Object>(shared_from_this()), [this](void* data) {
        std::pair<std::string, std::string>* p = reinterpret_cast<std::pair<std::string, std::string>*>(data);
        if (m_selectObjectsInitialTransform.contains(p->first)) {
            glm::mat4 transform = m_selectObjectsInitialTransform[p->first];
            m_selectObjectsInitialTransform.erase(p->first);
            m_selectObjectsInitialTransform[p->second] = transform;
        }
    });
}
void LE3Gizmo::draw(LE3ShaderPtr shaderOverride) {
    if (shaderOverride.lock()) return;
    if (m_state == LE3_GIZMO_STATE_DISABLED) return;

    m_pMaterial.lock()->apply();
    m_pMaterial.lock()->shader.lock()->uniform("hoveredAxis", (unsigned int)m_hoveredAxis);

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


// --------------------------------------------------------------------------------------------

glm::vec3 LE3Gizmo::getAxisLine(LE3GizmoAxis axis) {
    if (axis == LE3_GIZMO_AXIS_X) return glm::vec3(1.f, 0.f, 0.f);
    if (axis == LE3_GIZMO_AXIS_Y) return glm::vec3(0.f, 1.f, 0.f);
    if (axis == LE3_GIZMO_AXIS_Z) return glm::vec3(0.f, 0.f, 1.f);
    if (axis == LE3_GIZMO_AXIS_ALL) return glm::vec3(1.f);
    if (axis == LE3_GIZMO_AXIS_XY) return glm::vec3(1.f, 1.f, 0.f);
    if (axis == LE3_GIZMO_AXIS_XZ) return glm::vec3(1.f, 0.f, 1.f);
    if (axis == LE3_GIZMO_AXIS_YZ) return glm::vec3(0.f, 1.f, 1.f);
    return glm::vec3(0.f);
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
    if (gizmoAxis == LE3_GIZMO_AXIS_Z || gizmoAxis == LE3_GIZMO_AXIS_XZ) {
        gizmoAxisRot = glm::mat4(
            1, 0, 0, 0,
            0, 0, 1, 0,
            0, 1, 0, 0,
            0, 0, 0, 1
        );
    }
    if (gizmoAxis == LE3_GIZMO_AXIS_YZ) {
        gizmoAxisRot = glm::mat4(
            0, 0, 1, 0,
            0, 1, 0, 0,
            1, 0, 0, 0,
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

    m_pMaterial.lock()->shader.lock()->uniform("gizmoAxis", (unsigned int)LE3_GIZMO_AXIS_ALL);
    m_pMaterial.lock()->shader.lock()->uniform("gizmoTransform", transform);
    LE3GetAssetManager().getGizmoCenterMesh().lock()->draw();
}
void LE3Gizmo::drawModeTranslate(LE3ShaderPtr shaderOverride) {
    m_pMaterial.lock()->shader.lock()->uniform("gizmoAxis", (unsigned int)LE3_GIZMO_AXIS_X);
    m_pMaterial.lock()->shader.lock()->uniform("gizmoTransform", gizmoTransform(LE3_GIZMO_AXIS_X));
    LE3GetAssetManager().getGizmoArrowMesh().lock()->draw();

    m_pMaterial.lock()->shader.lock()->uniform("gizmoAxis", (unsigned int)LE3_GIZMO_AXIS_Y);
    m_pMaterial.lock()->shader.lock()->uniform("gizmoTransform", gizmoTransform(LE3_GIZMO_AXIS_Y));
    LE3GetAssetManager().getGizmoArrowMesh().lock()->draw();

    m_pMaterial.lock()->shader.lock()->uniform("gizmoAxis", (unsigned int)LE3_GIZMO_AXIS_Z);
    m_pMaterial.lock()->shader.lock()->uniform("gizmoTransform", gizmoTransform(LE3_GIZMO_AXIS_Z));
    LE3GetAssetManager().getGizmoArrowMesh().lock()->draw();

    m_pMaterial.lock()->shader.lock()->uniform("gizmoAxis", (unsigned int)LE3_GIZMO_AXIS_ALL);
    m_pMaterial.lock()->shader.lock()->uniform("gizmoTransform", gizmoTransform(LE3_GIZMO_AXIS_ALL));
    LE3GetAssetManager().getGizmoCenterMesh().lock()->draw();

    m_pMaterial.lock()->shader.lock()->uniform("gizmoAxis", (unsigned int)LE3_GIZMO_AXIS_XY);
    m_pMaterial.lock()->shader.lock()->uniform("gizmoTransform", gizmoTransform(LE3_GIZMO_AXIS_XY));
    LE3GetAssetManager().getGizmoPlaneMesh().lock()->draw();
    m_pMaterial.lock()->shader.lock()->uniform("gizmoAxis", (unsigned int)LE3_GIZMO_AXIS_YZ);
    m_pMaterial.lock()->shader.lock()->uniform("gizmoTransform", gizmoTransform(LE3_GIZMO_AXIS_YZ));
    LE3GetAssetManager().getGizmoPlaneMesh().lock()->draw();
    m_pMaterial.lock()->shader.lock()->uniform("gizmoAxis", (unsigned int)LE3_GIZMO_AXIS_XZ);
    m_pMaterial.lock()->shader.lock()->uniform("gizmoTransform", gizmoTransform(LE3_GIZMO_AXIS_XZ));
    LE3GetAssetManager().getGizmoPlaneMesh().lock()->draw();
}
void LE3Gizmo::drawModeRotate(LE3ShaderPtr shaderOverride) {
    m_pMaterial.lock()->shader.lock()->uniform("gizmoAxis", (unsigned int)LE3_GIZMO_AXIS_X);
    m_pMaterial.lock()->shader.lock()->uniform("gizmoTransform", gizmoTransform(LE3_GIZMO_AXIS_X));
    LE3GetAssetManager().getGizmoCircleMesh().lock()->draw();

    m_pMaterial.lock()->shader.lock()->uniform("gizmoAxis", (unsigned int)LE3_GIZMO_AXIS_Y);
    m_pMaterial.lock()->shader.lock()->uniform("gizmoTransform", gizmoTransform(LE3_GIZMO_AXIS_Y));
    LE3GetAssetManager().getGizmoCircleMesh().lock()->draw();

    m_pMaterial.lock()->shader.lock()->uniform("gizmoAxis", (unsigned int)LE3_GIZMO_AXIS_Z);
    m_pMaterial.lock()->shader.lock()->uniform("gizmoTransform", gizmoTransform(LE3_GIZMO_AXIS_Z));
    LE3GetAssetManager().getGizmoCircleMesh().lock()->draw();
}
void LE3Gizmo::drawModeScale(LE3ShaderPtr shaderOverride) {
    m_pMaterial.lock()->shader.lock()->uniform("gizmoAxis", (unsigned int)LE3_GIZMO_AXIS_X);
    m_pMaterial.lock()->shader.lock()->uniform("gizmoTransform", gizmoTransform(LE3_GIZMO_AXIS_X));
    LE3GetAssetManager().getGizmoScaleArrowMesh().lock()->draw();

    m_pMaterial.lock()->shader.lock()->uniform("gizmoAxis", (unsigned int)LE3_GIZMO_AXIS_Y);
    m_pMaterial.lock()->shader.lock()->uniform("gizmoTransform", gizmoTransform(LE3_GIZMO_AXIS_Y));
    LE3GetAssetManager().getGizmoScaleArrowMesh().lock()->draw();

    m_pMaterial.lock()->shader.lock()->uniform("gizmoAxis", (unsigned int)LE3_GIZMO_AXIS_Z);
    m_pMaterial.lock()->shader.lock()->uniform("gizmoTransform", gizmoTransform(LE3_GIZMO_AXIS_Z));
    LE3GetAssetManager().getGizmoScaleArrowMesh().lock()->draw();

    m_pMaterial.lock()->shader.lock()->uniform("gizmoAxis", (unsigned int)LE3_GIZMO_AXIS_ALL);
    m_pMaterial.lock()->shader.lock()->uniform("gizmoTransform", gizmoTransform(LE3_GIZMO_AXIS_ALL));
    LE3GetAssetManager().getGizmoCenterMesh().lock()->draw();

    m_pMaterial.lock()->shader.lock()->uniform("gizmoAxis", (unsigned int)LE3_GIZMO_AXIS_XY);
    m_pMaterial.lock()->shader.lock()->uniform("gizmoTransform", gizmoTransform(LE3_GIZMO_AXIS_XY));
    LE3GetAssetManager().getGizmoPlaneMesh().lock()->draw();
    m_pMaterial.lock()->shader.lock()->uniform("gizmoAxis", (unsigned int)LE3_GIZMO_AXIS_YZ);
    m_pMaterial.lock()->shader.lock()->uniform("gizmoTransform", gizmoTransform(LE3_GIZMO_AXIS_YZ));
    LE3GetAssetManager().getGizmoPlaneMesh().lock()->draw();
    m_pMaterial.lock()->shader.lock()->uniform("gizmoAxis", (unsigned int)LE3_GIZMO_AXIS_XZ);
    m_pMaterial.lock()->shader.lock()->uniform("gizmoTransform", gizmoTransform(LE3_GIZMO_AXIS_XZ));
    LE3GetAssetManager().getGizmoPlaneMesh().lock()->draw();
}
// --------------------------------------------------------------------------------------------

void LE3Gizmo::updateStateDisabled(float deltaTime) {
    if (LE3GetEditorManager().getSelection().type == LE3EditorSelection::LE3_SELECTION_OBJECT) {
        m_state = LE3_GIZMO_STATE_IDLE;
        return;
    }
    
    // Note that if we are disabled, then nothing was selected, so no need to check for modifier keys
    if (LE3GetEditorManager().getHoveredObject().lock() && isMouseDown()) {
        LE3GetEditorManager().getSelection().selectObject(LE3GetEditorManager().getHoveredObject());
        m_state = LE3_GIZMO_STATE_IDLE;
        setHidden(true);
    }

}
void LE3Gizmo::updateStateIdle(float deltaTime) {
    if (LE3GetEditorManager().getSelection().type != LE3EditorSelection::LE3_SELECTION_OBJECT) {
        m_state = LE3_GIZMO_STATE_DISABLED;
        return;
    }
    // When updaing position outside of scene view, update gizmo position
    if (LE3ObjectPtr pObject = LE3GetEditorManager().getSelection().getLastSelectedObject().lock()) {
        m_transform.setPosition(pObject->getWorldPosition());
        if (isHidden()) setHidden(false);
    }

    // Gizmo hover update
    m_hoveredAxis = getHoveredAxis();


    // Re-select (if no hover)
    if (
        isMouseDown() &&
        m_hoveredAxis == LE3_GIZMO_AXIS_NONE) {
        bool bReset = !LE3GetEditorManager().isCtrlDown();
        LE3GetEditorManager().getSelection().selectObject(LE3GetEditorManager().getHoveredObject(), bReset);
        setHidden(true); // After selection, hide gizmo and only show after the position was updated
    }

    // Gizmo drag initialization handling (if hover)
    if (isMouseDown() && m_hoveredAxis != LE3_GIZMO_AXIS_NONE) {
        m_dragFrames++;
        if (m_dragFrames > 3) {
            m_state = LE3_GIZMO_STATE_DRAGGING;    
            m_dragCursortStart = glm::vec2(LE3GetActiveScene()->getCursorLocation());
            m_selectObjectsInitialTransform.clear();
            for (auto pObjectWeak : LE3GetEditorManager().getSelection().pObjects) {
                LE3ObjectPtr pObject = pObjectWeak.lock();
                if (!pObject) continue;
                m_selectObjectsInitialTransform[pObject->getName()] = pObject->getTransform().getTransformMatrix();
            }
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

    if (LE3ObjectPtr pObject = LE3GetEditorManager().getSelection().getLastSelectedObject().lock()) {
        m_transform.setPosition(pObject->getWorldPosition());
    }

    const float gizmoAxisLength = 0.565f;
    float gizmoDragSpeed = 4.0f;

    glm::mat4 projViewMatrix = LE3GetActiveScene()->getMainCamera()->getProjectionMatrix() * LE3GetActiveScene()->getMainCamera()->getViewMatrix();
    glm::mat4 modelMatrix = getWorldMatrix() * gizmoTransform(m_hoveredAxis);
    glm::vec3 pWorld = glm::vec3(modelMatrix * glm::vec4(0.f, 0.f, 0.f, 1.f));
    glm::vec3 qWorld = glm::vec3(modelMatrix * glm::vec4(0.f, 0.565f, 0.f, 1.f));
    glm::vec2 pScreen = worldToScreen(projViewMatrix, pWorld);
    glm::vec2 qScreen = worldToScreen(projViewMatrix, qWorld);

    glm::vec2 mouseCurr = glm::vec2(LE3GetActiveScene()->getCursorLocation());
    float dx = mouseCurr.x - m_dragCursortStart.x;
    float dy = mouseCurr.y - m_dragCursortStart.y;

    LE3EditorSnap snap = LE3GetEditorManager().getSnap();

    if (m_mode == LE3_GIZMO_MODE_TRANSLATE) {
        glm::vec3 projection(0.f);
        if (m_hoveredAxis == LE3_GIZMO_AXIS_X || m_hoveredAxis == LE3_GIZMO_AXIS_Y || m_hoveredAxis == LE3_GIZMO_AXIS_Z) {
            float t = gizmoDragSpeed * glm::dot(glm::vec2(dx, dy), glm::normalize(qScreen - pScreen));
            if (snap.enabled) t = glm::round(t / snap.snapTranslation) * snap.snapTranslation;
            projection = t * getAxisLine(m_hoveredAxis);
        }
        else {
            // Special treatment for [all axes / planes] on the translation case
            // (Project into each axis individually, and aggregate)
            const LE3GizmoAxis axes[] = { LE3_GIZMO_AXIS_X, LE3_GIZMO_AXIS_Y, LE3_GIZMO_AXIS_Z };
            for (LE3GizmoAxis axis : axes) {

                if (m_hoveredAxis == LE3_GIZMO_AXIS_XY && axis == LE3_GIZMO_AXIS_Z) continue;
                if (m_hoveredAxis == LE3_GIZMO_AXIS_XZ && axis == LE3_GIZMO_AXIS_Y) continue;
                if (m_hoveredAxis == LE3_GIZMO_AXIS_YZ && axis == LE3_GIZMO_AXIS_X) continue;

                glm::mat4 modelMatrix = getWorldMatrix() * gizmoTransform(axis);
                glm::vec3 pWorld = glm::vec3(modelMatrix * glm::vec4(0.f, 0.f, 0.f, 1.f));
                glm::vec3 qWorld = glm::vec3(modelMatrix * glm::vec4(0.f, gizmoAxisLength, 0.f, 1.f));
                glm::vec2 pScreen = worldToScreen(projViewMatrix, pWorld);
                glm::vec2 qScreen = worldToScreen(projViewMatrix, qWorld);

                float t = gizmoDragSpeed * glm::dot(glm::vec2(dx, dy), glm::normalize(qScreen - pScreen));
                if (snap.enabled) t = glm::round(t / snap.snapTranslation) * snap.snapTranslation;
                projection += t * getAxisLine(axis);
            }
        }
        for (auto pObjectWeak : LE3GetEditorManager().getSelection().pObjects) {
            LE3ObjectPtr pObject = pObjectWeak.lock();
            if (!pObject) continue;
            pObject->getTransform().setPosition(glm::vec3(m_selectObjectsInitialTransform[pObject->getName()][3]) + projection);
        }
    }
    if (m_mode == LE3_GIZMO_MODE_SCALE) {
        float t = gizmoDragSpeed * glm::dot(glm::vec2(dx, dy), glm::normalize(qScreen - pScreen));
        if (snap.enabled) t = glm::round(t / snap.snapScale) * snap.snapScale;
        glm::vec3 projection = t * getAxisLine(m_hoveredAxis);

        for (auto pObjectWeak : LE3GetEditorManager().getSelection().pObjects) {
            LE3ObjectPtr pObject = pObjectWeak.lock();
            if (!pObject) continue;
            glm::vec3 originalScale = glm::vec3(
                glm::length(m_selectObjectsInitialTransform[pObject->getName()][0]),
                glm::length(m_selectObjectsInitialTransform[pObject->getName()][1]),
                glm::length(m_selectObjectsInitialTransform[pObject->getName()][2]));
            pObject->getTransform().setScale(originalScale + projection);
        }
    }
    if (m_mode == LE3_GIZMO_MODE_ROTATE) {
        float tmp = 0.5 * (dx + dy);
        float t = gizmoDragSpeed * glm::dot(glm::vec2(tmp, tmp), glm::normalize(qScreen - pScreen));
        if (snap.enabled) {
            t = t / M_PI * 180.f;
            t = glm::round(t / snap.snapRotation) * snap.snapRotation;
            t = t / 180.f * M_PI;
        }
        glm::quat delta = glm::angleAxis(t, getAxisLine(m_hoveredAxis));
        for (auto pObjectWeak : LE3GetEditorManager().getSelection().pObjects) {
            LE3ObjectPtr pObject = pObjectWeak.lock();
            if (!pObject) continue;
            glm::quat originalRotation = rotFromMatrix(m_selectObjectsInitialTransform[pObject->getName()]);
            pObject->getTransform().setRotation(delta * originalRotation);
        }
    }

}
void LE3Gizmo::updateStateRelease(float deltaTime) {
    std::vector<std::string> objectNames;
    std::map<std::string, glm::mat4> deltaTransforms;
    for (auto pObjectWeak : LE3GetEditorManager().getSelection().pObjects) {
        LE3ObjectPtr pObject = pObjectWeak.lock();
        if (!pObject) continue;
        objectNames.push_back(pObject->getName());

        glm::mat4 objectTargetTransform = pObject->getTransform().getTransformMatrix();
        glm::mat4 deltaTransform = objectTargetTransform * glm::inverse(m_selectObjectsInitialTransform[pObject->getName()]);
        deltaTransforms[pObject->getName()] = deltaTransform;
        pObject->getTransform().fromTransformMatrix(m_selectObjectsInitialTransform[pObject->getName()]);
    }
    LE3GetEditorManager().getCommandStack().execute(std::make_unique<LE3GizmoReleaseCommand>(objectNames, deltaTransforms));
    m_state = LE3_GIZMO_STATE_IDLE;
}

bool LE3Gizmo::isMouseDown() {
    bool bMouseDown = LE3GetEditorManager().isMouseDown();
    bool bInsideViewport = LE3GetActiveScene()->getCursorLocation().z >= 0;

    // Lock mouse when started dragging outside of viewport
    if (!bMouseDown) m_bMouseDownLock = false;
    if (m_bMouseDownLock) return false;
    if (bMouseDown && !bInsideViewport) {
        m_bMouseDownLock = true;
        return false;
    }

    // Ignore when cursor is outside!
    if (!bInsideViewport) return false;
    return bMouseDown;
}

LE3GizmoAxis LE3Gizmo::getHoveredAxis() {
    if (!m_bIsHoverable) return LE3_GIZMO_AXIS_NONE;
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
    const LE3GizmoAxis planes[] = { LE3_GIZMO_AXIS_XY, LE3_GIZMO_AXIS_XZ, LE3_GIZMO_AXIS_YZ };
    const float gizmoAxisLength = 0.565f;
    const float gizmoSelectionThreshold = 0.05f;

    // First check for "all axes"
    glm::vec3 centerWorld = posFromMatrix(getWorldMatrix());
    glm::vec2 centerScreen = worldToScreen(projViewMatrix, centerWorld);
    if (glm::length(centerScreen - cursorPosition) < gizmoSelectionThreshold) return LE3_GIZMO_AXIS_ALL;

    // Then check for planes
    glm::vec3 planeCenter = glm::vec3(0.25f, 0.25f, 0.f);
    for (LE3GizmoAxis plane : planes) {
        glm::mat4 modelMatrix = getWorldMatrix() * gizmoTransform(plane);
        glm::vec3 pWorld = glm::vec3(modelMatrix * glm::vec4(planeCenter, 1.f));
        glm::vec2 pScreen = worldToScreen(projViewMatrix, pWorld);
        if (glm::length(pScreen - cursorPosition) < gizmoSelectionThreshold) return plane;
    }

    // Finally try for the axes themselves
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
    const LE3GizmoAxis axes[] = { LE3_GIZMO_AXIS_X, LE3_GIZMO_AXIS_Y, LE3_GIZMO_AXIS_Z };
    const float gizmoMajorRadius = 0.4f;
    const float gizmoSelectionThreshold = 0.05f;

    for (LE3GizmoAxis axis : axes) {
        std::vector<glm::vec2> pointsScreen;
        glm::mat4 modelMatrix = m_transform.getTransformMatrix() * gizmoTransform(axis);
        for (int i = 0; i < 32; i++) {
            float theta = (float)i / 31.f * 2.f * M_PI;
            glm::vec3 pWorld = glm::vec3(modelMatrix * glm::vec4(gizmoMajorRadius * cosf(theta), 0.f, gizmoMajorRadius * sinf(theta), 1.f));
            pointsScreen.push_back(worldToScreen(projViewMatrix, pWorld));
        }
        float dist = -1.f;
        for (int i = 0; i < pointsScreen.size(); i++) {
            glm::vec2 pScreen = pointsScreen[i];
            glm::vec2 qScreen = pointsScreen[(i+1) % pointsScreen.size()];
            float tmp = distancePointLineSegment(pScreen, qScreen, cursorPosition);
            if ((tmp < dist) || (dist < 0.f)) dist = tmp;
        }
        if (dist < gizmoSelectionThreshold) return axis;
    }

    return LE3_GIZMO_AXIS_NONE;
}