#include "commands/le3ed_com_add_texture.h"
#include "le3_engine_systems.h"
using namespace le3;

LE3EditorComAddTexture::LE3EditorComAddTexture(std::string name, std::string path, bool interpolate) :
    m_name(name), m_path(path), m_bInterpolate(interpolate)
{
}

void LE3EditorComAddTexture::execute() {
    LE3GetAssetManager().addTexture(m_name, m_path, m_bInterpolate);
}
void LE3EditorComAddTexture::undo() {
    LE3GetAssetManager().deleteTexture(m_name);
}