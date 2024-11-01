#include "commands/le3ed_com_add_mesh.h"
#include "le3_engine_systems.h"
using namespace le3;

LE3EditorComAddMesh::LE3EditorComAddMesh(std::string name, std::string path, bool isSkeletal) :
    m_name(name), m_path(path), m_bIsSkeletal(isSkeletal)
{
}

void LE3EditorComAddMesh::execute() {
    if (m_bIsSkeletal)
        LE3GetAssetManager().addSkeletalMesh(m_name, m_path);
    else
        LE3GetAssetManager().addStaticMesh(m_name, m_path);
}
void LE3EditorComAddMesh::undo() {
    if (m_bIsSkeletal)
        LE3GetAssetManager().deleteSkeletalMesh(m_name);
    else
        LE3GetAssetManager().deleteStaticMesh(m_name);
}