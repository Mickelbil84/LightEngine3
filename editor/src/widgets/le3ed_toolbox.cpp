#include "widgets/le3ed_toolbox.h"
using namespace le3;

#include <imgui_internal.h>

void LE3EditorToolbox::init() {
    m_buttons.push_back(LE3EditorToolbarButton("Cube", "icon_newcube", [this]() {
        std::string name = LE3GetActiveScene()->getNextAvailableName("box_1");
        LE3GetActiveScene()->addBox(name, DEFAULT_MATERIAL);
        LE3GetEditorManager().getSelection().selectObject(LE3GetActiveScene()->getObject(name));
    }));
    m_buttons.push_back(LE3EditorToolbarButton("Sphere", "icon_newsphere"));
    m_buttons.push_back(LE3EditorToolbarButton("Cylinder", "icon_newcylinder"));
    m_buttons.push_back(LE3EditorToolbarButton("Cone", "icon_newcone"));
    m_buttons.push_back(LE3EditorToolbarButton("Torus", "icon_newtorus"));
    m_buttons.push_back(LE3EditorToolbarButton("StaticMesh", "icon_newstaticmesh"));
    m_buttons.push_back(LE3EditorToolbarButton("Empty", "icon_newempty"));
    m_buttons.push_back(LE3EditorToolbarButton());
    m_buttons.push_back(LE3EditorToolbarButton("AmbientLight", "icon_addambientlight"));
    m_buttons.push_back(LE3EditorToolbarButton("DirectionalLight", "icon_adddirectionallight"));
    m_buttons.push_back(LE3EditorToolbarButton("PointLight", "icon_addpointlight"));
    m_buttons.push_back(LE3EditorToolbarButton("SpotLight", "icon_addspotlight"));
    m_buttons.push_back(LE3EditorToolbarButton());
}
void LE3EditorToolbox::update() {
    for (auto button : m_buttons) {
        if (button.separator) {
            ImGui::SeparatorEx(ImGuiSeparatorFlags_Horizontal);
            continue;
        }
        bool clicked = ImGui::ImageButton(
            button.name.c_str(), 
            LE3GetAssetManager().getTexture(button.iconName).lock()->getTextureID(), 
            ImVec2(LE3ED_TOOLBAR_BUTTON_SIZE, LE3ED_TOOLBAR_BUTTON_SIZE));
        if (button.onClick && clicked) {
            button.onClick();
        }
    }
}