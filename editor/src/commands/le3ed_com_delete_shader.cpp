#include "commands/le3ed_com_delete_shader.h"
using namespace le3;

LE3EditorComDeleteShader::LE3EditorComDeleteShader(std::string name, std::string vertexPath, std::string fragmentPath) :
    m_name(name), m_vertexPath(vertexPath), m_fragmentPath(fragmentPath) {
    for (auto& [name, material] : LE3GetAssetManager().getMaterials()) {
        if (material->shader.lock() && material->shader.lock()->getName() == m_name) {
            m_dependingMaterials.push_back(name);
        }
    }
}

void LE3EditorComDeleteShader::execute() {
    LE3GetAssetManager().deleteShader(m_name);
}
void LE3EditorComDeleteShader::undo() {
    LE3GetAssetManager().addShaderFromFile(m_name, m_vertexPath, m_fragmentPath);
    for (std::string materialName : m_dependingMaterials) {
        LE3GetAssetManager().getMaterial(materialName).lock()->shader = LE3GetAssetManager().getShader(m_name);
    }
}