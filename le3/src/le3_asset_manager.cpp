#include "le3_asset_manager.h"
using namespace le3;

#include <stdexcept>

#include <fmt/core.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "le3_primitives.h"
#include "le3_engine_systems.h"

void LE3AssetManager::init() {
    m_screenRect = createScreenRect();
    
    m_debugLine = createDebugLine();
    m_debugBox = createDebugBox();
    m_debugCylinder = createDebugCylinder();
    m_debugCone = createDebugCone();

    m_gizmoArrow = createGizmoArrow();
    m_gizmoScaleArrow = createGizmoScaleArrow();
    m_gizmoCircle = createGizmoCircle();
    m_gizmoPlane = createGizmoPlane();
    m_gizmoCenter = createGizmoCenter();

    addShaderFromFile(DEFAULT_POSTPROCESS_SHADER, "/engine/shaders/postprocess/ppvert.vs", "/engine/shaders/postprocess/ppbasic.fs");
    addShaderFromFile(DEFAULT_SHADOWMAP_SHADER, "/engine/shaders/shadowmap/shadowmap.vs", "/engine/shaders/shadowmap/shadowmap.fs");
    addShaderFromFile(DEFAULT_DEBUG_SHADER, "/engine/shaders/debug/debug.vs", "/engine/shaders/debug/debug.fs");
    addShaderFromFile(DEFAULT_GIZMO_SHADER, "/engine/shaders/gizmo/gizmo.vs", "/engine/shaders/gizmo/gizmo.fs");
    addShaderFromFile(DEFAULT_OBJECTID_SHADER, "/engine/shaders/objectid/objectid.vs", "/engine/shaders/objectid/objectid.fs");
    addShaderFromFile(DEFAULT_SPRITE_SHADER, "/engine/shaders/sprite/sprite.vs", "/engine/shaders/sprite/sprite.fs");
    // addShaderFromFile(DEFAULT_SPRITE_SHADER, "/engine/shaders/objectid/objectid.vs", "/engine/shaders/objectid/objectid.fs");

    addMaterial(DEFAULT_GIZMO_MATERIAL, DEFAULT_GIZMO_SHADER);
    addMaterial(DEFAULT_SPRITE_MATERIAL, DEFAULT_SPRITE_SHADER);

    addTexture(SPRITE_AMBIENT_LIGHT, "/engine/sprites/sprite_ambient.png");
    addTexture(SPRITE_DIRECTIONAL_LIGHT, "/engine/sprites/sprite_directional.png");
    addTexture(SPRITE_POINT_LIGHT, "/engine/sprites/sprite_point.png");
    addTexture(SPRITE_SPOT_LIGHT, "/engine/sprites/sprite_spot.png");
}

void LE3AssetManager::addShaderFromFile(std::string name, std::string vertexShaderPath, std::string fragmentShaderPath) {
    std::string vertexShaderSource = readFile(vertexShaderPath);
    std::string fragmentShaderSource = readFile(fragmentShaderPath);
    addShaderFromSource(name, vertexShaderSource, fragmentShaderSource);
    m_shadersPaths[name] = std::make_pair(vertexShaderPath, fragmentShaderPath);
}
void LE3AssetManager::addShaderFromSource(std::string name, std::string vertexShaderSource, std::string fragmentShaderSource) {
    if (m_pShaders.contains(name)) throw std::runtime_error(fmt::format("Shader [{}] already exists", name));
    m_pShaders[name] = std::make_shared<LE3Shader>(vertexShaderSource, fragmentShaderSource);
    m_pShaders[name]->setName(name);
}

void LE3AssetManager::addMaterial(std::string name, std::string shaderName) {
    if (m_pMaterials.contains(name)) throw std::runtime_error(fmt::format("Material [{}] already exists", name));
    if (!m_pShaders.contains(shaderName)) throw std::runtime_error(fmt::format("Cannot create material [{}]: shader [{}] does not exist", name, shaderName));
    m_pMaterials[name] = std::make_shared<LE3Material>(m_pShaders[shaderName]);
    m_pMaterials[name]->name = name;
}

void LE3AssetManager::addTexture(std::string name, std::vector<unsigned char> data, int width, int height, int nChannels, bool interpolate) {
    if (m_pTextures.contains(name)) throw std::runtime_error(fmt::format("Texture [{}] already exists", name));
    m_pTextures[name] = std::make_shared<LE3Texture>(data, width, height, nChannels, interpolate);
    m_pTextures[name]->setName(name);
}

void LE3AssetManager::addTexture(std::string name, std::string filename, bool interpolate) {
    int width, height, nChannels;
    unsigned char* rawData;
    LE3DatBuffer buffer = LE3GetDatFileSystem().getFileContent(filename);
    // rawData = stbi_load(filename.c_str(), &width, &height, &nChannels, 0);
    rawData = stbi_load_from_memory((uint8_t*)&buffer.data[0], buffer.data.size(), &width, &height, &nChannels, 0);
    if (!rawData) throw std::runtime_error(fmt::format("Could not load texture from path: {}", filename));
    // std::copy(&rawData[0], &rawData[width * height * nChannels - 1], std::back_inserter(data));
    // data.reserve(width * height * nChannels);
    // memcpy(&data[0], rawData, width * height * nChannels);
    std::vector<unsigned char> data(rawData, rawData + width * height * nChannels);
    addTexture(name, data, width, height, nChannels, interpolate);
    stbi_image_free(rawData);
    m_texturesPaths[name] = filename;
}

void LE3AssetManager::addStaticMesh(std::string name, std::string filename, bool keepData) {
    if (m_pStaticMeshes.contains(name)) throw std::runtime_error(fmt::format("Static mesh [{}] already exists", name));
    m_pStaticMeshes[name] = loadStaticMesh(filename, keepData);
    m_meshesPaths[name] = filename;
}

void LE3AssetManager::searchStaticMeshes(std::string prefix, std::vector<std::string>& out) {
    for (auto [name, mesh] : m_pStaticMeshes) {
        if (name.find(prefix) == 0) out.push_back(name);
    }
}


void LE3AssetManager::addSkeletalMesh(std::string name, std::string filename) {
    if (m_pSkeletalMeshes.contains(name)) throw std::runtime_error(fmt::format("Skeletal mesh [{}] already exists", name));
    m_pSkeletalMeshes[name] = loadSkeletalMesh(filename);
    m_meshesPaths[name] = filename;
}

bool LE3AssetManager::isSkeletalMesh(std::string name) {
    return m_pSkeletalMeshes.contains(name);
}

std::string LE3AssetManager::readFile(std::string filename) {
    return LE3GetDatFileSystem().getFileContent(filename).toString();
}