#include "le3_visual_debug.h"
using namespace le3;

#include "le3_engine_systems.h"

#include <GL/glew.h>

void LE3VisualDebug::drawDebugLine(glm::vec3 start, glm::vec3 end, glm::vec3 color) {
    if (!m_activeCamera) return;
    glm::mat4 model = glm::translate(glm::mat4(1.f), start) * glm::scale(glm::mat4(1.f), end - start);
    setupDebugShader(model, color);
    LE3GetAssetManager().getDebugLine()->drawLines();
}

void LE3VisualDebug::drawDebugBox(glm::vec3 position, glm::quat rotation, glm::vec3 scale, glm::vec3 color) {
    if (!m_activeCamera) return;
    LE3Transform transform;
    transform.setPosition(position);
    transform.setRotation(rotation);
    transform.setScale(scale);
    drawDebugBox(transform.getTransformMatrix(), color);
}
void LE3VisualDebug::drawDebugBox(glm::mat4 modelMatrix, glm::vec3 color) {
    if (!m_activeCamera) return;
    setupDebugShader(modelMatrix, color);
    LE3GetAssetManager().getDebugBox()->drawLines();
}

void LE3VisualDebug::drawDebugCylinder(glm::vec3 position, float radius, float height, glm::vec3 color) {
    if (!m_activeCamera) return;
    LE3Transform transform;
    transform.setPosition(position);
    transform.setScale(glm::vec3(radius, height, radius));
    setupDebugShader(transform.getTransformMatrix(), color);
    LE3GetAssetManager().getDebugCylinder()->drawLines();
}

void LE3VisualDebug::drawDebugCone(glm::vec3 position, float radius, float height, glm::vec3 color) {
    if (!m_activeCamera) return;
    LE3Transform transform;
    transform.setPosition(position);
    transform.setScale(glm::vec3(radius, height, radius));
    setupDebugShader(transform.getTransformMatrix(), color);
    LE3GetAssetManager().getDebugCone()->drawLines();
}


// -------------------------------

void LE3VisualDebug::setupDebugShader(glm::mat4 modelMatrix, glm::vec3 color) {
    LE3ShaderPtr debugShader = LE3GetAssetManager().getShader(DEFAULT_DEBUG_SHADER);
    debugShader->use();
    debugShader->uniform("view", m_activeCamera->getViewMatrix());
    debugShader->uniform("projection", m_activeCamera->getProjectionMatrix());
    debugShader->uniform("model", modelMatrix);
    debugShader->uniform("debugColor", color);
}