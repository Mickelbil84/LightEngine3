#include "commands/le3ed_com_add_material.h"
#include "core/le3_engine_systems.h"
using namespace le3;

LE3EditorComAddMaterial::LE3EditorComAddMaterial(std::string name, std::string shaderName) :
    m_name(name), m_shaderName(shaderName)
{
}

void LE3EditorComAddMaterial::execute() {
    LE3GetAssetManager().addMaterial(m_name, m_shaderName);
}
void LE3EditorComAddMaterial::undo() {
    LE3GetAssetManager().deleteMaterial(m_name);
}