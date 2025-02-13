#include "le3ed_project_browser.h"
#include "le3ed_cache.h"
using namespace le3;

#include <fmt/core.h>

void LE3EditorProjectBrowser::init() {
    LE3GetDatFileSystem().addArchive("editor", "editor.dat");
    LE3EditorCache::load();

    m_engineState.requestResize(500, 300);

    m_fileBrowser = ImGui::FileBrowser(
        ImGuiFileBrowserFlags_SelectDirectory | ImGuiFileBrowserFlags_NoModal | 
        ImGuiFileBrowserFlags_CreateNewDir | ImGuiFileBrowserFlags_HideRegularFiles | ImGuiFileBrowserFlags_EditPathString);
    m_fileBrowser.SetTitle("Open Project");
}

void LE3EditorProjectBrowser::render() {
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDocking;
    const ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->Pos);
    ImGui::SetNextWindowSize(viewport->Size);
    ImGui::SetNextWindowViewport(viewport->ID);
    window_flags |= ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
    window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

    ImGui::Begin("Project Browser", nullptr, window_flags);
    if (ImGui::Button("Open Project")) {
        m_fileBrowser.Open();
    }
    ImGui::End();

    m_fileBrowser.Display();
    if (m_fileBrowser.HasSelected()) {
        std::string selection = m_fileBrowser.GetSelected().string();
        fmt::print("Selected: {}\n", selection);
        m_fileBrowser.ClearSelected();

        LE3EngineSystems::instance().requestReset();
    }
}