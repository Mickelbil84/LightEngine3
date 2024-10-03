#include "widgets/le3ed_tab_scene.h"
using namespace le3;

void LE3EditorTabScene::init() {
    flags = 
        ImGuiTableFlags_BordersV | 
        ImGuiTableFlags_BordersOuterH | 
        ImGuiTableFlags_Resizable | 
        ImGuiTableFlags_RowBg | 
        ImGuiTableFlags_NoBordersInBody;
}
void LE3EditorTabScene::update() {
    ImGui::Checkbox("Show hidden engine objects", &m_bShowEngineObjects);

    if (ImGui::BeginTable("##SceneTreeView", 2, flags)) {
        ImGui::TableSetupColumn("Name", ImGuiTableColumnFlags_NoHide);    
        ImGui::TableSetupColumn("Type", ImGuiTableColumnFlags_NoHide);
        ImGui::TableHeadersRow();

        recurseSceneTree(LE3GetSceneManager().getScene("scene")->getSceneRoot());

        ImGui::EndTable();
    }
    // ImGui::TreePop();
}

void LE3EditorTabScene::recurseSceneTree(LE3ObjectPtr obj) {
    if (!m_bShowEngineObjects && obj->getName().starts_with(DEFAULT_ENGINE_PREFIX)) {
        return;
    }
        
    ImGui::TableNextRow();
    ImGui::TableNextColumn();

    ImGuiTreeNodeFlags selected = 0;
    LE3ObjectPtr ptr = LE3GetEditorManager().getSelectedObject().lock();
    while (ptr) {
        if (obj == ptr) {
            selected = ImGuiTreeNodeFlags_Selected;
            break;
        }
        ptr = ptr->getParent();
    }

    if (obj->getChildren().size() > 0) {
        bool open = ImGui::TreeNodeEx(obj->getName().c_str(), ImGuiTreeNodeFlags_SpanAllColumns | selected);
        ImGui::TableNextColumn();
        ImGui::TextDisabled("%s", obj->getObjectType().c_str());
        if (open) {
            for (LE3ObjectPtr child : obj->getChildren()) {
                recurseSceneTree(child);
            }
            ImGui::TreePop();
        }
    }
    else {
        ImGui::TreeNodeEx(obj->getName().c_str(), 
            ImGuiTreeNodeFlags_SpanAllColumns | ImGuiTreeNodeFlags_Leaf | 
            ImGuiTreeNodeFlags_Bullet | ImGuiTreeNodeFlags_NoTreePushOnOpen | selected);
        ImGui::TableNextColumn();
        ImGui::TextDisabled("%s", obj->getObjectType().c_str());
    }

}