#include "graphics/le3_point_cloud.h"
#include "core/le3_engine_systems.h"
using namespace le3;


LE3PointCloud::LE3PointCloud() :
    LE3DrawableObject(LE3MaterialPtr()), m_pointSize(1.f), m_opacity(1.f) {
    setMaterial(LE3GetAssetManager().getMaterial(DEFAULT_PCD_MATERIAL));
    setCastShadow(false);
}


void LE3PointCloud::update(float deltaTime) {
    LE3DrawableObject::update(deltaTime);
}


void LE3PointCloud::draw(LE3ShaderPtr shaderOverride) {
    if (m_pMaterial.lock()) m_pMaterial.lock()->apply();
    if (m_pMaterial.lock() && !shaderOverride.lock()) shaderOverride = m_pMaterial.lock()->shader;
    shaderOverride.lock()->uniform("bIsSkeletal", (uint32_t)0);
    shaderOverride.lock()->uniform("opacity", m_opacity);
    m_pMesh->drawPoints(m_pointSize);
}

void LE3PointCloud::addPoint(glm::vec3 position) {
    addPoint(position, glm::vec3(1.f, 0.f, 0.f), glm::vec3(0.7f, 0.7f, 0.7f));
}
void LE3PointCloud::addPoint(glm::vec3 position, glm::vec3 normal) {
    addPoint(position, normal, glm::vec3(0.7f, 0.7f, 0.7f));
}
void LE3PointCloud::addPoint(glm::vec3 position, glm::vec3 normal, glm::vec3 color) {
    m_points.push_back(vertexFromGLMColor(position, normal, color));
}
void LE3PointCloud::addPoints(std::vector<glm::vec3> positions) {
    addPoints(positions, glm::vec3(1.f, 0.f, 0.f));
}
void LE3PointCloud::addPoints(std::vector<glm::vec3> positions, glm::vec3 normal) {
    addPoints(positions, normal, glm::vec3(0.7f, 0.7f, 0.7f));
}
void LE3PointCloud::addPoints(std::vector<glm::vec3> positions, glm::vec3 normal, glm::vec3 color) {
    std::vector<glm::vec3> normals;
    std::vector<glm::vec3> colors;
    for (size_t i = 0; i < positions.size(); ++i) {
        normals.push_back(normal);
        colors.push_back(color);
    }
    addPoints(positions, normals, colors);
}
void LE3PointCloud::addPoints(std::vector<glm::vec3> positions, std::vector<glm::vec3> normals) {
    std::vector<glm::vec3> colors;
    for (size_t i = 0; i < positions.size(); ++i) {
        colors.push_back(glm::vec3(0.7f, 0.7f, 0.7f));
    }
    addPoints(positions, normals, colors);
}
void LE3PointCloud::addPoints(std::vector<glm::vec3> positions, std::vector<glm::vec3> normals, std::vector<glm::vec3> colors) {
    for (size_t idx = 0; idx < positions.size(); ++idx) {
        m_points.push_back(vertexFromGLMColor(positions[idx], normals[idx], colors[idx]));
    } 
}
void LE3PointCloud::clear() {
    m_points.clear();
}

void LE3PointCloud::create() {
    m_pMesh = std::make_shared<LE3Mesh<LE3Vertex3p2t3n3c>>(m_points);
}

void LE3PointCloud::fromFile(std::string filename, bool swapYZ) {
    std::vector<glm::vec3> points, normals, colors;
    LE3GetAssetManager().loadPointCloud(points, normals, colors, filename);
    if (swapYZ) {
        for (auto& p : points) {
            float tmp = p.y;
            // p.x *= -1.f;
            p.y = p.z;
            p.z = -tmp;
        }
    }
    addPoints(points, normals, colors);
}