#include "widgets/le3ed_tab_assets.h"
using namespace le3;

void LE3EditorTabAssets::init() {
    flags = 
        ImGuiTableFlags_BordersV | 
        ImGuiTableFlags_BordersOuterH | 
        ImGuiTableFlags_Resizable | 
        ImGuiTableFlags_RowBg | 
        ImGuiTableFlags_NoBordersInBody |
        ImGuiTableFlags_ScrollX;
}
void LE3EditorTabAssets::update() {
    if (ImGui::BeginTabBar("##AssetsTabBar")) {
        if (ImGui::BeginTabItem("Shaders")) {
            updateShaders();
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("Materials")) {
            updateMaterials();
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("Textures")) {
            updateTextures();
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("Meshes")) {
            updateMeshes();
            ImGui::EndTabItem();
        }
        ImGui::EndTabBar();
    }
}


void LE3EditorTabAssets::updateShaders() {
    std::map<std::string, std::pair<std::string, std::string>> shadersPaths = LE3GetAssetManager().getShadersPaths();

    if (ImGui::BeginTable("##ShadersTable", 3, flags)) {
        ImGui::TableSetupColumn("Name", ImGuiTableColumnFlags_NoHide);
        ImGui::TableSetupColumn("Path (Vertex)", ImGuiTableColumnFlags_NoHide);
        ImGui::TableSetupColumn("Path (Fragment)", ImGuiTableColumnFlags_NoHide);
        ImGui::TableHeadersRow();

        for (auto& [name, paths] : shadersPaths) {
            ImGui::TableNextRow();
            ImGui::TableNextColumn();
            ImGui::Selectable(name.c_str());
            if (ImGui::IsItemClicked()) {
                // ...
            }
            ImGui::TableNextColumn();
            ImGui::Text(paths.first.c_str());
            ImGui::TableNextColumn();
            ImGui::Text(paths.second.c_str());
        }

        ImGui::EndTable();
    }
}
void LE3EditorTabAssets::updateMaterials() {

}
void LE3EditorTabAssets::updateTextures() {

}
void LE3EditorTabAssets::updateMeshes() {

}