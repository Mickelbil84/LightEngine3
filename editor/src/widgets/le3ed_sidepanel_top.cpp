#include "widgets/le3ed_sidepanel_top.h"
using namespace le3;

#include <imgui_internal.h>

void LE3EditorSidepanelTop::init() {

}
void LE3EditorSidepanelTop::update() {
    if (ImGui::BeginTabBar("##SidepanelTopTabs", ImGuiTabBarFlags_None)) {
        if (ImGui::BeginTabItem("Scene")) {
            ImGui::Text("Scene");
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("Assets")) {
            ImGui::Text("Assets");
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("Content")) {
            ImGui::Text("Content");
            ImGui::EndTabItem();
        }
        ImGui::EndTabBar();
    }
}