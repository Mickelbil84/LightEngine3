#include "widgets/popups/le3ed_pop_load_scene.h"
#include "core/le3_engine_systems.h"
#include "le3ed_project.h"
#include "le3ed_editor_systems.h"
using namespace le3;

#include <algorithm>
// #include <imgui.h>

void LE3EdPopLoadScene::init() {
    if (m_availableScenesCStr) {
        for (int i = 0; i < m_availableScenes.size() + 1; i++) {
            delete[] m_availableScenesCStr[i];
        }
        delete[] m_availableScenesCStr;
    }
    m_availableScenes.clear();
    for (auto& file : LE3GetDatFileSystem().getFilesFromDir(LE3ED_PROJECT_SCENES_ROOT.substr(0, LE3ED_PROJECT_SCENES_ROOT.size() - 1))) {
        m_availableScenes.push_back(file.substr(LE3ED_PROJECT_SCENES_ROOT.size()));
    }
    std::sort(m_availableScenes.begin(), m_availableScenes.end());
    m_selectionIdx = 0;

    m_availableScenesCStr = new char*[m_availableScenes.size() + 1];
    std::string placeholder = "-------";
    m_availableScenesCStr[0] = new char[placeholder.size() + 1];
    strcpy(m_availableScenesCStr[0], placeholder.c_str());
    for (int i = 0; i < m_availableScenes.size(); i++) {
        m_availableScenesCStr[i+1] = new char[m_availableScenes[i].size() + 1];
        strcpy(m_availableScenesCStr[i+1], m_availableScenes[i].c_str());
    }
}

void LE3EdPopLoadScene::update() {
    ImVec2 center = ImGui::GetMainViewport()->GetCenter();
    ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
    if (ImGui::BeginPopupModal(LE3ED_POP_LOAD_SCENE.c_str(), NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
        this->lockEngine();
        ImGui::Text("Select Scene:");
        if (ImGui::BeginCombo("##select_scene", m_availableScenesCStr[m_selectionIdx], 0)) {
            for (int n = 0; n < m_availableScenes.size() + 1; n++) {
                const bool isSelected = (m_selectionIdx == n);
                ImGuiSelectableFlags flags = 0;
                if (n == 0) flags = ImGuiSelectableFlags_Disabled;
                if (ImGui::Selectable(m_availableScenesCStr[n], isSelected, flags)) {
                    m_selectionIdx = n;
                }
                if (isSelected) {
                    ImGui::SetItemDefaultFocus();
                }
            }
            ImGui::EndCombo();
        }


        if (ImGui::Button("Cancel")) {
            ImGui::CloseCurrentPopup();
            this->unlockEngine();
        }
        ImGui::SameLine();
        if (ImGui::Button("Open")) {
            if (m_selectionIdx > 0) {
                LE3EditorSystems::instance().getScenesComponent()->loadScene(LE3ED_PROJECT_SCENES_ROOT + m_availableScenes[m_selectionIdx - 1]);
                ImGui::CloseCurrentPopup();
                this->unlockEngine();
            }
        }
        ImGui::EndPopup();
    }
}