#pragma once

#include "le3ed_project.h"
#include "le3ed_component.h"
#include "widgets/popups/le3ed_pop_load_scene.h"
#include "widgets/popups/le3ed_pop_save_scene.h"

namespace le3 {

    const std::string LE3ED_SHARED_SCENE_NAME = "__shared__";
    const std::string LE3ED_SHARED_SCENE_PATH = LE3ED_PROJECT_SCENES_ROOT + fmt::format("{}.lua", LE3ED_SHARED_SCENE_NAME);    

    class LE3EditorScenes : public LE3EditorComponent {
    public:
        LE3ED_COMPONENT_DEAFULT_CTOR(LE3EditorScenes)
        void init();
        void update(float deltaTime);
        void handleInput(LE3Input input);
        void render();
        
        void saveScene(std::string name);
        void loadScene(std::string name);

        void openLoadScenePopup();
        void openSaveScenePopup();

        LE3EditorPopup* getLoadScenePopup() { return &m_loadScenePop; }
        LE3EditorPopup* getSaveScenePopup() { return &m_saveScenePop; }
    
    private:
        void initCameras();
        void initScenes(std::string name);
        void initGizmo();

        void initSharedScene();

        glm::vec3 cameraVelocity, cameraRotation;
        float walkSpeed = 2.2f, sensitivity = 0.005f;

        LE3EdPopLoadScene m_loadScenePop;
        LE3EdPopSaveScene m_saveScenePop;
    };

}