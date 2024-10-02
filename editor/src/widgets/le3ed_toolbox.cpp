#include "widgets/le3ed_toolbox.h"
using namespace le3;

#include <imgui_internal.h>

void LE3EditorToolbox::init() {
    m_buttons.push_back(LE3EditorToolbarButton("Cube", "icon_newcube"));
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
        ImGui::ImageButton(button.name.c_str(), reinterpret_cast<void*>(LE3GetAssetManager().getTexture(button.iconName)->getTextureID()), ImVec2(24, 24));
    }
}