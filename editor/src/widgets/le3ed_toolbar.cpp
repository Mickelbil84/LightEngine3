#include "widgets/le3ed_toolbar.h"
#include "le3ed_editor_systems.h"
#include "le3ed_project.h"
using namespace le3;

#include "commands/le3ed_com_reparent.h"
#include "commands/le3ed_com_duplicate.h"
#include "commands/le3ed_com_delete_objects.h"
#include "le3ed_events.h"

#include <imgui_internal.h>



void LE3EditorToolbar::init() {
    m_buttons.push_back(LE3EditorToolbarButton("New", "icon_new"));
    m_buttons.push_back(LE3EditorToolbarButton("Open", "icon_open", []() {
        LE3GetActiveScene()->load(LE3ED_PROJECT_SCENES_ROOT + "untitled.lua"); // TODO: Move to scenes component
        LE3GetEventManager().notify(LE3ED_EVENT_ON_SCENE_LOAD, nullptr);
    }));
    m_buttons.push_back(LE3EditorToolbarButton("Save", "icon_save", []() {
        LE3GetActiveScene()->save(LE3ED_PROJECT_SCENES_ROOT + "untitled.lua"); // TODO: Move to scenes component
        LE3GetEventManager().notify(LE3ED_EVENT_ON_SCENE_SAVE, nullptr);
    }));
    m_buttons.push_back(LE3EditorToolbarButton("SaveAs", "icon_saveas"));
    m_buttons.push_back(LE3EditorToolbarButton());

    // -------

    m_buttons.push_back(LE3EditorToolbarButton("Undo", "icon_undo", []() {
        LE3GetEditorManager().getCommandStack().undo();
    }));
    m_buttons.back().setupHotkey({"KEY_Z", KEY_LE3_CTRL});
    m_buttons.push_back(LE3EditorToolbarButton("Redo", "icon_redo", []() {
        LE3GetEditorManager().getCommandStack().redo();
    }));
    m_buttons.back().setupHotkey({"KEY_Y", KEY_LE3_CTRL});
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

    m_buttons.push_back(LE3EditorToolbarButton("Skeleton", "icon_skeleton", []() {
        LE3GetVisualDebug().setDrawDebugSkeletons(!LE3GetVisualDebug().getDrawDebugSkeletons());
    }));
    m_buttons.back().isToggled = []() { return LE3GetVisualDebug().getDrawDebugSkeletons(); };
    m_buttons.push_back(LE3EditorToolbarButton("Collision", "icon_collision"));
    m_buttons.push_back(LE3EditorToolbarButton("BulletCollision", "icon_bulletcollision"));
    m_buttons.push_back(LE3EditorToolbarButton());

    // -------


    m_buttons.push_back(LE3EditorToolbarButton("Reparent", "icon_reparent", [this]() {
        std::vector<std::string> names = LE3GetEditorManager().getSelection().getSelectedObjectsNames();
        if (names.size() < 2) return;
        LE3GetEditorManager().getCommandStack().execute(std::make_unique<LE3EditorComReparent>(names));
    }));
    m_buttons.back().setupHotkey({"KEY_P"});
    m_buttons.push_back(LE3EditorToolbarButton("Duplicate", "icon_duplicate", [this]() {
        LE3GetEditorManager().getCommandStack().execute(std::make_unique<LE3EditorComDuplicate>(
            LE3GetEditorManager().getSelection().getSelectedObjectsNames()
        ));
    }));
    m_buttons.back().setupHotkey({"KEY_D", "KEY_LSHIFT"});
    m_buttons.push_back(LE3EditorToolbarButton("Delete", "icon_delete", [this]() {
        LE3GetEditorManager().getCommandStack().execute(std::make_unique<LE3EditorComDeleteObjects>(
            LE3GetEditorManager().getSelection().getSelectedObjectsNames()
        ));
    }));
    m_buttons.back().setupHotkey({"KEY_BACKSPACE"});

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
            LE3GetAssetManager().getTexture(button.iconName).lock()->getTextureID(), 
            ImVec2(LE3ED_TOOLBAR_BUTTON_SIZE, LE3ED_TOOLBAR_BUTTON_SIZE), 
            ImVec2(0, 0), ImVec2(1, 1), bg);
        if (button.onClick && clicked) {
            button.onClick();
        }
    }
    for (auto& [name, popup]: m_popups) {
        popup->update();
    }
}