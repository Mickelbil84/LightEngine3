#pragma once

#include "le3ed_component.h"
#include "widgets/popups/le3ed_pop_load_scene.h"

namespace le3 {

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
    
    private:
        void initCameras();
        void initScenes(std::string name);
        void initGizmo();

        glm::vec3 cameraVelocity, cameraRotation;
        float walkSpeed = 2.2f, sensitivity = 0.005f;

        LE3EdPopLoadScene m_loadScenePop;
    };

}