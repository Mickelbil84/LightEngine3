#include "widgets/le3ed_tab_assets.h"
#include "commands/le3ed_com_delete_mesh.h"
#include "commands/le3ed_com_delete_shader.h"
#include "commands/le3ed_com_delete_texture.h"
#include "commands/le3ed_com_delete_material.h"
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
        m_popAddShader.init();
        ImGui::OpenPopup((LE3ED_POP_ADD_SHADER).c_str());
    }
    ImGui::SameLine();
    if (ImGui::Button("Delete")) {
        std::shared_ptr<LE3Shader> pShader = LE3GetEditorManager().getSelection().pShader.lock();
        if (pShader) {
            std::pair<std::string, std::string> paths = LE3GetAssetManager().getShaderPaths(pShader->getName());
            LE3GetEditorManager().getCommandStack().execute(std::make_unique<LE3EditorComDeleteShader>(
                pShader->getName(), paths.first, paths.second
            ));
            LE3GetEditorManager().getSelection().deselect();
        }
    }

    m_popAddShader.update();

    if (ImGui::BeginTable("##ShadersTable", 3, flags)) {
        ImGui::TableSetupColumn("Name", ImGuiTableColumnFlags_NoHide);
        ImGui::TableSetupColumn("Path (Vertex)", ImGuiTableColumnFlags_NoHide);
        ImGui::TableSetupColumn("Path (Fragment)", ImGuiTableColumnFlags_NoHide);
        ImGui::TableHeadersRow();

        for (auto& [name, paths] : shadersPaths) {
            if (!m_bShowEngineAssets && isEngineAsset(name, paths.first)) continue;
            bool selected = LE3GetEditorManager().getSelection().type == LE3EditorSelection::LE3_SELECTION_ASSET_SHADER &&
                LE3GetEditorManager().getSelection().pShader.lock() &&
                LE3GetEditorManager().getSelection().pShader.lock()->getName() == name;

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
    std::map<std::string, std::shared_ptr<LE3Material>> materials = LE3GetAssetManager().getMaterials();

    addEngineAssetsCheckbox();
    if (ImGui::Button("Add")) {
        m_popAddMaterial.init();
        ImGui::OpenPopup((LE3ED_POP_ADD_MATERIAL).c_str());
    }
    ImGui::SameLine();
    if (ImGui::Button("Delete")) {
        std::shared_ptr<LE3Material> pMaterial = LE3GetEditorManager().getSelection().pMaterial.lock();
        if (pMaterial) {
            std::string name = pMaterial->name;
            std::string shaderName = !pMaterial->shader.expired() ? pMaterial->shader.lock()->getName() : "";
            LE3GetEditorManager().getCommandStack().execute(std::make_unique<LE3EditorComDeleteMaterial>(name, shaderName));
            LE3GetEditorManager().getSelection().deselect();
        }
    }
    
    m_popAddMaterial.update();

    if (ImGui::BeginTable("##MaterialsTable", 2, flags)) {
        ImGui::TableSetupColumn("Name", ImGuiTableColumnFlags_NoHide);
        ImGui::TableSetupColumn("Shader", ImGuiTableColumnFlags_NoHide);
        ImGui::TableHeadersRow();

        for (auto& [name, material] : materials) {
            if (!m_bShowEngineAssets && isEngineAsset(name, "")) continue;
            bool selected = LE3GetEditorManager().getSelection().type == LE3EditorSelection::LE3_SELECTION_ASSET_MATERIAL &&
                LE3GetEditorManager().getSelection().pMaterial.lock()->name == material->name;
            ImGui::TableNextRow();
            ImGui::TableNextColumn();
            ImGui::Selectable(name.c_str(), selected, ImGuiSelectableFlags_SpanAllColumns);
            if (ImGui::IsItemClicked()) {
                LE3GetEditorManager().getSelection().selectAsset(material);
            }
            ImGui::TableNextColumn();
            std::string shaderName = !material->shader.expired() ? material->shader.lock()->getName() : "[Invalid]";
            ImGui::Text("%s", shaderName.c_str());
        }

        ImGui::EndTable();
    }
}
void LE3EditorTabAssets::updateTextures() {
    std::map<std::string, std::string> texturesPaths = LE3GetAssetManager().getTexturesPaths();

    addEngineAssetsCheckbox();
    if (ImGui::Button("Add")) {
        m_popAddTexture.init();
        ImGui::OpenPopup((LE3ED_POP_ADD_TEXTURE).c_str());
    }
    ImGui::SameLine();
    if (ImGui::Button("Delete")) {
        std::shared_ptr<LE3Texture> pTexture = LE3GetEditorManager().getSelection().pTexture.lock();
        if (pTexture) {
            std::string name = pTexture->getName();
            std::string path = LE3GetAssetManager().getTexturePath(name);
            bool interpolate = pTexture->getInterpolate();
            LE3GetEditorManager().getCommandStack().execute(std::make_unique<LE3EditorComDeleteTexture>(name, path, interpolate));
            LE3GetEditorManager().getSelection().deselect();
        }
    }

    m_popAddTexture.update();

    if (ImGui::BeginTable("##TexturesTable", 2, flags)) {
        ImGui::TableSetupColumn("Name", ImGuiTableColumnFlags_NoHide);
        ImGui::TableSetupColumn("Path", ImGuiTableColumnFlags_NoHide);
        ImGui::TableHeadersRow();

        for (auto& [name, path] : texturesPaths) {
            if (!m_bShowEngineAssets && isEngineAsset(name, path)) continue;
            bool selected = LE3GetEditorManager().getSelection().type == LE3EditorSelection::LE3_SELECTION_ASSET_TEXTURE &&
                LE3GetEditorManager().getSelection().pTexture.lock()->getName() == name;
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
        m_popAddMesh.init();
        ImGui::OpenPopup((LE3ED_POP_ADD_MESH).c_str());
    }
    ImGui::SameLine();
    if (ImGui::Button("Delete")) {
        std::shared_ptr<LE3StaticMesh> pStaticMesh = LE3GetEditorManager().getSelection().pStaticMesh.lock();
        if (pStaticMesh) {
            std::string name = pStaticMesh->getName();
            std::string path = LE3GetAssetManager().getMeshPath(name);
            LE3GetEditorManager().getCommandStack().execute(std::make_unique<LE3EditorComDeleteMesh>(name, path, false));
            LE3GetEditorManager().getSelection().deselect();
        }
        std::shared_ptr<LE3SkeletalMesh> pSkeletalMesh = LE3GetEditorManager().getSelection().pSkeletalMesh.lock();
        if (pSkeletalMesh) {
            std::string name = pSkeletalMesh->getName();
            std::string path = LE3GetAssetManager().getMeshPath(name);
            LE3GetEditorManager().getCommandStack().execute(std::make_unique<LE3EditorComDeleteMesh>(name, path, true));
            LE3GetEditorManager().getSelection().deselect();
        }
    }

    m_popAddMesh.update();

    if (ImGui::BeginTable("##MeshesTable", 3, flags)) {
        ImGui::TableSetupColumn("Name", ImGuiTableColumnFlags_NoHide);
        ImGui::TableSetupColumn("Skeletal", ImGuiTableColumnFlags_NoHide);
        ImGui::TableSetupColumn("Path", ImGuiTableColumnFlags_NoHide);
        ImGui::TableHeadersRow();

        for (auto& [name, path] : meshesPaths) {
            if (!m_bShowEngineAssets && isEngineAsset(name, path)) continue;
            bool isSkeletal = LE3GetAssetManager().isSkeletalMesh(name);
            bool selected = false;
            if (LE3GetEditorManager().getSelection().type == LE3EditorSelection::LE3_SELECTION_ASSET_MESH) {
                selected = 
                    !isSkeletal && (LE3GetEditorManager().getSelection().pStaticMesh.lock()) && (LE3GetEditorManager().getSelection().pStaticMesh.lock()->getName() == name) ||
                    isSkeletal && (LE3GetEditorManager().getSelection().pSkeletalMesh.lock()) && (LE3GetEditorManager().getSelection().pSkeletalMesh.lock()->getName() == name);
            }

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
                        LE3GetAssetManager().getTexture("icon_tick").lock()->getTextureID(), ImVec2(16, 16));
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

        for (auto& [name, track] : pSkeletalMesh.lock()->getAnimationTracks()) {
            bool selected = (LE3GetEditorManager().getSelection().animationTrack == name) &&
                (LE3GetEditorManager().getSelection().pSkeletalMesh.lock()->getName() == pSkeletalMesh.lock()->getName());
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
    if (path.starts_with("/engine") && !path.starts_with("/engine/shaders")) return true;
    if (path.starts_with("/editor")) return true;
    return false;
}