#include "widgets/le3ed_toolbar.h"
#include "le3ed_editor_systems.h"
using namespace le3;

#include <imgui_internal.h>

void LE3EditorToolbar::init() {
    m_buttons.push_back(LE3EditorToolbarButton("New", "icon_new"));
    m_buttons.push_back(LE3EditorToolbarButton("Open", "icon_open"));
    m_buttons.push_back(LE3EditorToolbarButton("Save", "icon_save"));
    m_buttons.push_back(LE3EditorToolbarButton("SaveAs", "icon_saveas"));
    m_buttons.push_back(LE3EditorToolbarButton());

    // -------

    m_buttons.push_back(LE3EditorToolbarButton("Undo", "icon_undo", []() {
        LE3GetEditorManager().getCommandStack().undo();
    }));
    m_buttons.back().setupHotkey({"KEY_Z", "KEY_LGUI"});
    m_buttons.push_back(LE3EditorToolbarButton("Redo", "icon_redo", []() {
        LE3GetEditorManager().getCommandStack().redo();
    }));
    m_buttons.back().setupHotkey({"KEY_Y", "KEY_LGUI"});
    m_buttons.push_back(LE3EditorToolbarButton());

    // -------

    m_buttons.push_back(LE3EditorToolbarButton("Select", "icon_gizmo_select", []() {
        LE3GetEditorManager().getGizmo()->setMode(LE3_GIZMO_MODE_SELECT);
    }));
    m_buttons.back().setupHotkey({"KEY_Q"});
    m_buttons.push_back(LE3EditorToolbarButton("Move", "icon_gizmo_move", []() {
        LE3GetEditorManager().getGizmo()->setMode(LE3_GIZMO_MODE_TRANSLATE);
    }));
    m_buttons.back().setupHotkey({"KEY_W"});
    m_buttons.push_back(LE3EditorToolbarButton("Rotate", "icon_gizmo_rotate", []() {
        LE3GetEditorManager().getGizmo()->setMode(LE3_GIZMO_MODE_ROTATE);
    }));
    m_buttons.back().setupHotkey({"KEY_E"});
    m_buttons.push_back(LE3EditorToolbarButton("Scale", "icon_gizmo_scale", []() {
        LE3GetEditorManager().getGizmo()->setMode(LE3_GIZMO_MODE_SCALE);
    }));
    m_buttons.back().setupHotkey({"KEY_R"});
    m_buttons.push_back(LE3EditorToolbarButton("Snap", "icon_magnet", []() {
        LE3GetEditorManager().getSnap().enabled = !LE3GetEditorManager().getSnap().enabled;
    }));
    m_buttons.back().isToggled = []() { return LE3GetEditorManager().getSnap().enabled; };
    m_buttons.back().setupHotkey({"KEY_X"});
    m_buttons.push_back(LE3EditorToolbarButton());
    // -------

    m_buttons.push_back(LE3EditorToolbarButton("Collision", "icon_collision"));
    m_buttons.push_back(LE3EditorToolbarButton("BulletCollision", "icon_bulletcollision"));
    m_buttons.push_back(LE3EditorToolbarButton());

    // -------

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
        ImVec4 bg(0.f, 0.f, 0.f, 0.f);
        if (button.isToggled && button.isToggled()) bg = ImVec4(0.5f, 0.5f, 0.5f, 0.5f);
        bool clicked = ImGui::ImageButton(
            button.name.c_str(), 
            reinterpret_cast<void*>(LE3GetAssetManager().getTexture(button.iconName)->getTextureID()), 
            ImVec2(LE3ED_TOOLBAR_BUTTON_SIZE, LE3ED_TOOLBAR_BUTTON_SIZE), 
            ImVec2(0, 0), ImVec2(1, 1), bg);
        if (button.onClick && clicked) {
            button.onClick();
        }
    }
}