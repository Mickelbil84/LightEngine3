#include "widgets/le3ed_toolbar.h"
using namespace le3;

#include <imgui_internal.h>

void LE3EditorToolbar::init() {
    m_buttons.push_back(LE3EditorToolbarButton("New", "icon_new"));
    m_buttons.push_back(LE3EditorToolbarButton("Open", "icon_open"));
    m_buttons.push_back(LE3EditorToolbarButton("Save", "icon_save"));
    m_buttons.push_back(LE3EditorToolbarButton("SaveAs", "icon_saveas"));
    m_buttons.push_back(LE3EditorToolbarButton());
    m_buttons.push_back(LE3EditorToolbarButton("Undo", "icon_undo", []() {
        LE3GetEditorManager().getCommandStack().undo();
    }));
    m_buttons.push_back(LE3EditorToolbarButton("Redo", "icon_redo", []() {
        LE3GetEditorManager().getCommandStack().redo();
    }));
    m_buttons.push_back(LE3EditorToolbarButton());
    m_buttons.push_back(LE3EditorToolbarButton("Select", "icon_gizmo_select"));
    m_buttons.push_back(LE3EditorToolbarButton("Move", "icon_gizmo_move"));
    m_buttons.push_back(LE3EditorToolbarButton("Rotate", "icon_gizmo_rotate"));
    m_buttons.push_back(LE3EditorToolbarButton("Scale", "icon_gizmo_scale"));
    m_buttons.push_back(LE3EditorToolbarButton());
    m_buttons.push_back(LE3EditorToolbarButton("Collision", "icon_collision"));
    m_buttons.push_back(LE3EditorToolbarButton("BulletCollision", "icon_bulletcollision"));
    m_buttons.push_back(LE3EditorToolbarButton());
    m_buttons.push_back(LE3EditorToolbarButton("Reparent", "icon_reparent"));
    m_buttons.push_back(LE3EditorToolbarButton("Duplicate", "icon_duplicate"));

}
void LE3EditorToolbar::update() {
    for (auto button : m_buttons) {
        ImGui::SameLine();
        if (button.separator) {
            ImGui::SeparatorEx(ImGuiSeparatorFlags_Vertical);
            continue;
        }
        bool clicked = ImGui::ImageButton(
            button.name.c_str(), 
            reinterpret_cast<void*>(LE3GetAssetManager().getTexture(button.iconName)->getTextureID()), 
            ImVec2(LE3ED_TOOLBAR_BUTTON_SIZE, LE3ED_TOOLBAR_BUTTON_SIZE));
        if (button.onClick && clicked) {
            button.onClick();
        }
    }
}