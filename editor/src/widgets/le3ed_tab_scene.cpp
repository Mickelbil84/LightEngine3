#include "widgets/le3ed_tab_scene.h"
using namespace le3;

void LE3EditorTabScene::init() {
    flags = 
        ImGuiTableFlags_BordersV | 
        ImGuiTableFlags_BordersOuterH | 
        ImGuiTableFlags_Resizable | 
        ImGuiTableFlags_RowBg | 
        ImGuiTableFlags_NoBordersInBody |
        ImGuiTableFlags_ScrollX;
}
void LE3EditorTabScene::update() {
    ImGui::Checkbox("Show hidden engine objects", &m_bShowEngineObjects);

    if (ImGui::Button("Expand All")) {
        for (auto& [path, open] : m_openStatus) {
            m_openStatus[path] = true;
        }
    }
    ImGui::SameLine();
    if (ImGui::Button("Collapse All")) {
        for (auto& [path, open] : m_openStatus) {
            m_openStatus[path] = false;
        }
    }

    if (ImGui::BeginTable("##SceneTreeView", 2, flags)) {
        ImGui::TableSetupColumn("Name", ImGuiTableColumnFlags_NoHide);    
        ImGui::TableSetupColumn("Type", ImGuiTableColumnFlags_NoHide);
        ImGui::TableHeadersRow();

        ImGui::BeginMultiSelect(ImGuiMultiSelectFlags_SingleSelect);
        recurseSceneTree(LE3GetSceneManager().getScene("scene")->getSceneRoot());
        ImGui::EndMultiSelect();

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

    ImGuiTreeNodeFlags extraFlags = 0;
    bool shouldOpen = true;
    if (m_openStatus.contains(obj->getName())) {
        shouldOpen = m_openStatus[obj->getName()];
    }
    LE3ObjectPtr ptr = nullptr;
    for (auto tmp : LE3GetEditorManager().getSelection().pObjects) {
        if (tmp.lock() == obj) {
            ptr = tmp.lock();
            break;
        }
    }
    if (obj == ptr) extraFlags |= ImGuiTreeNodeFlags_Selected;
    while (ptr) {
        if (obj == ptr) {
            shouldOpen = true;
            break;
        }
        ptr = ptr->getParent();
    }

    // Special case: If we only have delegated for selection, no need for expansion (unless we want to show engine objects)
    bool hasOnlyDelegates = obj->getChildren().size() > 0;
    for (LE3ObjectPtr child : obj->getChildren()) {
        if (!child->isDelegate()) {
            hasOnlyDelegates = false;
            break;
        }
    }

    if ((obj->getChildren().size() > 0) && (!hasOnlyDelegates || m_bShowEngineObjects)) {
        ImGui::SetNextItemOpen(shouldOpen);
        bool open = ImGui::TreeNodeEx(obj->getName().c_str(), ImGuiTreeNodeFlags_SpanAllColumns | extraFlags);
        m_openStatus[obj->getName()] = open;
        if (ImGui::IsItemClicked(ImGuiMouseButton_Right)) {
            LE3GetEditorManager().getSelection().selectObject(obj);
            // LE3GetSceneManager().updateScenes(0);
        }
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
            ImGuiTreeNodeFlags_Bullet | ImGuiTreeNodeFlags_NoTreePushOnOpen | extraFlags);
        if (ImGui::IsItemClicked()) {
            LE3GetEditorManager().getSelection().selectObject(obj);
            // LE3GetSceneManager().updateScenes(0);
        }
        ImGui::TableNextColumn();
        ImGui::TextDisabled("%s", obj->getObjectType().c_str());
    }

}