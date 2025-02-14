#include "components/le3ed_gui.h"
using namespace le3;

#include <imgui_internal.h>

void LE3EditorGUI::init() {
    // Load all editor icons
    for (auto filename : LE3GetDatFileSystem().getFilesFromDir("/editor/icons")) {
        if (!filename.ends_with(".png")) continue;
        std::string iconName = filename.substr(filename.find_last_of("/") + 1);
        iconName = iconName.substr(0, iconName.find_last_of("."));
        LE3GetAssetManager().addTexture(iconName, filename);
    }
    m_toolbar.init();
    m_toolbox.init();
    m_sidepanelTop.init();
    m_settingsPanel.init();
    m_propertiesPanel.init();
}

void LE3EditorGUI::update(float deltaTime) {
    setupLayout();

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
            ImGui::Separator();
            if (ImGui::MenuItem("Close Project")) {
                LE3EngineSystems::instance().requestReset();
            }
            if (ImGui::MenuItem("Exit")) {
                m_engineState.notifyWantsQuit();
            }
        ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }
    ImGui::End();

    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.f, 0.f));
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0.f, 0.f));
    ImGui::PushStyleVar(ImGuiStyleVar_WindowMinSize, ImVec2(0.f, 0.f));
    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.f, 0.f, 0.f, 0.f));

    ImGui::Begin("##Toolbar", nullptr, ImGuiWindowFlags_NoMove | 
            ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | 
            ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_AlwaysAutoResize);
        m_toolbar.update();
    ImGui::End();
    ImGui::PopStyleColor(1);
    ImGui::PopStyleVar(3);

    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(6.f, 4.f));
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0.f, 2.f));
    ImGui::PushStyleVar(ImGuiStyleVar_WindowMinSize, ImVec2(0.f, 0.f));
    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.f, 0.f, 0.f, 0.f));
    ImGui::Begin("##Toolbox", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);
        m_toolbox.update();
    ImGui::End();
    ImGui::PopStyleColor(1);
    ImGui::PopStyleVar(3);

    LE3GetImGuiUtils().addSceneViewport("Viewport", *LE3GetSceneManager().getScene("scene"), m_engineState);

    ImGui::Begin("Text Editor", nullptr, ImGuiWindowFlags_NoMove);
        // m_textEditor.update();
        std::string selectedFile = LE3GetEditorManager().getSelectedFile();
        if (selectedFile.ends_with(".lua") || selectedFile.ends_with(".txt") || selectedFile.ends_with(".vs") || selectedFile.ends_with(".fs")) {
            std::string content = LE3GetDatFileSystem().getFileContent(selectedFile).toString();
            ImGui::TextWrapped(content.c_str());
        }
    ImGui::End();

    ImGui::Begin("SidepanelTop", nullptr, ImGuiWindowFlags_NoMove);
        m_sidepanelTop.update();
    ImGui::End();

    ImGui::Begin("Properties", nullptr, ImGuiWindowFlags_NoMove);
        m_propertiesPanel.update();
    ImGui::End();

    ImGui::Begin("Settings", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoFocusOnAppearing);
        m_settingsPanel.update();
    ImGui::End();

}

void LE3EditorGUI::setupLayout() {
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
    const ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->Pos);
    ImGui::SetNextWindowSize(viewport->Size);
    ImGui::SetNextWindowViewport(viewport->ID);
    window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
    window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;


    ImGui::Begin("EDITOR", nullptr, window_flags);
    ImGuiID dockspace_id = ImGui::GetID("Dockspace");
    ImGui::DockSpace(dockspace_id, ImVec2(0.f, 0.f), ImGuiDockNodeFlags_PassthruCentralNode);

    static auto rebuild_dockspace = true;
    if (rebuild_dockspace) {
        rebuild_dockspace = false;
        
        ImGui::DockBuilderRemoveNode(dockspace_id); 
        ImGui::DockBuilderAddNode(dockspace_id, ImGuiDockNodeFlags_DockSpace);
        ImGui::DockBuilderSetNodeSize(dockspace_id, viewport->Size);

        ImGuiID dock_toolbar, dock_toolbox, dock_mainView, dock_sidepanelTop, dock_properties;

        dock_toolbox = ImGui::DockBuilderSplitNode(dockspace_id, ImGuiDir_Down, 0.95f, nullptr, &dock_toolbar);
        dock_mainView = ImGui::DockBuilderSplitNode(dock_toolbox, ImGuiDir_Right, 0.9f, nullptr, &dock_toolbox);
        dock_sidepanelTop = ImGui::DockBuilderSplitNode(dock_mainView, ImGuiDir_Right, 0.2f, nullptr, &dock_mainView);
        dock_properties = ImGui::DockBuilderSplitNode(dock_sidepanelTop, ImGuiDir_Down, 0.5f, nullptr, &dock_sidepanelTop);

        ImGui::DockBuilderDockWindow("##Toolbar", dock_toolbar);
        ImGui::DockBuilderDockWindow("##Toolbox", dock_toolbox);
        ImGui::DockBuilderDockWindow("Viewport", dock_mainView);
        ImGui::DockBuilderDockWindow("Text Editor", dock_mainView);
        ImGui::DockBuilderDockWindow("SidepanelTop", dock_sidepanelTop);
        ImGui::DockBuilderDockWindow("Properties", dock_properties);
        ImGui::DockBuilderDockWindow("Settings", dock_properties);

        ImGui::DockBuilderGetNode(dock_toolbar)->LocalFlags |= ImGuiDockNodeFlags_NoTabBar | ImGuiDockNodeFlags_NoResize;
        ImGui::DockBuilderGetNode(dock_toolbox)->LocalFlags |= ImGuiDockNodeFlags_NoTabBar | ImGuiDockNodeFlags_NoResize;
        ImGui::DockBuilderGetNode(dock_sidepanelTop)->LocalFlags |= ImGuiDockNodeFlags_NoTabBar;

        ImVec2 toolbarSize = ImGui::DockBuilderGetNode(dock_toolbar)->Size;
        int orgToolbarY = toolbarSize.y;
        toolbarSize.y = LE3ED_TOOLBAR_HEIGHT;
        ImGui::DockBuilderSetNodeSize(dock_toolbar, toolbarSize);

        ImVec2 toolboxSize = ImGui::DockBuilderGetNode(dock_toolbox)->Size;
        toolboxSize.x = LE3ED_TOOLBAR_HEIGHT;
        toolboxSize.y = toolboxSize.y + orgToolbarY - toolbarSize.y;
        ImGui::DockBuilderSetNodeSize(dock_toolbox, toolboxSize);

        ImGui::DockBuilderFinish(dockspace_id);
    }
}