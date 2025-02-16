#include "widgets/popups/le3ed_pop_add_mesh.h"
#include "commands/le3ed_com_add_mesh.h"
#include "le3_engine_systems.h"
using namespace le3;

#include <imgui.h>

void LE3EdPopAddMesh::init() {
    for (int i = 0; i < 256; i++) m_meshName[i] = 0;
    for (int i = 0; i < 1024; i++) m_path[i] = 0;
    m_bIsSkeletal = false;
    strcpy(m_path, LE3GetEditorManager().getSelectedFile().c_str());
}
void LE3EdPopAddMesh::update() {
    ImVec2 center = ImGui::GetMainViewport()->GetCenter();
    ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
    if (ImGui::BeginPopupModal(LE3ED_POP_ADD_MESH.c_str(), NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
        this->lockEngine();
        ImGui::Text("Mesh Name:");
        ImGui::InputText("##meshName", m_meshName, 256);

        ImGui::Text("Path:");
        ImGui::InputText("##path", m_path, 1024);

        ImGui::Checkbox("Skeletal", &m_bIsSkeletal);

        if (ImGui::Button("Cancel")) {
            ImGui::CloseCurrentPopup();
            this->unlockEngine();
        }
        ImGui::SameLine();
        if (ImGui::Button("Add")) {

            if (LE3GetAssetManager().hasStaticMesh(m_meshName) || LE3GetAssetManager().hasSkeletalMesh(m_meshName)) {
            }
            else {
                LE3GetEditorManager().getCommandStack().execute(std::make_unique<LE3EditorComAddMesh>(m_meshName, m_path, m_bIsSkeletal));
                ImGui::CloseCurrentPopup();
                this->unlockEngine();
            }
        }
        ImGui::EndPopup();
    }
}