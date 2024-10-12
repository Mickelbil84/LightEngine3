#include "widgets/popups/le3ed_pop_add_shader.h"
#include "commands/le3ed_com_add_shader.h"
#include "le3_engine_systems.h"
using namespace le3;

#include <imgui.h>

void LE3EdPopAddShader::init() {
    for (int i = 0; i < 256; i++) m_shaderName[i] = 0;
    for (int i = 0; i < 1024; i++) m_pathVS[i] = 0;
    for (int i = 0; i < 1024; i++) m_pathFS[i] = 0;
}
void LE3EdPopAddShader::update() {
    ImVec2 center = ImGui::GetMainViewport()->GetCenter();
    ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
    if (ImGui::BeginPopupModal(LE3ED_POP_ADD_SHADER.c_str(), NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
        this->lockEngine();
        ImGui::Text("Shader Name:");
        ImGui::InputText("##shaderName", m_shaderName, 256);

        ImGui::Text("Vertex Shader Path:");
        ImGui::InputText("##pathVS", m_pathVS, 1024);

        ImGui::Text("Fragment Shader Path:");
        ImGui::InputText("##pathFS", m_pathFS, 1024);

        if (ImGui::Button("Cancel")) {
            ImGui::CloseCurrentPopup();
            this->unlockEngine();
        }
        ImGui::SameLine();
        if (ImGui::Button("Add")) {

            if (LE3GetAssetManager().hasShader(m_shaderName)) {
                ImGui::OpenPopup("Shader Already Exists");

                if (ImGui::BeginPopupModal("Shader Already Exists")) {
                    ImGui::Text("A shader with the name '%s' already exists.", m_shaderName);
                    if (ImGui::Button("OK")) {
                        ImGui::CloseCurrentPopup();
                    }
                    ImGui::EndPopup();
                }
            }
            else {
                LE3GetEditorManager().getCommandStack().execute(std::make_unique<LE3EditorComAddShader>(m_shaderName, m_pathVS, m_pathFS));
                ImGui::CloseCurrentPopup();
                this->unlockEngine();
            }
        }
        ImGui::EndPopup();
    }
}