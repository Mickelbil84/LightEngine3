#include "le3_scene.h"
using namespace le3;

#include <fstream>
#include <sstream>
#include <stdexcept>

#include <fmt/core.h>
using fmt::format;

void LE3Scene::addShaderFromFile(std::string name, std::string vertexShaderPath, std::string fragmentShaderPath) {
    std::string vertexShaderSource = readFile(vertexShaderPath);
    std::string fragmentShaderSource = readFile(fragmentShaderPath);
    addShaderFromSource(name, vertexShaderSource, fragmentShaderSource);
}
void LE3Scene::addShaderFromSource(std::string name, std::string vertexShaderSource, std::string fragmentShaderSource) {
    if (m_pShaders.contains(name)) throw std::runtime_error(format("Shader [{}] already exist", name));
    m_pShaders[name] = std::make_shared<LE3Shader>(vertexShaderSource, fragmentShaderSource);
}

std::string LE3Scene::readFile(std::string filename) {
    std::ifstream ifs(filename);
    if (!ifs.good()) throw std::runtime_error(format("Could not open file:\n\t{}\n", filename));
    std::stringstream ss;
    ss << ifs.rdbuf();
    return ss.str();
}