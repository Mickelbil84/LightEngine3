#include "widgets/popups/le3ed_pop_add_material.h"
#include "commands/le3ed_com_add_material.h"
#include "core/le3_engine_systems.h"
using namespace le3;

#include <imgui.h>

void LE3EdPopAddMaterial::init() {
    for (int i = 0; i < 256; i++) m_materialName[i] = 0;
    for (int i = 0; i < 256; i++) m_shaderName[i] = 0;
    strcpy(m_shaderName, DEFAULT_SHADER.c_str());
}
void LE3EdPopAddMaterial::update() {
    ImVec2 center = ImGui::GetMainViewport()->GetCenter();
    ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
    if (ImGui::BeginPopupModal(LE3ED_POP_ADD_MATERIAL.c_str(), NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
        this->lockEngine();
        ImGui::Text("Material Name:");
        ImGui::InputText("##materialName", m_materialName, 256);

        ImGui::Text("Shader Name:");
        ImGui::InputText("##shaderName", m_shaderName, 256);

        if (ImGui::Button("Cancel")) {
            ImGui::CloseCurrentPopup();
            this->unlockEngine();
        }
        ImGui::SameLine();
        if (ImGui::Button("Add")) {

            if (LE3GetAssetManager().hasMaterial(m_materialName)) {
            }
            else {
                LE3GetEditorManager().getCommandStack().execute(std::make_unique<LE3EditorComAddMaterial>(m_materialName, m_shaderName));
                ImGui::CloseCurrentPopup();
                this->unlockEngine();
            }
        }
        ImGui::EndPopup();
    }
}