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
    ImGui::TableNextRow();
    ImGui::TableNextColumn();

    if (obj->getChildren().size() > 0) {
        bool open = ImGui::TreeNodeEx("node", ImGuiTreeNodeFlags_SpanAllColumns);
        ImGui::TableNextColumn();
        ImGui::TextDisabled("--");
        if (open) {
            for (LE3ObjectPtr child : obj->getChildren()) {
                recurseSceneTree(child);
            }
            ImGui::TreePop();
        }
    }
    else {
        ImGui::TreeNodeEx("node", 
            ImGuiTreeNodeFlags_SpanAllColumns | ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_Bullet | ImGuiTreeNodeFlags_NoTreePushOnOpen);
        ImGui::TableNextColumn();
        ImGui::TextDisabled("--");
    }

}