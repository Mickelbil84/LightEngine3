#include "widgets/le3ed_toolbar.h"
#include "le3ed_editor_systems.h"
#include "tools/le3_tool_pkg.h"
using namespace le3;

#include "commands/le3ed_com_reparent.h"
#include "commands/le3ed_com_duplicate.h"
#include "commands/le3ed_com_delete_objects.h"
#include "le3ed_events.h"
#include "le3ed_project.h"
#include "le3ed_cache.h"

#include <imgui_internal.h>



void LE3EditorToolbar::init() {
    m_buttons.push_back(LE3EditorToolbarButton("New", "icon_new", []() {
        LE3EditorSystems::instance().getScenesComponent()->loadScene("");
    }));
    m_buttons.back().setupHotkey({"KEY_N", KEY_LE3_CTRL});

    m_buttons.push_back(LE3EditorToolbarButton("Open", "icon_open", []() {
        LE3EditorSystems::instance().getScenesComponent()->openLoadScenePopup();
    }));
    m_buttons.back().setupHotkey({"KEY_O", KEY_LE3_CTRL});
    m_popups[LE3ED_POP_LOAD_SCENE] = LE3EditorSystems::instance().getScenesComponent()->getLoadScenePopup();

    m_buttons.push_back(LE3EditorToolbarButton("Save", "icon_save", []() {
        std::string sceneName = LE3GetConfig<std::string>("LE3ProjectConfig.LastOpenedScene", "");
        if (sceneName.size() == 0) {
            LE3EditorSystems::instance().getScenesComponent()->openSaveScenePopup();
        } else {
            LE3EditorSystems::instance().getScenesComponent()->saveScene(sceneName);
        }
    }));
    m_buttons.back().setupHotkey({"KEY_S", KEY_LE3_CTRL});

    m_buttons.push_back(LE3EditorToolbarButton("SaveAs", "icon_saveas", []() {
        LE3EditorSystems::instance().getScenesComponent()->openSaveScenePopup();
    }));
    m_buttons.back().setupHotkey({"KEY_S", KEY_LE3_CTRL, "KEY_LSHIFT"});
    m_popups[LE3ED_POP_SAVE_SCENE] = LE3EditorSystems::instance().getScenesComponent()->getSaveScenePopup();

    m_buttons.push_back(LE3EditorToolbarButton("ReloadAssets", "icon_reloadassets", []() {
        std::string projectPath = LE3EditorCache::getMostRecentProject();
        LE3ToolPkg::run(projectPath, projectPath);
        LE3GetEditorManager().setSelectedFile("");
        LE3GetDatFileSystem().closeArchives([](std::string archiveName) {
            if (archiveName == "engine") return false;
            if (archiveName == "editor") return false;
            if (archiveName == "demos") return false;
            if (archiveName == "le3proj") return false;
            if (archiveName == "le3edcache") return false;
            return true;
        });
    }));
    m_buttons.back().setupHotkey({"KEY_R", KEY_LE3_CTRL, "KEY_LSHIFT"});


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
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.f, 0.f));
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0.f, 0.f));
    ImGui::PushStyleVar(ImGuiStyleVar_WindowMinSize, ImVec2(0.f, 0.f));
    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.f, 0.f, 0.f, 0.f));
    ImGui::Begin("##Toolbar", nullptr, ImGuiWindowFlags_NoMove | 
            ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | 
            ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_AlwaysAutoResize);

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

    ImGui::PopStyleColor(1);
    ImGui::PopStyleVar(3);
    
    LE3EditorSystems::instance().updatePopups();
    
    ImGui::End();
}