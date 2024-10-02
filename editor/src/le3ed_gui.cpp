#include "le3ed_gui.h"
using namespace le3;

#include <imgui_internal.h>

void LE3EditorGUI::init() {
}

void LE3EditorGUI::update() {
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
        

        ImGui::DockBuilderDockWindow("LightEngine3 Editor", dockspace_id);
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

    LE3GetImGuiUtils().addSceneViewport("Viewport", *LE3GetSceneManager().getScene("scene"), m_engineState);
    LE3GetImGuiUtils().addSceneViewport("Viewport2", *LE3GetSceneManager().getScene("inspector0"), m_engineState);

    ImGui::Begin("LightEngine3 Editor", nullptr, ImGuiWindowFlags_NoMove);
    ImGui::Button("LOL");
    ImGui::End();

}