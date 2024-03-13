#include "le3_point_cloud.h"
using namespace le3;


LE3PointCloud::LE3PointCloud(LE3MaterialPtr pMaterial) :
    LE3DrawableObject(pMaterial), m_pointSize(1.f) {
}


void LE3PointCloud::update(float deltaTime) {
    LE3DrawableObject::update(deltaTime);
}


void LE3PointCloud::draw(LE3ShaderPtr shaderOverride) {
    if (m_pMaterial) m_pMaterial->apply();
    if (m_pMaterial && !shaderOverride) shaderOverride = m_pMaterial->shader;
    shaderOverride->uniform("bIsSkeletal", (uint32_t)0);
    if (m_pMesh) m_pMesh->drawPoints(m_pointSize);
}

void LE3PointCloud::addPoint(glm::vec3 position) {
    addPoint(position, glm::vec3(1.f, 0.f, 0.f));
}
void LE3PointCloud::addPoint(glm::vec3 position, glm::vec3 normal) {
    m_points.push_back(vertexFromGLM(position, glm::vec2(), normal));
}
void LE3PointCloud::addPoints(std::vector<glm::vec3> positions) {
    addPoints(positions, glm::vec3(1.f, 0.f, 0.f));
}
void LE3PointCloud::addPoints(std::vector<glm::vec3> positions, glm::vec3 normal) {
    std::vector<glm::vec3> normals;
    for (size_t i = 0; i < positions.size(); ++i) normals.push_back(normal);
    addPoints(positions, normals);
}
void LE3PointCloud::addPoints(std::vector<glm::vec3> positions, std::vector<glm::vec3> normals) {
    for (size_t idx = 0; idx < positions.size(); ++idx) {
        m_points.push_back(vertexFromGLM(positions[idx], glm::vec2(), normals[idx]));
    } 
}
void LE3PointCloud::clear() {
    m_points.clear();
}

void LE3PointCloud::create() {
    m_pMesh = std::make_shared<LE3StaticMesh>(m_points);
}