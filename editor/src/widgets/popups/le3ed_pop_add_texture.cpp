#include "widgets/popups/le3ed_pop_add_texture.h"
#include "commands/le3ed_com_add_texture.h"
#include "le3_engine_systems.h"
using namespace le3;

#include <imgui.h>

void LE3EdPopAddTexture::init() {
    for (int i = 0; i < 256; i++) m_textureName[i] = 0;
    for (int i = 0; i < 1024; i++) m_path[i] = 0;
    m_bInterpolate = true;
    strcpy(m_path, LE3GetEditorManager().getSelectedFile().c_str());

    if (!LE3GetEditorManager().getSelectedFile().empty()) {
        // Get file name, without extensions, as texture name
        // Also remove of course the directories leading to the file
        std::string fileName = LE3GetEditorManager().getSelectedFile();
        size_t lastSlash = fileName.find_last_of("/\\");
        if (lastSlash != std::string::npos) {
            fileName = fileName.substr(lastSlash + 1);
        }
        size_t lastDot = fileName.find_last_of(".");
        if (lastDot != std::string::npos) {
            fileName = fileName.substr(0, lastDot);
        }
        strcpy(m_textureName, fileName.c_str());
    }
}
void LE3EdPopAddTexture::update() {
    ImVec2 center = ImGui::GetMainViewport()->GetCenter();
    ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
    if (ImGui::BeginPopupModal(LE3ED_POP_ADD_TEXTURE.c_str(), NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
        this->lockEngine();
        ImGui::Text("Texture Name:");
        ImGui::InputText("##textureName", m_textureName, 256);

        ImGui::Text("Texture Path:");
        ImGui::InputText("##path", m_path, 1024);

        ImGui::Text("Interpolate?");
        ImGui::SameLine();
        ImGui::Checkbox("##interpolate", &m_bInterpolate);

        if (ImGui::Button("Cancel")) {
            ImGui::CloseCurrentPopup();
            this->unlockEngine();
        }
        ImGui::SameLine();
        if (ImGui::Button("Add")) {

            if (LE3GetAssetManager().hasTexture(m_textureName)) {
            }
            else {
                LE3GetEditorManager().getCommandStack().execute(std::make_unique<LE3EditorComAddTexture>(m_textureName, m_path, m_bInterpolate));
                ImGui::CloseCurrentPopup();
                this->unlockEngine();
            }
        }
        ImGui::EndPopup();
    }
}