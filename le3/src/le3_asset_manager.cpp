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

    addShaderFromFile(ERROR_SHADER, ERROR_SHADER_VERTEX_PATH, ERROR_SHADER_FRAGMENT_PATH);
    addTexture(ERROR_TEXTURE, ERROR_TEXTURE_PATH);
    addMaterial(ERROR_MATERIAL, ERROR_SHADER);
    m_gErrorShader = getShader(ERROR_SHADER).lock(); // Even if user deletes that shader from assets, we should still have a reference to it
    m_gErrorTexture = getTexture(ERROR_TEXTURE).lock(); // Same here, etc.
    m_gErrorMaterial = getMaterial(ERROR_MATERIAL).lock();

    addShaderFromFile(DEFAULT_SHADER, "/engine/shaders/blinn_phong/blinn_phong.vs", "/engine/shaders/blinn_phong/blinn_phong.fs");
    addShaderFromFile(DEFAULT_POSTPROCESS_SHADER, "/engine/shaders/postprocess/ppvert.vs", "/engine/shaders/postprocess/ppbasic.fs");
    addShaderFromFile(DEFAULT_SHADOWMAP_SHADER, "/engine/shaders/shadowmap/shadowmap.vs", "/engine/shaders/shadowmap/shadowmap.fs");
    addShaderFromFile(DEFAULT_DEBUG_SHADER, "/engine/shaders/debug/debug.vs", "/engine/shaders/debug/debug.fs");
    addShaderFromFile(DEFAULT_GIZMO_SHADER, "/engine/shaders/gizmo/gizmo.vs", "/engine/shaders/gizmo/gizmo.fs");
    addShaderFromFile(DEFAULT_OBJECTID_SHADER, "/engine/shaders/objectid/objectid.vs", "/engine/shaders/objectid/objectid.fs");
    addShaderFromFile(DEFAULT_SPRITE_SHADER, "/engine/shaders/sprite/sprite.vs", "/engine/shaders/sprite/sprite.fs");
    addShaderFromFile(DEFAULT_PCD_SHADER, "/engine/shaders/pcd/pcd.vs", "/engine/shaders/pcd/pcd.fs");

    addMaterial(DEFAULT_MATERIAL, DEFAULT_SHADER);
    addMaterial(DEFAULT_GIZMO_MATERIAL, DEFAULT_GIZMO_SHADER);
    addMaterial(DEFAULT_SPRITE_MATERIAL, DEFAULT_SPRITE_SHADER);
    addMaterial(DEFAULT_PCD_MATERIAL, DEFAULT_PCD_SHADER);
    getMaterial(DEFAULT_PCD_MATERIAL).lock()->specularIntensity = 0.0f;

    addTexture(SPRITE_AMBIENT_LIGHT, "/engine/sprites/sprite_ambient.png");
    addTexture(SPRITE_DIRECTIONAL_LIGHT, "/engine/sprites/sprite_directional.png");
    addTexture(SPRITE_POINT_LIGHT, "/engine/sprites/sprite_point.png");
    addTexture(SPRITE_SPOT_LIGHT, "/engine/sprites/sprite_spot.png");
}
void LE3AssetManager::reset() {
    m_pShaders.clear();
    m_pMaterials.clear();
    m_pTextures.clear();
    m_pStaticMeshes.clear();
    m_pSkeletalMeshes.clear();
    m_shadersPaths.clear();
    m_texturesPaths.clear();
    m_meshesPaths.clear();

    m_screenRect = nullptr;
    m_debugLine = nullptr;
    m_debugBox = nullptr;
    m_debugCylinder = nullptr;
    m_debugCone = nullptr;
    m_gizmoArrow = nullptr;
    m_gizmoScaleArrow = nullptr;
    m_gizmoCircle = nullptr;
    m_gizmoPlane = nullptr;
    m_gizmoCenter = nullptr;
    m_gErrorShader = nullptr;
    m_gErrorTexture = nullptr;
    m_gErrorMaterial = nullptr;
    m_lastDeletedShader = "";
    m_lastDeletedTexture = ""; 
    m_lastDeletedMaterial = ""; 
    m_lastDeletedStaticMesh = ""; m_lastDeletedSkeletalMesh = "";
}

void LE3AssetManager::addShaderFromFile(std::string name, std::string vertexShaderPath, std::string fragmentShaderPath) {
    try {
        std::string vertexShaderSource = readFile(vertexShaderPath);
        std::string fragmentShaderSource = readFile(fragmentShaderPath);
        addShaderFromSource(name, vertexShaderSource, fragmentShaderSource);
    } catch (std::runtime_error& e) {
        fmt::print("Error loading shader from file: {}\n", e.what());
        addShaderFromSource(name, "", "");
    }
    m_shadersPaths[name] = std::make_pair(vertexShaderPath, fragmentShaderPath);
}
void LE3AssetManager::addShaderFromSource(std::string name, std::string vertexShaderSource, std::string fragmentShaderSource) {
    if (m_pShaders.contains(name)) throw std::runtime_error(fmt::format("Shader [{}] already exists", name));
    m_pShaders[name] = std::make_shared<LE3Shader>(vertexShaderSource, fragmentShaderSource);
    m_pShaders[name]->setName(name);
}

void LE3AssetManager::renameShader(std::string oldName, std::string newName) {
    if (oldName == newName) return;
    if (m_pShaders.contains(oldName)) {
        m_pShaders[oldName]->setName(newName);
        m_pShaders[newName] = m_pShaders[oldName];
        m_pShaders.erase(oldName);
    }
    if (m_shadersPaths.contains(oldName)) {
        m_shadersPaths[newName] = m_shadersPaths[oldName];
        m_shadersPaths.erase(oldName);
    }
}
void LE3AssetManager::deleteShader(std::string name) {
    if (m_pShaders.contains(name)) m_pShaders.erase(name);
    if (m_shadersPaths.contains(name)) m_shadersPaths.erase(name);
    m_lastDeletedShader = name;
    refreshPointers();
}

void LE3AssetManager::addMaterial(std::string name, std::string shaderName) {
    if (m_pMaterials.contains(name)) throw std::runtime_error(fmt::format("Material [{}] already exists", name));
    if (!m_pShaders.contains(shaderName)) throw std::runtime_error(fmt::format("Cannot create material [{}]: shader [{}] does not exist", name, shaderName));
    m_pMaterials[name] = std::make_shared<LE3Material>(m_pShaders[shaderName]);
    m_pMaterials[name]->name = name;
}

void LE3AssetManager::renameMaterial(std::string oldName, std::string newName) {
    if (oldName == newName) return;
    if (m_pMaterials.contains(oldName)) {
        m_pMaterials[oldName]->name = newName;
        m_pMaterials[newName] = m_pMaterials[oldName];
        m_pMaterials.erase(oldName);
    }
}
void LE3AssetManager::deleteMaterial(std::string name) {
    if (m_pMaterials.contains(name)) m_pMaterials.erase(name);
    m_lastDeletedMaterial = name;
    refreshPointers();
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
    rawData = stbi_load_from_memory((uint8_t*)&buffer.data[0], buffer.data.size(), &width, &height, &nChannels, 0);
    if (!rawData) throw std::runtime_error(fmt::format("Could not load texture from path: {}", filename));
    std::vector<unsigned char> data(rawData, rawData + width * height * nChannels);
    addTexture(name, data, width, height, nChannels, interpolate);
    stbi_image_free(rawData);
    m_texturesPaths[name] = filename;
}

void LE3AssetManager::reloadTexture(std::string name, std::string filename, bool interpolate) {
    int width, height, nChannels;
    unsigned char* rawData;
    LE3DatBuffer buffer = LE3GetDatFileSystem().getFileContent(filename);
    rawData = stbi_load_from_memory((uint8_t*)&buffer.data[0], buffer.data.size(), &width, &height, &nChannels, 0);
    if (!rawData) throw std::runtime_error(fmt::format("Could not load texture from path: {}", filename));
    std::vector<unsigned char> data(rawData, rawData + width * height * nChannels);
    m_pTextures[name]->load(data, width, height, nChannels, interpolate);
    stbi_image_free(rawData);
}

void LE3AssetManager::renameTexture(std::string oldName, std::string newName) {
    if (oldName == newName) return;
    if (m_pTextures.contains(oldName)) {
        m_pTextures[oldName]->setName(newName);
        m_pTextures[newName] = m_pTextures[oldName];
        m_pTextures.erase(oldName);
    }
    if (m_texturesPaths.contains(oldName)) {
        m_texturesPaths[newName] = m_texturesPaths[oldName];
        m_texturesPaths.erase(oldName);
    }
}

void LE3AssetManager::deleteTexture(std::string name) {
    if (m_pTextures.contains(name)) m_pTextures.erase(name);
    if (m_texturesPaths.contains(name)) m_texturesPaths.erase(name);
    m_lastDeletedTexture = name;
    refreshPointers();
}

void LE3AssetManager::addStaticMesh(std::string name, std::string filename, bool keepData) {
    if (m_pStaticMeshes.contains(name)) throw std::runtime_error(fmt::format("Static mesh [{}] already exists", name));
    m_pStaticMeshes[name] = loadStaticMesh(filename, keepData);
    m_pStaticMeshes[name]->setName(name);
    m_meshesPaths[name] = filename;
}

void LE3AssetManager::searchStaticMeshes(std::string prefix, std::vector<std::string>& out) {
    for (auto [name, mesh] : m_pStaticMeshes) {
        if (name.find(prefix) == 0) out.push_back(name);
    }
}
void LE3AssetManager::reloadStaticMesh(std::string name, std::string filename, bool keepData) {
    reloadStaticMesh(m_pStaticMeshes[name], filename, keepData);
    m_meshesPaths[name] = filename;
}
void LE3AssetManager::renameStaticMesh(std::string oldName, std::string newName) {
    if (oldName == newName) return;
    if (m_pStaticMeshes.contains(oldName)) {
        m_pStaticMeshes[oldName]->setName(newName);
        m_pStaticMeshes[newName] = m_pStaticMeshes[oldName];
        m_pStaticMeshes.erase(oldName);
    }
    if (m_meshesPaths.contains(oldName)) {
        m_meshesPaths[newName] = m_meshesPaths[oldName];
        m_meshesPaths.erase(oldName);
    }
}
void LE3AssetManager::deleteStaticMesh(std::string name) {
    if (m_pStaticMeshes.contains(name)) m_pStaticMeshes.erase(name);
    if (m_meshesPaths.contains(name)) m_meshesPaths.erase(name);
    m_lastDeletedStaticMesh = name;
    refreshPointers();
}


void LE3AssetManager::addSkeletalMesh(std::string name, std::string filename) {
    if (m_pSkeletalMeshes.contains(name)) throw std::runtime_error(fmt::format("Skeletal mesh [{}] already exists", name));
    m_pSkeletalMeshes[name] = loadSkeletalMesh(filename);
    m_pSkeletalMeshes[name]->setName(name);
    m_meshesPaths[name] = filename;
}

bool LE3AssetManager::isSkeletalMesh(std::string name) {
    return m_pSkeletalMeshes.contains(name);
}

void LE3AssetManager::reloadSkeletalMesh(std::string name, std::string filename) {
    reloadSkeletalMesh(m_pSkeletalMeshes[name], filename);
    m_meshesPaths[name] = filename;
}
void LE3AssetManager::renameSkeletalMesh(std::string oldName, std::string newName) {
    if (oldName == newName) return;
    if (m_pSkeletalMeshes.contains(oldName)) {
        m_pSkeletalMeshes[oldName]->setName(newName);
        m_pSkeletalMeshes[newName] = m_pSkeletalMeshes[oldName];
        m_pSkeletalMeshes.erase(oldName);
    }
    if (m_meshesPaths.contains(oldName)) {
        m_meshesPaths[newName] = m_meshesPaths[oldName];
        m_meshesPaths.erase(oldName);
    }
}
void LE3AssetManager::deleteSkeletalMesh(std::string name) {
    if (m_pSkeletalMeshes.contains(name)) m_pSkeletalMeshes.erase(name);
    if (m_meshesPaths.contains(name)) m_meshesPaths.erase(name);
    m_lastDeletedSkeletalMesh = name;
    refreshPointers();
}

std::string LE3AssetManager::readFile(std::string filename) {
    return LE3GetDatFileSystem().getFileContent(filename).toString();
}

void LE3AssetManager::refreshPointers() {
    for (auto& [name, material] : m_pMaterials) {
        // The second condition seems weird, but since Lua binding sometimes also temporarily holds
        // a shared reference, the pointer is not immideatly deleted, hence this trick
        if (m_pMaterials[name]->shader.expired() || m_pMaterials[name]->shader.lock()->getName() == m_lastDeletedShader) {
            m_pMaterials[name]->shader = getErrorShader();
        }

        if ((m_pMaterials[name]->diffuseTexture.expired() && m_pMaterials[name]->bUseDiffuseTexture) ||
            (!m_pMaterials[name]->diffuseTexture.expired() && m_pMaterials[name]->diffuseTexture.lock()->getName() == m_lastDeletedTexture)) {
            m_pMaterials[name]->diffuseTexture = getErrorTexture();
        }
        if ((m_pMaterials[name]->specularTexture.expired() && m_pMaterials[name]->bUseSpecularTexture) ||
            (!m_pMaterials[name]->specularTexture.expired() && m_pMaterials[name]->specularTexture.lock()->getName() == m_lastDeletedTexture)) {
            m_pMaterials[name]->specularTexture = getErrorTexture();
        }
        if ((m_pMaterials[name]->normalTexture.expired() && m_pMaterials[name]->bUseNormalTexture) ||
            (!m_pMaterials[name]->normalTexture.expired() && m_pMaterials[name]->normalTexture.lock()->getName() == m_lastDeletedTexture)) {
            m_pMaterials[name]->normalTexture = getErrorTexture();
        }
        if ((m_pMaterials[name]->cubemap.expired() && m_pMaterials[name]->reflectionIntensity > 0) ||
            (!m_pMaterials[name]->cubemap.expired() && m_pMaterials[name]->cubemap.lock()->getName() == m_lastDeletedTexture)) {
            m_pMaterials[name]->cubemap = getErrorTexture();
        }
    }

    // Also rebuild data structures that depend on these assets
    // (and especially materials and meshes)
    for (auto& [name, scene] : LE3GetSceneManager().getScenes()) {
        scene->propagateDeleteMaterial(m_lastDeletedMaterial);
        scene->rebuild();
    }


    m_lastDeletedShader = "";
    m_lastDeletedTexture = "";
    m_lastDeletedMaterial = "";
    m_lastDeletedStaticMesh = "";
    m_lastDeletedSkeletalMesh = "";
}