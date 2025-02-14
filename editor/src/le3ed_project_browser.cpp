#include "le3ed_project_browser.h"
#include "le3ed_cache.h"
using namespace le3;

#include <filesystem>

#include <fmt/core.h>
#include <NMB/NMB.h>


void LE3EditorProjectBrowser::init() {
    LE3GetDatFileSystem().addArchive("editor", "editor.dat");
    LE3EditorCache::load();
    LE3EditorCache::setMostRecentProject("");

    for (auto s : LE3EditorCache::getRecentProjects()) {
        fmt::print("Recent project: {}\n", s);
    }

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
        m_fileBrowser.ClearSelected();

        if (isValidProjectDir(selection)) {
            LE3EditorCache::setMostRecentProject(selection);
            LE3EngineSystems::instance().requestReset();
        } else {
            LE3EditorCache::setMostRecentProject("");
            std::string errmsg = fmt::format("Please select either an empty directory or a directory containing a project file ('{}').", LE3ED_PROJECT_FILENAME);
            NMB::show("Invalid project directory", errmsg.c_str(), NMB::Icon::ICON_ERROR);
        }
    }
}

bool LE3EditorProjectBrowser::isValidProjectDir(std::string dir) {
    if (std::filesystem::is_empty(dir)) {
        LE3GetDatFileSystem().addArchive(LE3ED_PROJECT_ARCHIVE, dir + "/" + LE3ED_PROJECT_FILENAME); // Creates a file, if directory is empty
        return true;
    }
    if (std::filesystem::exists(dir + "/" + LE3ED_PROJECT_FILENAME)) return true;
    return false;
}