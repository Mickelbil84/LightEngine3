#include "widgets/popups/le3ed_pop_save_scene.h"
#include "core/le3_engine_systems.h"
#include "le3ed_project.h"
#include "le3ed_editor_systems.h"
using namespace le3;

void LE3EdPopSaveScene::init() {
    for (int i = 0; i < 1024; i++)
        m_sceneName[i] = '\0';
}

void LE3EdPopSaveScene::update() {
    ImVec2 center = ImGui::GetMainViewport()->GetCenter();
    ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
    if (ImGui::BeginPopupModal(LE3ED_POP_SAVE_SCENE.c_str(), NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
        this->lockEngine();

        ImGui::Text("Scene Name (*.lua):");
        ImGui::InputText("##sceneName", m_sceneName, 1024);

        if (ImGui::Button("Cancel")) {
            ImGui::CloseCurrentPopup();
            this->unlockEngine();
        }
        ImGui::SameLine();
        if (ImGui::Button("Save")) {
            LE3EditorSystems::instance().getScenesComponent()->saveScene(LE3ED_PROJECT_SCENES_ROOT + std::string(m_sceneName));
            ImGui::CloseCurrentPopup();
            this->unlockEngine();
        }
        ImGui::EndPopup();
    }
}