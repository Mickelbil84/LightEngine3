#include "widgets/popups/le3ed_pop_load_scene.h"
#include "le3_engine_systems.h"
#include "le3ed_project.h"
#include "le3ed_editor_systems.h"
using namespace le3;

#include <algorithm>
// #include <imgui.h>

void LE3EdPopLoadScene::init() {
    for (auto& file : LE3GetDatFileSystem().getFilesFromDir(LE3ED_PROJECT_SCENES_ROOT.substr(0, LE3ED_PROJECT_SCENES_ROOT.size() - 1))) {
        m_availableScenes.push_back(file.substr(LE3ED_PROJECT_SCENES_ROOT.size()));
    }
    std::sort(m_availableScenes.begin(), m_availableScenes.end());
    m_selectionIdx = 0;
}

void LE3EdPopLoadScene::update() {
    ImVec2 center = ImGui::GetMainViewport()->GetCenter();
    ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
    if (ImGui::BeginPopupModal(LE3ED_POP_LOAD_SCENE.c_str(), NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
        this->lockEngine();
        ImGui::Text("Select Scene:");
        char tmp[1024] = {0};
        ImGui::InputText("##pathVS", tmp, 1024);

        if (ImGui::Button("Cancel")) {
            ImGui::CloseCurrentPopup();
            this->unlockEngine();
        }
        ImGui::SameLine();
        if (ImGui::Button("Open")) {
            LE3EditorSystems::instance().getScenesComponent()->loadScene(LE3ED_PROJECT_SCENES_ROOT + m_availableScenes[m_selectionIdx]);
            ImGui::CloseCurrentPopup();
            this->unlockEngine();
        }
        ImGui::EndPopup();
    }
}