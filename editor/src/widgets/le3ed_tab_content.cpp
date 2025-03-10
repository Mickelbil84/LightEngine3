#include "widgets/le3ed_tab_content.h"
using namespace le3;

void LE3EditorTabContent::init() {
    m_selectedArchive = -1;

    flags = 
        ImGuiTableFlags_BordersV | 
        ImGuiTableFlags_BordersOuterH | 
        ImGuiTableFlags_Resizable | 
        ImGuiTableFlags_RowBg | 
        ImGuiTableFlags_NoBordersInBody |
        ImGuiTableFlags_ScrollX;
}
void LE3EditorTabContent::update() {
    ImGui::Checkbox("Show engine content", &m_bShowEngineContent);
    ImGui::Checkbox("Show demo content", &m_bShowDemoContent);
    updateArchiveList();
    updateTreeView();
}

void LE3EditorTabContent::updateArchiveList() {
    m_archives = LE3GetDatFileSystem().getAvailableArchives();
    std::vector<const char*> archiveLabels;
    for (auto& archive : m_archives) {
        if ((archive == "engine" || archive == "editor" || archive == "le3proj" || archive == "le3edcache") && !m_bShowEngineContent) continue;
        if (archive == "demos" && !m_bShowDemoContent) continue;
        archiveLabels.push_back(archive.c_str());
    }
    
    ImGui::Combo("Archive", &m_selectedArchive, archiveLabels.data(), archiveLabels.size());
}

void LE3EditorTabContent::updateTreeView() {
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

    if (ImGui::BeginTable("##ContentTreeView", 2, flags)) {
        ImGui::TableSetupColumn("Name", ImGuiTableColumnFlags_NoHide);
        ImGui::TableSetupColumn("Size", ImGuiTableColumnFlags_NoHide);
        ImGui::TableHeadersRow();

        if (m_selectedArchive >= 0) {
            recurseContentTree(LE3GetDatFileSystem().getFileNode(
                "/" + m_archives[m_selectedArchive]));
        }

        ImGui::EndTable();
    }
}

void LE3EditorTabContent::recurseContentTree(LE3DatFileNode* node) {
    ImGui::TableNextRow();
    ImGui::TableNextColumn();

    ImGuiTreeNodeFlags extraFlags = 0;
    bool shouldOpen = true;
    if (m_openStatus.contains(node->path)) {
        shouldOpen = m_openStatus[node->path];
    }
    if (LE3GetEditorManager().getSelectedFile() == node->path) {
        extraFlags |= ImGuiTreeNodeFlags_Selected;
    }

    std::string filename = node->path;
    if (filename.ends_with("/")) filename = filename.substr(0, filename.size() - 1);
    filename = node->path.substr(node->path.find_last_of('/') + 1);

    if (node->children.size() > 0) {
        ImGui::SetNextItemOpen(shouldOpen);
        bool open = ImGui::TreeNodeEx(filename.c_str(), ImGuiTreeNodeFlags_SpanAllColumns | extraFlags);
        m_openStatus[node->path] = open;
        ImGui::TableNextColumn();
        ImGui::Text("--");
        if (open) {
            for (auto& child : node->children) {
                recurseContentTree(child);
            }
            ImGui::TreePop();
        }
    }
    else {
        ImGui::TreeNodeEx(filename.c_str(), 
            ImGuiTreeNodeFlags_SpanAllColumns | ImGuiTreeNodeFlags_Leaf | 
            ImGuiTreeNodeFlags_Bullet | ImGuiTreeNodeFlags_NoTreePushOnOpen | extraFlags);
        if (ImGui::IsItemClicked()) {
            LE3GetEditorManager().setSelectedFile(node->path);
        }
        ImGui::TableNextColumn();
        ImGui::Text("%s", LE3EditorTabContent::formatSize(
            LE3GetDatFileSystem().getFileInfo(node->path).packedSize).c_str());
    }
}

std::string LE3EditorTabContent::formatSize(uint64_t size) {
    const char* units[] = {"B", "KB", "MB", "GB", "TB"};
    int unitIdx = 0;
    while (size > 1024) {
        size /= 1024;
        unitIdx++;
    }
    if (unitIdx >= 5) unitIdx = 4;

    return fmt::format("{} {}", size, units[unitIdx]);
}