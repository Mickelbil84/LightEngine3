#include "widgets/le3ed_tab_content.h"
using namespace le3;

void LE3EditorTabContent::init() {
    m_selectedArchive = 0;

    flags = 
        ImGuiTableFlags_BordersV | 
        ImGuiTableFlags_BordersOuterH | 
        ImGuiTableFlags_Resizable | 
        ImGuiTableFlags_RowBg | 
        ImGuiTableFlags_NoBordersInBody;
}
void LE3EditorTabContent::update() {
    updateArchiveList();
    updateTreeView();
}

void LE3EditorTabContent::updateArchiveList() {
    m_archives = LE3GetDatFileSystem().getAvailableArchives();
    std::vector<const char*> archiveLabels;
    for (auto& archive : m_archives) archiveLabels.push_back(archive.c_str());
    
    ImGui::Combo("Archive", &m_selectedArchive, archiveLabels.data(), archiveLabels.size());
}

void LE3EditorTabContent::updateTreeView() {
    if (ImGui::BeginTable("##ContentTreeView", 2, flags)) {
        ImGui::TableSetupColumn("Name", ImGuiTableColumnFlags_NoHide);
        ImGui::TableSetupColumn("Size", ImGuiTableColumnFlags_NoHide);
        ImGui::TableHeadersRow();

        recurseContentTree(LE3GetDatFileSystem().getFileNode(
            "/" + m_archives[m_selectedArchive]));

        ImGui::EndTable();
    }
}

void LE3EditorTabContent::recurseContentTree(LE3DatFileNode* node) {
    ImGui::TableNextRow();
    ImGui::TableNextColumn();

    ImGuiTreeNodeFlags extraFlags = 0;
    bool shouldOpen = false;
    if (m_openStatus.contains(node->path)) {
        shouldOpen = m_openStatus[node->path];
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
        ImGui::Text("%s", filename.c_str());
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