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
        if (ImGui::BeginTabItem("Animations")) {
            updateAnimations();
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
            bool selected = LE3GetEditorManager().getSelection().pShader == LE3GetAssetManager().getShader(name);

            ImGui::TableNextRow();
            ImGui::TableNextColumn();
            ImGui::Selectable(name.c_str(), selected, ImGuiSelectableFlags_SpanAllColumns);
            if (ImGui::IsItemClicked()) {
                LE3GetEditorManager().getSelection().selectAsset(LE3GetAssetManager().getShader(name));
            }
            ImGui::TableNextColumn();
            ImGui::Text("%s", paths.first.c_str());
            ImGui::TableNextColumn();
            ImGui::Text("%s", paths.second.c_str());
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
            bool selected = LE3GetEditorManager().getSelection().pMaterial == material;
            ImGui::TableNextRow();
            ImGui::TableNextColumn();
            ImGui::Selectable(name.c_str(), selected, ImGuiSelectableFlags_SpanAllColumns);
            if (ImGui::IsItemClicked()) {
                LE3GetEditorManager().getSelection().selectAsset(material);
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
            bool selected = LE3GetEditorManager().getSelection().pTexture == LE3GetAssetManager().getTexture(name);
            ImGui::TableNextRow();
            ImGui::TableNextColumn();
            ImGui::Selectable(name.c_str(), selected, ImGuiSelectableFlags_SpanAllColumns);
            if (ImGui::IsItemClicked()) {
                LE3GetEditorManager().getSelection().selectAsset(LE3GetAssetManager().getTexture(name));
            }
            ImGui::TableNextColumn();
            ImGui::Text("%s", path.c_str());
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
            bool isSkeletal = LE3GetAssetManager().isSkeletalMesh(name);
            bool selected = 
                !isSkeletal && (LE3GetEditorManager().getSelection().pStaticMesh == LE3GetAssetManager().getStaticMesh(name)) ||
                isSkeletal && (LE3GetEditorManager().getSelection().pSkeletalMesh == LE3GetAssetManager().getSkeletalMesh(name));

            ImGui::TableNextRow();
            ImGui::TableNextColumn();
            ImGui::Selectable(name.c_str(), selected, ImGuiSelectableFlags_SpanAllColumns);

            if (ImGui::IsItemClicked()) {
                if (isSkeletal) {
                    LE3GetEditorManager().getSelection().selectAsset(LE3GetAssetManager().getSkeletalMesh(name));
                }
                else {
                    LE3GetEditorManager().getSelection().selectAsset(LE3GetAssetManager().getStaticMesh(name));
                }
            }

            ImGui::TableNextColumn();
            if (isSkeletal) {
                ImGui::Image(
                    reinterpret_cast<void*>(
                        LE3GetAssetManager().getTexture("icon_tick")->getTextureID()
                    ), ImVec2(16, 16));
            }
            else {
                ImGui::Text("");
            }

            ImGui::TableNextColumn();
            ImGui::Text("%s", path.c_str());
        }

        ImGui::EndTable();
    }
}

void LE3EditorTabAssets::updateAnimations() {
    std::map<std::string, std::string> meshesPaths = LE3GetAssetManager().getMeshesPaths();
    std::vector<std::string> skeletalMeshes;
    for (auto& [name, path] : meshesPaths) {
        if (!LE3GetAssetManager().isSkeletalMesh(name)) continue;
        skeletalMeshes.push_back(name);
    }
    std::vector<const char*> skeletalMeshesLabels;
    for (auto& mesh : skeletalMeshes) skeletalMeshesLabels.push_back(mesh.c_str());

    if (skeletalMeshes.size() == 0) {
        ImGui::Text("No skeletal meshes found");
        return;
    }

    static int selectedSkeletalMesh = 0;
    ImGui::Combo("Skeletal Mesh", &selectedSkeletalMesh, skeletalMeshesLabels.data(), skeletalMeshesLabels.size());

    if (ImGui::Button("Add")) {
        // ...
    }
    ImGui::SameLine();
    if (ImGui::Button("Delete")) {
        // ...
    }

    LE3SkeletalMeshPtr pSkeletalMesh = LE3GetAssetManager().getSkeletalMesh(skeletalMeshes[selectedSkeletalMesh]);
    if (ImGui::BeginTable("##AnimationsTable", 1, flags)) {
        ImGui::TableSetupColumn("Name", ImGuiTableColumnFlags_NoHide);
        ImGui::TableHeadersRow();

        for (auto& [name, track] : pSkeletalMesh->getAnimationTracks()) {
            bool selected = (LE3GetEditorManager().getSelection().animationTrack == name) &&
                (LE3GetEditorManager().getSelection().pSkeletalMesh == pSkeletalMesh);
            ImGui::TableNextRow();
            ImGui::TableNextColumn();
            ImGui::Selectable(name.c_str(), selected, ImGuiSelectableFlags_SpanAllColumns);
            if (ImGui::IsItemClicked()) {
                LE3GetEditorManager().getSelection().selectAsset(pSkeletalMesh, name);
            }
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