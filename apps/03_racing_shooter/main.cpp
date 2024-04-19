#include <le3.h>
using namespace le3;

#define _USE_MATH_DEFINES
#include <math.h>
#include <random>

#include <fmt/core.h>

#include <glm/gtx/string_cast.hpp>

#include <imgui_internal.h>

class Demo03_RacingShooter : public LE3GameLogic {
public:
    LE3Scene m_scene, m_inspector;
    glm::vec3 cameraVelocity, cameraRotation;
    

    // Gui panel info
    float orbitOffset = 3.f;
    float carSpeed = .0f;
    float sun_RPY[3] = {0.f, 0.f, 0.f};
    bool bspShown = false;


    float walkSpeed = 2.2f, sensitivity = 0.005f;

    void init() {
        LE3GetDatFileSystem().addArchive("demos", "demos.dat");

        // Load all demo scripts
        for (auto script : LE3GetDatFileSystem().getFilesFromDir("/demos/scripts/racing_shooter")) {
            LE3GetScriptSystem().doFile(script);
        }

        m_scene.init(m_engineState.getWindowWidth(), m_engineState.getWindowHeight());
        m_scene.load("/demos/scripts/racing_shooter/scene.lua");
        m_scene.setRenderDirectly(false);
        m_scene.resize(1024, 1024);
        m_scene.drawDebug = [this]() { this->renderDebug(); };

        m_inspector.init_inspector(100, 100, m_scene);
        m_inspector.setMainCamera("inspector");
        m_inspector.setRenderDirectly(false);
        m_inspector.getMainCamera()->setPitchYaw(-0.35, -0.87);
        
        // m_scene.getMainCamera()->setAspectRatio(m_engineState.getAspectRatio());
        m_scene.getMainCamera()->setAspectRatio(1.f);

        // Setup initial animation demo
        LE3SkeletalModelPtr soldier = std::dynamic_pointer_cast<LE3SkeletalModel>(m_scene.getObject("soldier"));
        soldier->setCurrentAnimation("ANIM_idle");

        ///////////////
        // BSP DEMO
        ///////////////
        m_scene.addBSPBrush("bsp_c1");
        m_scene.getObject("bsp_c1")->getTransform().setPosition(glm::vec3(1.28, 0.64, 0.04));
        m_scene.getObject("bsp_c1")->getTransform().setScale(glm::vec3(2.56, 1.28, 0.08));
        m_scene.getObject("bsp_c1")->update(0.f);
        m_scene.addBSPBrush("bsp_c2", LE3_BRUSH_SUBTRACTIVE);
        m_scene.getObject("bsp_c2")->getTransform().setPosition(glm::vec3(0.72 + 0.32 + 0.32 + 1.04 / 2, 0.96 / 2 + 0.16, 0.04));
        m_scene.getObject("bsp_c2")->getTransform().setScale(glm::vec3(1.04, 0.8, 0.08));
        m_scene.getObject("bsp_c2")->update(0.f);
        m_scene.addBSPBrush("bsp_c3", LE3_BRUSH_SUBTRACTIVE);
        m_scene.getObject("bsp_c3")->getTransform().setPosition(glm::vec3(0.72, 0.96 / 2, 0.04));
        m_scene.getObject("bsp_c3")->getTransform().setScale(glm::vec3(0.64, 0.96, 0.08));
        m_scene.getObject("bsp_c3")->update(0.f);

        m_scene.getBSPManager().setShowBrushes(false);
    }
    void update(float deltaTime) {
        updateGUI();

        // Setup FPS camera
        LE3Scene* scene = &m_scene;
        if (m_engineState.getFocusOverrider() == "Viewport2") scene = &m_inspector;
        scene->getMainCamera()->addPitchYaw(sensitivity * cameraRotation.y, -sensitivity * cameraRotation.x);
        scene->getMainCamera()->moveForward(deltaTime * walkSpeed * cameraVelocity.y);
        scene->getMainCamera()->moveRight(deltaTime * walkSpeed * cameraVelocity.x);
        scene->getMainCamera()->moveUp(deltaTime * walkSpeed * cameraVelocity.z);

        std::dynamic_pointer_cast<LE3OrbitCamera>(m_scene.getObject("cameraOrbit"))->setOffset(orbitOffset);

        // Setup sunlight
        scene->getObject("sunLight")->getTransform().setRotationRPY(sun_RPY[0], sun_RPY[1], sun_RPY[2]);

        // Move car forward
        // glm::vec3 carPos = m_scene.getObject("car")->getTransform().getPosition();
        // carPos.x += -1.f * deltaTime * carSpeed;
        // if (carPos.x < -3.f) carPos.x = 7.f;
        // m_scene.getObject("car")->getTransform().setPosition(carPos);
        
        // for (int i = 1; i <= 4; i++)
        //     m_scene.getObject(fmt::format("wheel{}", i))->getTransform().addRotationZ(1.9f * carSpeed * deltaTime);

        // Update scene
        m_scene.update(deltaTime);  
    }

    void updateGUI() {
        ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
        const ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->WorkPos);
        ImGui::SetNextWindowSize(viewport->WorkSize);
        ImGui::SetNextWindowViewport(viewport->ID);
        window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
        window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

        ImGui::Begin("DEMO", nullptr, window_flags);
        ImGuiID dockspace_id = ImGui::GetID("Dockspace");
        ImGui::DockSpace(dockspace_id, ImVec2(0.f, 0.f), ImGuiDockNodeFlags_None);

        static auto first_time = true;
        if (first_time) {
            first_time = false;
            
            ImGui::DockBuilderRemoveNode(dockspace_id); 
            ImGui::DockBuilderAddNode(dockspace_id, ImGuiDockNodeFlags_DockSpace);
            ImGui::DockBuilderSetNodeSize(dockspace_id, viewport->Size);
            auto dock_id_left = ImGui::DockBuilderSplitNode(dockspace_id, ImGuiDir_Left, 0.8f, nullptr, &dockspace_id);
            // auto dock_id_right = ImGui::DockBuilderSplitNode(dockspace_id, ImGuiDir_Down, 0.5f, nullptr, &dockspace_id);
            auto dock_id_down = ImGui::DockBuilderSplitNode(dockspace_id, ImGuiDir_Down, 0.5f, nullptr, &dockspace_id);
            

            ImGui::DockBuilderDockWindow("Demo 03: Racing Shooter", dockspace_id);
            ImGui::DockBuilderDockWindow("Viewport", dock_id_left);
            ImGui::DockBuilderDockWindow("Viewport2", dock_id_down);
            ImGui::DockBuilderFinish(dockspace_id);

        }

        if (ImGui::BeginMainMenuBar()) {
              if (ImGui::BeginMenu("File")) {
                   if (ImGui::MenuItem("Create")) { 
                   }
                   if (ImGui::MenuItem("Open", "Ctrl+O")) { 
                   }
                   if (ImGui::MenuItem("Save", "Ctrl+S")) {
                   }
                   if (ImGui::MenuItem("Save as..")) { 
                    }
             ImGui::EndMenu();
             }
             ImGui::EndMainMenuBar();
        }

        ImGui::End();

        LE3GetImGuiUtils().addSceneViewport("Viewport", m_scene, m_engineState);
        LE3GetImGuiUtils().addSceneViewport("Viewport2", m_inspector, m_engineState);
        // LE3DirectionalLightPtr sunlight = std::dynamic_pointer_cast<LE3DirectionalLight>(m_scene.getObject("sunLight"));
        // LE3GetImGuiUtils().addDepthFramebufferViewport("Viewport2", sunlight->getShadowMap());

        ImGui::Begin("Demo 03: Racing Shooter", nullptr, ImGuiWindowFlags_NoMove);
        if (ImGui::CollapsingHeader("Camera Control", ImGuiTreeNodeFlags_DefaultOpen)) {
            if (ImGui::Button("Set FPS (Free) Camera")) {
                m_scene.setMainCamera("cameraFree");
            }
            if (ImGui::Button("Set TPS (Orbit) Camera")) {
                m_scene.setMainCamera("cameraOrbit");
            }
            ImGui::Text("Orbit Offset:");
            ImGui::SliderFloat("##orbitOffset", &orbitOffset, 0.f, 5.f);
            ImGui::Separator();
            ImGui::Text("Press F to toggle relative mouse.");

        }
        if (ImGui::CollapsingHeader("Camera Control", ImGuiTreeNodeFlags_DefaultOpen)) {
            ImGui::Text("Car Speed:");
            ImGui::SliderFloat("##carSpeed", &carSpeed, 0.f, 3.f);
        }
        if (ImGui::CollapsingHeader("Sunlight Control", ImGuiTreeNodeFlags_DefaultOpen)) {
            ImGui::SliderFloat3("Sunlight Rotation", sun_RPY, -M_PI, M_PI);
        }
        if (ImGui::CollapsingHeader("Animation Control", ImGuiTreeNodeFlags_DefaultOpen)) {
            const char* items[] = { "ANIM_idle", "ANIM_walk", "ANIM_fire" };
            static int item_current_idx = 0; // Here we store our selection data as an index.
            int last_selected = item_current_idx;
            const char* combo_preview_value = items[item_current_idx];  // Pass in the preview value visible before opening the combo (it could be anything)
            if (ImGui::BeginCombo("Soldier Animation", combo_preview_value, 0))
            {
                for (int n = 0; n < IM_ARRAYSIZE(items); n++)
                {
                    const bool is_selected = (item_current_idx == n);
                    if (ImGui::Selectable(items[n], is_selected))
                        item_current_idx = n;

                    // Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
                    if (is_selected)
                        ImGui::SetItemDefaultFocus();
                }
                ImGui::EndCombo();
            }
            if (last_selected != item_current_idx) {
                LE3SkeletalModelPtr soldier = std::dynamic_pointer_cast<LE3SkeletalModel>(m_scene.getObject("soldier"));
                soldier->setCurrentAnimation(items[item_current_idx]);
            }
        }
        if (ImGui::CollapsingHeader("BSP Control", ImGuiTreeNodeFlags_DefaultOpen)) {
            if (ImGui::Button("Toggle Brushes")) {
                bspShown = !bspShown;
                m_scene.getBSPManager().setShowBrushes(bspShown);
            }
            if (ImGui::Button("Build")) {
                m_scene.buildBSP();
            }
        }


        ImGui::End();
    }

    void render() {
        m_scene.draw();
        m_inspector.draw();
    }

    void renderDebug() {
        LE3GetVisualDebug().drawDebugCone(glm::vec3(0.f), 1.f, 2.f, glm::vec3(1.f, 1.f, 0.f));
    }

    void handleInput(LE3Input input) {
        if (!m_engineState.getFocusedOverride()) return;
        if (input.keys["KEY_ESCAPE"]) m_engineState.notifyWantsQuit();

        if (input.isKeyDownEvent("KEY_F")) m_engineState.notifyWantsRelativeMOuse(!m_engineState.isRelativeMouse());

        ////////////////////////
        // Camera Movement
        ////////////////////////
        cameraVelocity = glm::vec3();
        cameraRotation = glm::vec3();
        if (input.bLeftMouseDown || m_engineState.isRelativeMouse()) {
            if (input.keys["KEY_W"]) cameraVelocity.y = 1.f;
            else if (input.keys["KEY_S"]) cameraVelocity.y = -1.f;
            else cameraVelocity.y = 0.f;

            if (input.keys["KEY_D"]) cameraVelocity.x = 1.f;
            else if (input.keys["KEY_A"]) cameraVelocity.x = -1.f;
            else cameraVelocity.x = 0.f;

            if (input.keys["KEY_E"]) cameraVelocity.z = 1.f;
            else if (input.keys["KEY_Q"]) cameraVelocity.z = -1.f;
            else cameraVelocity.z = 0.f;

            cameraRotation.x = (float)input.xrel;
            cameraRotation.y = -(float)input.yrel;
        }
    }
};

int main() {
    LE3Application app(std::make_unique<Demo03_RacingShooter>());
    app.run();
    return 0;
}