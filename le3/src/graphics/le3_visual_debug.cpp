#include "graphics/le3_visual_debug.h"
using namespace le3;

#include "core/le3_engine_systems.h"

#include <GL/glew.h>

void LE3VisualDebug::reset() {
    m_activeCamera = nullptr;
    m_bDrawDebugSkeletons = false;
}

void LE3VisualDebug::drawDebugMesh(std::weak_ptr<LE3DebugMesh> pMesh, glm::mat4 model, glm::vec3 color) {
    // TODO: Use this method for other visual debug methods
    if (!m_activeCamera) return;
    setupDebugShader(model, color);

    GLint polygonMode;
    glGetIntegerv(GL_POLYGON_MODE, &polygonMode);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    pMesh.lock()->draw();
    glPolygonMode(GL_FRONT_AND_BACK, polygonMode);
}

void LE3VisualDebug::drawDebugLine(glm::vec3 start, glm::vec3 end, glm::vec3 color) {
    if (!m_activeCamera) return;
    glm::mat4 model = glm::translate(glm::mat4(1.f), start) * glm::scale(glm::mat4(1.f), end - start);
    setupDebugShader(model, color);
    LE3GetAssetManager().getDebugLine().lock()->drawLines();
}

void LE3VisualDebug::drawDebugBox(glm::vec3 position, glm::quat rotation, glm::vec3 scale, glm::vec3 color) {
    if (!m_activeCamera) return;
    LE3Transform transform;
    transform.setPosition(position);
    transform.setRotation(rotation);
    transform.setScale(scale);
    drawDebugBox(transform.getTransformMatrix(), color);
}
void LE3VisualDebug::drawDebugBox(glm::mat4 modelMatrix, glm::vec3 color, bool drawDiagonal) {
    if (!m_activeCamera) return;
    setupDebugShader(modelMatrix, color);
    if (drawDiagonal) LE3GetAssetManager().getDebugBoxDiagonals().lock()->drawLines();
    else LE3GetAssetManager().getDebugBox().lock()->drawLines();
}

void LE3VisualDebug::drawDebugCylinder(glm::vec3 position, float radius, float height, glm::vec3 color) {
    if (!m_activeCamera) return;
    LE3Transform transform;
    transform.setPosition(position);
    transform.setScale(glm::vec3(radius, height, radius));
    setupDebugShader(transform.getTransformMatrix(), color);
    LE3GetAssetManager().getDebugCylinder().lock()->drawLines();
}

void LE3VisualDebug::drawDebugCone(glm::vec3 position, float radius, float height, glm::vec3 color) {
    if (!m_activeCamera) return;
    LE3Transform transform;
    transform.setPosition(position);
    transform.setScale(glm::vec3(radius, height, radius));
    setupDebugShader(transform.getTransformMatrix(), color);
    LE3GetAssetManager().getDebugCone().lock()->drawLines();
}

void LE3VisualDebug::drawDebugSphere(glm::mat4 modelMatrix, glm::vec3 color) {
    if (!m_activeCamera) return;
    setupDebugShader(modelMatrix, color);
    LE3GetAssetManager().getDebugSphere().lock()->drawLines();
}


// -------------------------------

void LE3VisualDebug::setupDebugShader(glm::mat4 modelMatrix, glm::vec3 color) {
    std::shared_ptr<LE3Shader> debugShader = LE3GetAssetManager().getShader(DEFAULT_DEBUG_SHADER).lock();
    debugShader->use();
    debugShader->uniform("view", m_activeCamera->getViewMatrix());
    debugShader->uniform("projection", m_activeCamera->getProjectionMatrix());
    debugShader->uniform("model", modelMatrix);
    debugShader->uniform("debugColor", color);
}