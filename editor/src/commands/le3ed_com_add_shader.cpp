#include "commands/le3ed_com_add_shader.h"
using namespace le3;

LE3EditorComAddShader::LE3EditorComAddShader(std::string name, std::string vertexPath, std::string fragmentPath) :
    m_name(name), m_vertexPath(vertexPath), m_fragmentPath(fragmentPath)
{
}

void LE3EditorComAddShader::execute() {
    LE3GetAssetManager().addShaderFromFile(m_name, m_vertexPath, m_fragmentPath);
}
void LE3EditorComAddShader::undo() {
    LE3GetAssetManager().deleteShader(m_name);
}