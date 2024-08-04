#include "le3_imgui_utils.h"
using namespace le3;

#include "_imgui.h"
#include <SDL2/SDL.h>

void LE3ImGuiUtils::addSceneViewport(std::string title, LE3Scene& scene, LE3EngineState& engineState) {
    ImGui::Begin(title.c_str(), nullptr, ImGuiWindowFlags_NoMove);
            
    // Handle resize
    ImVec2 view = ImGui::GetContentRegionAvail();
    ImVec2 pos = ImGui::GetWindowPos();
    ImVec2 size = ImGui::GetWindowSize();
    scene.updateOffset(pos.x + (size.x - view.x) / 2, pos.y + (size.y - view.y) / 2);
    if (
        view.x != scene.getSceneFramebuffer()->getWidth() ||
        view.y != scene.getSceneFramebuffer()->getHeight()) {
        if ( view.x <= 0 || view.y <= 0 ) {
            view.x = 1; view.y = 1;
        }
        
        scene.resize(view.x, view.y);
    }

    ImGui::Image(
        (void*)reinterpret_cast<int*>(scene.getSceneFramebuffer()->getColorTexture()), 
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
        (void*)reinterpret_cast<int*>(buffer->getDepthStencilTexture()), 
        ImVec2(view.x, view.y), {0, 1}, {1, 0});
    ImGui::End();
}

glm::vec3 LE3ImGuiUtils::getRelativeCursor(int width, int height, int offsetX, int offsetY) {
    glm::vec3 result(0.f);
    int cursorX, cursorY;
    SDL_GetGlobalMouseState(&cursorX, &cursorY);
    result.x = (float)(cursorX - offsetX) / (float) width;
    result.y = (float)(cursorY - offsetY) / (float) height;
    if (result.x < 0.f || result.x > 1.f || result.y < 0.f || result.y > 1.f) {
        result.z = -1.f;
        return result;
    }
    result = result * 2.f - 1.f;
    result.y =  -result.y;
    result.z = 1.f;
    return result;
}