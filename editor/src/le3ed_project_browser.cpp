#include "le3ed_project_browser.h"
using namespace le3;

#include <fmt/core.h>

void LE3EditorProjectBrowser::init() {
    m_engineState.requestResize(500, 300);
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
    ImGui::Text("Hello, world!");
    ImGui::End();
}