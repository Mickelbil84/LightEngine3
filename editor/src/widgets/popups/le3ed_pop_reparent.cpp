#include "widgets/popups/le3ed_pop_reparent.h"
#include "commands/le3ed_com_reparent.h"
#include "le3_engine_systems.h"
using namespace le3;

#include <imgui.h>

void LE3EditorPopReparent::init() {
    setNameString(m_objName);
}

void LE3EditorPopReparent::update() {
    ImVec2 center = ImGui::GetMainViewport()->GetCenter();
    ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
    if (ImGui::BeginPopupModal(LE3ED_POP_REPARENT.c_str(), NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
        this->lockEngine();
        ImGui::Text("  Object:");
        ImGui::Text("  \t%s", m_objName.c_str());

        setNameString(m_newParentName);
        if (m_newParentName == m_objName || m_newParentName == "") {
            ImGui::Text("  Select a new parent..");

            if (ImGui::Button("Cancel")) {
                ImGui::CloseCurrentPopup();
                this->unlockEngine();
            }
        }
        else {
            ImGui::Text("  New Parent:");
            ImGui::Text("  \t%s", m_newParentName.c_str());

            if (ImGui::Button("Cancel")) {
                ImGui::CloseCurrentPopup();
                this->unlockEngine();
            }
            ImGui::SameLine();
            if (ImGui::Button("Add")) {
                LE3GetEditorManager().getCommandStack().execute(std::make_unique<LE3EditorComReparent>(m_objName, m_newParentName));
                ImGui::CloseCurrentPopup();
                this->unlockEngine();
            }
        }
        ImGui::EndPopup();
    }
}

void LE3EditorPopReparent::setNameString(std::string& str) {
    str = "";
    LE3ObjectPtr pObject = LE3GetEditorManager().getSelection().pObject.lock();
    if (pObject) str = pObject->getName();
}