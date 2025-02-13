#include "le3ed_project_browser.h"
using namespace le3;

#include <fmt/core.h>

void LE3EditorProjectBrowser::init() {
    m_engineState.requestResize(500, 300);
}

void LE3EditorProjectBrowser::render() {
    ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowSize(ImVec2(500, 300));
    ImGui::SetNextWindowPos(ImVec2(0,0));
    ImGui::Begin("Project Browser", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse);
    ImGui::Text("Hello, world!");
    ImGui::End();
}