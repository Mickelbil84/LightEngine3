#include "le3_imgui_utils.h"
using namespace le3;

#include "_imgui.h"

void LE3ImGuiUtils::addSceneViewport(std::string title, LE3Scene& scene, LE3GameEngineState& engineState) {
    ImGui::Begin(title.c_str(), nullptr, ImGuiWindowFlags_NoMove);
            
    // Handle resize
    ImVec2 view = ImGui::GetContentRegionAvail();
    if (
        view.x != scene.getSceneFramebuffer()->getWidth() ||
        view.y != scene.getSceneFramebuffer()->getHeight()) {
        if ( view.x <= 0 || view.y <= 0 ) {
            view.x = 1; view.y = 1;
        }
        
        scene.resize(view.x, view.y);
    }

    ImGui::Image(
        (void*)(int*)scene.getSceneFramebuffer()->getColorTexture(), 
        ImVec2(view.x, view.y), {0, 1}, {1, 0});
    if (!engineState.getFocusedOverride() || engineState.getFocusOverrider() == title) {
        engineState.setFocusedOverride(ImGui::IsWindowHovered());
        if (ImGui::IsWindowHovered()) engineState.setFocusOverrider(title);
    }

    ImGui::End();
}

void LE3ImGuiUtils::addDepthFramebufferViewport(std::string title, LE3FramebufferPtr& buffer) {
    ImGui::Begin(title.c_str(), nullptr, ImGuiWindowFlags_NoMove);
    ImVec2 view = ImGui::GetContentRegionAvail();
    ImGui::Image(
        (void*)(int*)buffer->getDepthStencilTexture(), 
        ImVec2(view.x, view.y), {0, 1}, {1, 0});
    ImGui::End();
}