#include "commands/le3ed_com_delete_mesh.h"
#include "le3_engine_systems.h"
using namespace le3;

LE3EditorComDeleteMesh::LE3EditorComDeleteMesh(std::string name, std::string path, bool isSkeletal) :
    m_name(name), m_path(path), m_bIsSkeletal(isSkeletal)
{
    for (auto& [name, scene] : LE3GetSceneManager().getScenes()) {
        for (auto& [objectName, object] : scene->getObjects()) {
            if (LE3StaticModelPtr model = std::dynamic_pointer_cast<LE3StaticModel>(object)) {
                if (!model->getMesh().expired() && model->getMesh().lock()->getName() == m_name)
                    m_depObjects.push_back(std::make_pair(name, objectName));
            }
            if (LE3SkeletalModelPtr model = std::dynamic_pointer_cast<LE3SkeletalModel>(object)) {
                if (!model->getMesh().expired() && model->getMesh().lock()->getName() == m_name)
                    m_depObjects.push_back(std::make_pair(name, objectName));
            }
        }
    }
    if (m_bIsSkeletal)
        m_animationTracks = LE3GetAssetManager().getSkeletalMesh(m_name).lock()->getAnimationTracks();
}

void LE3EditorComDeleteMesh::execute() {
    if (m_bIsSkeletal) LE3GetAssetManager().deleteSkeletalMesh(m_name);
    else LE3GetAssetManager().deleteStaticMesh(m_name);
}
void LE3EditorComDeleteMesh::undo() {
    if (m_bIsSkeletal) {
        LE3GetAssetManager().addSkeletalMesh(m_name, m_path);
        LE3GetAssetManager().getSkeletalMesh(m_name).lock()->setAnimationTracks(m_animationTracks);
    }
    else {
        LE3GetAssetManager().addStaticMesh(m_name, m_path);
    }

    for (auto& [sceneName, objectName] : m_depObjects) {
        LE3ObjectPtr pObject = LE3GetSceneManager().getScene(sceneName)->getObject(objectName);

        if (m_bIsSkeletal) {
            LE3SkeletalModelPtr model = std::dynamic_pointer_cast<LE3SkeletalModel>(pObject);
            model->setMesh(LE3GetAssetManager().getSkeletalMesh(m_name));
        } else {
            LE3StaticModelPtr model = std::dynamic_pointer_cast<LE3StaticModel>(pObject);
            model->setMesh(LE3GetAssetManager().getStaticMesh(m_name));
        }
    }
    LE3GetAssetManager().refreshPointers();
}