#include "le3_scene.h"
using namespace le3;

#include <fstream>
#include <sstream>
#include <stdexcept>

#include <fmt/core.h>
using fmt::format;

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

void LE3Scene::init() {
    m_pRoot = std::make_shared<LE3SceneRoot>();
    m_pMainCamera = nullptr;
}
void LE3Scene::reset() {
    m_pShaders.clear();
    m_pObjects.clear();
    m_pPrototypes.clear();
    init();
}

void LE3Scene::update(float deltaTime) {
    m_pRoot->update(deltaTime);
}
void LE3Scene::draw(LE3ShaderPtr shaderOverride) {
    if (shaderOverride == nullptr) for (auto kv : m_pShaders) applyMainCamera(kv.second);
    else applyMainCamera(shaderOverride);
    m_drawQueue.draw(shaderOverride);
}

void LE3Scene::addShaderFromFile(std::string name, std::string vertexShaderPath, std::string fragmentShaderPath) {
    std::string vertexShaderSource = readFile(vertexShaderPath);
    std::string fragmentShaderSource = readFile(fragmentShaderPath);
    addShaderFromSource(name, vertexShaderSource, fragmentShaderSource);
}
void LE3Scene::addShaderFromSource(std::string name, std::string vertexShaderSource, std::string fragmentShaderSource) {
    if (m_pShaders.contains(name)) throw std::runtime_error(format("Shader [{}] already exists", name));
    m_pShaders[name] = std::make_shared<LE3Shader>(vertexShaderSource, fragmentShaderSource);
}

void LE3Scene::addMaterial(std::string name, std::string shaderName) {
    if (m_pMaterials.contains(name)) throw std::runtime_error(format("Material [{}] already exists", name));
    if (!m_pShaders.contains(shaderName)) throw std::runtime_error(format("Cannot create material [{}]: shader [{}] does not exist", name, shaderName));
    m_pMaterials[name] = std::make_shared<LE3Material>(m_pShaders[shaderName]);
}

void LE3Scene::addTexture(std::string name, std::vector<unsigned char> data, int width, int height, int nChannels, bool interpolate) {
    if (m_pTextures.contains(name)) throw std::runtime_error(format("Texture [{}] already exists", name));
    m_pTextures[name] = std::make_shared<LE3Texture>(data, width, height, nChannels, interpolate);
}
void LE3Scene::addTexture(std::string name, std::string filename, bool interpolate) {
    int width, height, nChannels;
    unsigned char* rawData;
    std::vector<unsigned char> data;

    LE3DatBuffer buffer = LE3EngineSystems::instance().getDatFilesystem().getFileContent(filename);
    // rawData = stbi_load(filename.c_str(), &width, &height, &nChannels, 0);
    rawData = stbi_load_from_memory((u_char*)&buffer.data[0], buffer.data.size(), &width, &height, &nChannels, 0);
    if (!rawData) throw std::runtime_error(format("Could not load texture from path: {}", filename));
    std::copy(&rawData[0], &rawData[width * height * nChannels - 1], std::back_inserter(data));
    stbi_image_free(rawData);
    addTexture(name, data, width, height, nChannels, interpolate);
}

void LE3Scene::addStaticMesh(std::string name, std::string filename) {
    if (m_pStaticMeshes.contains(name)) throw std::runtime_error(format("Static mesh [{}] already exists", name));
    m_pStaticMeshes[name] = loadStaticMesh(filename);
}

// -----------

void LE3Scene::addEmptyObject(std::string name, std::string parent) {
    assertObjectName(name);
    LE3ObjectPtr obj = std::make_shared<LE3Object>();
    attachObject(name, obj, parent);
}


void LE3Scene::addCube(std::string name, std::string materialName, glm::vec3 position, glm::vec3 extent, std::string parent) {
    assertObjectName(name);
    LE3StaticMeshPtr mesh = createBox(position.x, position.y, position.z, extent.x, extent.y, extent.z);
    LE3StaticModelPtr obj = std::make_shared<LE3StaticModel>(mesh, m_pMaterials[materialName]); // TODO: engine default shader + material
    attachObject(name, obj, parent);
    m_drawQueue.addObject(obj);
}

void LE3Scene::addStaticModel(std::string name, std::string meshName, std::string materialName, std::string parent) {
    assertObjectName(name);
    LE3StaticMeshPtr mesh = m_pStaticMeshes[meshName];
    LE3StaticModelPtr obj = std::make_shared<LE3StaticModel>(mesh, m_pMaterials[materialName]);
    attachObject(name, obj, parent);
    m_drawQueue.addObject(obj);
}


void LE3Scene::addFreeCamera(std::string name, std::string parent) {
    assertObjectName(name);
    LE3CameraPtr obj = std::make_shared<LE3FreeCamera>();
    attachObject(name, obj, parent);
    attachCamera(obj);
    
}
void LE3Scene::addOrbitCamera(std::string name, std::string parent) {
    assertObjectName(name);
    LE3CameraPtr obj = std::make_shared<LE3OrbitCamera>();
    attachObject(name, obj, parent);
    attachCamera(obj);
}

// --------------------------------------------------------------------------------

std::string LE3Scene::readFile(std::string filename) {
    // std::ifstream ifs(filename);
    // if (!ifs.good()) throw std::runtime_error(format("Could not open file:\n\t{}\n", filename));
    // std::stringstream ss;
    // ss << ifs.rdbuf();
    // return ss.str();
    return LE3EngineSystems::instance().getDatFilesystem().getFileContent(filename).toString();
}

void LE3Scene::assertObjectName(std::string name) { 
    if (name.size() == 0) throw std::runtime_error(format("Empty name is not allowed"));
    if (m_pObjects.contains(name)) throw std::runtime_error(format("Object '{}' already exists", name));
}

void LE3Scene::attachObject(std::string name, LE3ObjectPtr obj, std::string parent) {
    m_pObjects[name] = obj;
    LE3ObjectPtr pParent = m_pRoot;
    if (m_pObjects.contains(parent)) pParent = m_pObjects[parent];
    obj->reparent(pParent);
}

void LE3Scene::attachCamera(LE3CameraPtr pCamera) {
    if (m_pMainCamera == nullptr) m_pMainCamera = pCamera;
}

void LE3Scene::applyMainCamera(LE3ShaderPtr shader) {
    if (!m_pMainCamera) return;
    shader->use();
    shader->uniform("view", m_pMainCamera->getViewMatrix());
    shader->uniform("projection", m_pMainCamera->getProjectionMatrix());
    shader->uniform("cameraPos", glm::vec3(m_pMainCamera->getWorldMatrix()[3]));
}

void LE3Scene::setMainCamera(std::string camera) {
    if (!m_pObjects.contains(camera)) throw std::runtime_error(format("Object '{}' does not exist", camera));
    LE3CameraPtr pCamera = std::dynamic_pointer_cast<LE3Camera>(m_pObjects[camera]);
    if (!pCamera) throw std::runtime_error(format("Object '{}' is not a camera", camera));
    m_pMainCamera = pCamera;
}