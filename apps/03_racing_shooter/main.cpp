#include <le3.h>
using namespace le3;

#include <fmt/core.h>
using fmt::print, fmt::format;

#include <glm/gtx/string_cast.hpp>

#include <imgui_internal.h>

class Demo03_RacingShooter : public LE3GameLogic {
public:
    LE3Scene m_scene;
    glm::vec3 cameraVelocity, cameraRotation;

    // Gui panel info
    float orbitOffset = 3.f;
    float carSpeed = .0f;


    float walkSpeed = 2.2f, sensitivity = 0.005f;

    void init() {
        LE3GetDatFileSystem().addArchive("demos", "demos.dat");
        m_scene.init(m_engineState.getWindowWidth(), m_engineState.getWindowHeight());
        m_scene.load("/demos/scripts/racing_shooter/scene.lua");
        m_scene.setRenderDirectly(false);
        m_scene.resize(1024, 1024);
        
        // m_scene.getMainCamera()->setAspectRatio(m_engineState.getAspectRatio());
        m_scene.getMainCamera()->setAspectRatio(1.f);
    }
    void update(float deltaTime) {
        updateGUI();

        // Setup FPS camera
        m_scene.getMainCamera()->addPitchYaw(sensitivity * cameraRotation.y, -sensitivity * cameraRotation.x);
        m_scene.getMainCamera()->moveForward(deltaTime * walkSpeed * cameraVelocity.y);
        m_scene.getMainCamera()->moveRight(deltaTime * walkSpeed * cameraVelocity.x);
        m_scene.getMainCamera()->moveUp(deltaTime * walkSpeed * cameraVelocity.z);

        std::dynamic_pointer_cast<LE3OrbitCamera>(m_scene.getObject("cameraOrbit"))->setOffset(orbitOffset);

        // Move car forward
        glm::vec3 carPos = m_scene.getObject("car")->getTransform().getPosition();
        carPos.x += -1.f * deltaTime * carSpeed;
        if (carPos.x < -3.f) carPos.x = 7.f;
        m_scene.getObject("car")->getTransform().setPosition(carPos);
        
        for (int i = 1; i <= 4; i++)
            m_scene.getObject(format("wheel{}", i))->getTransform().addRotationZ(1.9f * carSpeed * deltaTime);

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
            // auto dock_id_right = ImGui::DockBuilderSplitNode(dockspace_id, ImGuiDir_Right, 0.5f, nullptr, &dockspace_id);
            // auto dock_id_down = ImGui::DockBuilderSplitNode(dock_id_right, ImGuiDir_Down, 0.5f, nullptr, &dock_id_right);
            

            ImGui::DockBuilderDockWindow("Demo 03: Racing Shooter", dockspace_id);
            ImGui::DockBuilderDockWindow("Viewport", dock_id_left);
            ImGui::DockBuilderFinish(dockspace_id);

        }
        ImGui::End();

        
        
        LE3GetImGuiUtils().addSceneViewport("Viewport", m_scene, m_engineState);
        // LE3GetImGuiUtils().addSceneViewport("Viewport2", m_scene, m_engineState);

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
        ImGui::End();
    }

    void render() {
        m_scene.draw();
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