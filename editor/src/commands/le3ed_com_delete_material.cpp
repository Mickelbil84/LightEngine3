#include "commands/le3ed_com_delete_material.h"
#include "core/le3_engine_systems.h"
using namespace le3;

LE3EditorComDeleteMaterial::LE3EditorComDeleteMaterial(std::string name, std::string shaderName) :
    m_name(name), m_shaderName(shaderName), m_material(LE3ShaderPtr())
{
    for (auto& [name, scene] : LE3GetSceneManager().getScenes()) {
        for (auto& [objectName, object] : scene->getObjects()) {
            if (LE3DrawableObjectPtr drawable = std::dynamic_pointer_cast<LE3DrawableObject>(object)) {
                if (drawable->getMaterial().lock() && drawable->getMaterial().lock()->name == m_name)
                    m_depObjects.push_back(std::make_pair(name, objectName));
            }
        }
    }
    m_material = *(LE3GetAssetManager().getMaterial(m_name).lock());
}

void LE3EditorComDeleteMaterial::execute() {
    LE3GetAssetManager().deleteMaterial(m_name);
}
void LE3EditorComDeleteMaterial::undo() {
    LE3GetAssetManager().addMaterial(m_name, m_shaderName);
    *(LE3GetAssetManager().getMaterial(m_name).lock()) = m_material;
    for (auto& [sceneName, objectName] : m_depObjects) {
        LE3ObjectPtr pObject = LE3GetSceneManager().getScene(sceneName)->getObject(objectName);
        LE3DrawableObjectPtr drawable = std::dynamic_pointer_cast<LE3DrawableObject>(pObject);
        drawable->setMaterial(LE3GetAssetManager().getMaterial(m_name));
    }
    LE3GetAssetManager().refreshPointers();
}