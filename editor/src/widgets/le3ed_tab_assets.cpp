#include "widgets/le3ed_tab_assets.h"
using namespace le3;

void LE3EditorTabAssets::init() {
    m_bShowEngineAssets = false;
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

void LE3EditorTabAssets::addEngineAssetsCheckbox() {
    ImGui::Checkbox("Show hidden engine assets", &m_bShowEngineAssets);
}


void LE3EditorTabAssets::updateShaders() {
    std::map<std::string, std::pair<std::string, std::string>> shadersPaths = LE3GetAssetManager().getShadersPaths();

    addEngineAssetsCheckbox();
    if (ImGui::Button("Add")) {
        // ...
    }
    ImGui::SameLine();
    if (ImGui::Button("Delete")) {
        // ...
    }

    if (ImGui::BeginTable("##ShadersTable", 3, flags)) {
        ImGui::TableSetupColumn("Name", ImGuiTableColumnFlags_NoHide);
        ImGui::TableSetupColumn("Path (Vertex)", ImGuiTableColumnFlags_NoHide);
        ImGui::TableSetupColumn("Path (Fragment)", ImGuiTableColumnFlags_NoHide);
        ImGui::TableHeadersRow();

        for (auto& [name, paths] : shadersPaths) {
            if (!m_bShowEngineAssets && isEngineAsset(name, paths.first)) continue;
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
    std::map<std::string, LE3MaterialPtr> materials = LE3GetAssetManager().getMaterials();

    addEngineAssetsCheckbox();
    if (ImGui::Button("Add")) {
        // ...
    }
    ImGui::SameLine();
    if (ImGui::Button("Delete")) {
        // ...
    }

    if (ImGui::BeginTable("##MaterialsTable", 2, flags)) {
        ImGui::TableSetupColumn("Name", ImGuiTableColumnFlags_NoHide);
        ImGui::TableSetupColumn("Shader", ImGuiTableColumnFlags_NoHide);
        ImGui::TableHeadersRow();

        for (auto& [name, material] : materials) {
            if (!m_bShowEngineAssets && isEngineAsset(name, "")) continue;
            ImGui::TableNextRow();
            ImGui::TableNextColumn();
            ImGui::Selectable(name.c_str());
            if (ImGui::IsItemClicked()) {
                // ...
            }
            ImGui::TableNextColumn();
            ImGui::Text("%s", material->shader->getName().c_str());
        }

        ImGui::EndTable();
    }
}
void LE3EditorTabAssets::updateTextures() {
    std::map<std::string, std::string> texturesPaths = LE3GetAssetManager().getTexturesPaths();

    addEngineAssetsCheckbox();
    if (ImGui::Button("Add")) {
        // ...
    }
    ImGui::SameLine();
    if (ImGui::Button("Delete")) {
        // ...
    }

    if (ImGui::BeginTable("##TexturesTable", 2, flags)) {
        ImGui::TableSetupColumn("Name", ImGuiTableColumnFlags_NoHide);
        ImGui::TableSetupColumn("Path", ImGuiTableColumnFlags_NoHide);
        ImGui::TableHeadersRow();

        for (auto& [name, path] : texturesPaths) {
            if (!m_bShowEngineAssets && isEngineAsset(name, path)) continue;
            ImGui::TableNextRow();
            ImGui::TableNextColumn();
            ImGui::Selectable(name.c_str());
            if (ImGui::IsItemClicked()) {
                // ...
            }
            ImGui::TableNextColumn();
            ImGui::Text(path.c_str());
        }

        ImGui::EndTable();
    }
}
void LE3EditorTabAssets::updateMeshes() {
    std::map<std::string, std::string> meshesPaths = LE3GetAssetManager().getMeshesPaths();

    addEngineAssetsCheckbox();
    if (ImGui::Button("Add")) {
        // ...
    }
    ImGui::SameLine();
    if (ImGui::Button("Delete")) {
        // ...
    }

    if (ImGui::BeginTable("##MeshesTable", 3, flags)) {
        ImGui::TableSetupColumn("Name", ImGuiTableColumnFlags_NoHide);
        ImGui::TableSetupColumn("Skeletal", ImGuiTableColumnFlags_NoHide);
        ImGui::TableSetupColumn("Path", ImGuiTableColumnFlags_NoHide);
        ImGui::TableHeadersRow();

        for (auto& [name, path] : meshesPaths) {
            if (!m_bShowEngineAssets && isEngineAsset(name, path)) continue;
            ImGui::TableNextRow();
            ImGui::TableNextColumn();
            ImGui::Selectable(name.c_str());
            if (ImGui::IsItemClicked()) {
                // ...
            }

            ImGui::TableNextColumn();
            if (LE3GetAssetManager().isSkeletalMesh(name)) {
                ImGui::Image(
                    reinterpret_cast<void*>(
                        LE3GetAssetManager().getTexture("icon_tick")->getTextureID()
                    ), ImVec2(16, 16));
            }
            else {
                ImGui::Text("");
            }

            ImGui::TableNextColumn();
            ImGui::Text(path.c_str());
        }

        ImGui::EndTable();
    }
}

bool LE3EditorTabAssets::isEngineAsset(std::string name, std::string path) {
    if (name.starts_with(DEFAULT_ENGINE_PREFIX)) return true;
    if (path.starts_with("/engine")) return true;
    if (path.starts_with("/editor")) return true;
    return false;
}