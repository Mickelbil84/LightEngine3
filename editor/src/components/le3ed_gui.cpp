#include "components/le3ed_gui.h"
using namespace le3;

#include <imgui_internal.h>

void LE3EditorGUI::init() {
    
}

void LE3EditorGUI::update(float deltaTime) {
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
    const ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->WorkPos);
    ImGui::SetNextWindowSize(viewport->WorkSize);
    ImGui::SetNextWindowViewport(viewport->ID);
    window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
    window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

    ImGui::Begin("EDITOR", nullptr, window_flags);
    ImGuiID dockspace_id = ImGui::GetID("Dockspace");
    ImGui::DockSpace(dockspace_id, ImVec2(0.f, 0.f), ImGuiDockNodeFlags_None);

    static auto rebuild_dockspace = true;
    if (rebuild_dockspace) {
        rebuild_dockspace = false;
        
        ImGui::DockBuilderRemoveNode(dockspace_id); 
        ImGui::DockBuilderAddNode(dockspace_id, ImGuiDockNodeFlags_DockSpace);
        ImGui::DockBuilderSetNodeSize(dockspace_id, viewport->Size);

        ImGuiID dock_toolbar, dock_toolbox, dock_mainView, dock_sidepanelTop, dock_sidepanelBottom;

        dock_toolbox = ImGui::DockBuilderSplitNode(dockspace_id, ImGuiDir_Down, 0.89f, nullptr, &dock_toolbar);
        dock_mainView = ImGui::DockBuilderSplitNode(dock_toolbox, ImGuiDir_Right, 0.9f, nullptr, &dock_toolbox);
        dock_sidepanelTop = ImGui::DockBuilderSplitNode(dock_mainView, ImGuiDir_Right, 0.3f, nullptr, &dock_mainView);
        dock_sidepanelBottom = ImGui::DockBuilderSplitNode(dock_sidepanelTop, ImGuiDir_Down, 0.5f, nullptr, &dock_sidepanelTop);

        ImGui::DockBuilderDockWindow("##Toolbar", dock_toolbar);
        ImGui::DockBuilderDockWindow("##Toolbox", dock_toolbox);
        ImGui::DockBuilderDockWindow("Viewport", dock_mainView);
        ImGui::DockBuilderDockWindow("SidepanelTop", dock_sidepanelTop);
        ImGui::DockBuilderDockWindow("SidepanelBottom", dock_sidepanelBottom);

        ImGui::DockBuilderGetNode(dock_toolbar)->LocalFlags |= ImGuiDockNodeFlags_NoTabBar | ImGuiDockNodeFlags_NoResize;
        ImGui::DockBuilderGetNode(dock_toolbox)->LocalFlags |= ImGuiDockNodeFlags_NoTabBar | ImGuiDockNodeFlags_NoResize;

        ImVec2 toolbarSize = ImGui::DockBuilderGetNode(dock_toolbar)->Size;
        int orgToolbarY = toolbarSize.y;
        toolbarSize.y = 16;
        ImGui::DockBuilderSetNodeSize(dock_toolbar, toolbarSize);

        ImVec2 toolboxSize = ImGui::DockBuilderGetNode(dock_toolbox)->Size;
        toolboxSize.x = 48;
        toolboxSize.y = toolboxSize.y + orgToolbarY - toolbarSize.y;
        ImGui::DockBuilderSetNodeSize(dock_toolbox, toolboxSize);

        ImVec2 viewportSize = ImGui::DockBuilderGetNode(dock_mainView)->Size;
        viewportSize.y = viewportSize.y + orgToolbarY - toolbarSize.y;
        ImGui::DockBuilderSetNodeSize(dock_mainView, viewportSize);

        ImVec2 sidepanelTopSize = ImGui::DockBuilderGetNode(dock_sidepanelTop)->Size;
        sidepanelTopSize.y = sidepanelTopSize.y + orgToolbarY - toolbarSize.y;
        ImGui::DockBuilderSetNodeSize(dock_sidepanelTop, sidepanelTopSize);

        ImVec2 sidepanelBottomSize = ImGui::DockBuilderGetNode(dock_sidepanelBottom)->Size;
        sidepanelBottomSize.y = sidepanelBottomSize.y + orgToolbarY - toolbarSize.y;
        ImGui::DockBuilderSetNodeSize(dock_sidepanelBottom, sidepanelBottomSize);

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

    ImGui::Begin("##Toolbar", nullptr, ImGuiWindowFlags_NoMove | 
            ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | 
            ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_AlwaysAutoResize);
        ImGui::SameLine(); ImGui::Button("New");
        ImGui::SameLine(); ImGui::Button("Open");
        ImGui::SameLine(); ImGui::Button("Save");
        ImGui::SameLine(); ImGui::Button("Save As");
        ImGui::SameLine(); ImGui::SeparatorEx(ImGuiSeparatorFlags_Vertical);
        ImGui::SameLine(); ImGui::Button("Undo");
        ImGui::SameLine(); ImGui::Button("Redo");
        ImGui::SameLine(); ImGui::SeparatorEx(ImGuiSeparatorFlags_Vertical);
        ImGui::SameLine(); ImGui::Button("Select");
        ImGui::SameLine(); ImGui::Button("Move");
        ImGui::SameLine(); ImGui::Button("Rotate");
        ImGui::SameLine(); ImGui::Button("Scale");
        ImGui::SameLine(); ImGui::SeparatorEx(ImGuiSeparatorFlags_Vertical);
    ImGui::End();

    ImGui::Begin("##Toolbox", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);
    ImGui::Button("LOL");
    ImGui::End();

    LE3GetImGuiUtils().addSceneViewport("Viewport", *LE3GetSceneManager().getScene("scene"), m_engineState);

    ImGui::Begin("SidepanelTop", nullptr, ImGuiWindowFlags_NoMove);
    ImGui::Button("SidepanelTop");
    ImGui::End();

    ImGui::Begin("SidepanelBottom", nullptr, ImGuiWindowFlags_NoMove);
    ImGui::Button("SidepanelBottom");
    ImGui::End();

}