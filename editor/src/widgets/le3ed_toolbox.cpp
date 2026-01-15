#include "widgets/le3ed_toolbox.h"
using namespace le3;

#include <imgui_internal.h>

void LE3EditorToolbox::init() {
    m_buttons.push_back(LE3EditorToolbarButton("Cube", "icon_newcube", [this]() {
        std::string name = LE3GetActiveScene()->getNextAvailableName("box_0");
        LE3GetActiveScene()->addBox(name, DEFAULT_MATERIAL);
        LE3GetEditorManager().getSelection().selectObject(LE3GetActiveScene()->getObject(name));
    }));
    m_buttons.push_back(LE3EditorToolbarButton("Sphere", "icon_newsphere", [this]() {
        std::string name = LE3GetActiveScene()->getNextAvailableName("sphere_0");
        LE3GetActiveScene()->addSphere(name, DEFAULT_MATERIAL);
        LE3GetEditorManager().getSelection().selectObject(LE3GetActiveScene()->getObject(name));
    }));
    m_buttons.push_back(LE3EditorToolbarButton("Cylinder", "icon_newcylinder", [this]() {
        std::string name = LE3GetActiveScene()->getNextAvailableName("cylinder_0");
        LE3GetActiveScene()->addCylinder(name, DEFAULT_MATERIAL);
        LE3GetEditorManager().getSelection().selectObject(LE3GetActiveScene()->getObject(name));
    }));
    m_buttons.push_back(LE3EditorToolbarButton("Cone", "icon_newcone", [this]() {
        std::string name = LE3GetActiveScene()->getNextAvailableName("cone_0");
        LE3GetActiveScene()->addCone(name, DEFAULT_MATERIAL);
        LE3GetEditorManager().getSelection().selectObject(LE3GetActiveScene()->getObject(name));
    }));
    m_buttons.push_back(LE3EditorToolbarButton("Torus", "icon_newtorus", [this]() {
        std::string name = LE3GetActiveScene()->getNextAvailableName("torus_0");
        LE3GetActiveScene()->addTorus(name, DEFAULT_MATERIAL);
        LE3GetEditorManager().getSelection().selectObject(LE3GetActiveScene()->getObject(name));
    }));
    m_buttons.push_back(LE3EditorToolbarButton("StaticMesh", "icon_newstaticmesh", [this]() {
        auto pStaticMesh = LE3GetEditorManager().getSelection().pStaticMesh.lock();
        auto pSkeletalMesh = LE3GetEditorManager().getSelection().pSkeletalMesh.lock();
        if (pStaticMesh) {
            std::string name = LE3GetActiveScene()->getNextAvailableName(pStaticMesh->getName() + "_0");
            LE3GetActiveScene()->addStaticModel(name, pStaticMesh->getName(), DEFAULT_MATERIAL);
            LE3GetEditorManager().getSelection().selectObject(LE3GetActiveScene()->getObject(name));
        }
        if (pSkeletalMesh) {
            std::string name = LE3GetActiveScene()->getNextAvailableName(pSkeletalMesh->getName() + "_0");
            LE3GetActiveScene()->addSkeletalModel(name, pSkeletalMesh->getName(), DEFAULT_MATERIAL);
            LE3GetEditorManager().getSelection().selectObject(LE3GetActiveScene()->getObject(name));
        }
    }));
    m_buttons.push_back(LE3EditorToolbarButton("Empty", "icon_newempty", [this]() {
        std::string name = LE3GetActiveScene()->getNextAvailableName("empty_0");
        LE3GetActiveScene()->addEmptyObject(name);
        LE3GetEditorManager().getSelection().selectObject(LE3GetActiveScene()->getObject(name));
    }));
    m_buttons.push_back(LE3EditorToolbarButton("ScriptObject", "icon_scriptobject", [this]() {
        std::string name = LE3GetActiveScene()->getNextAvailableName("scriptObject_0");
        LE3GetActiveScene()->addScriptObject(name, "");
        LE3GetEditorManager().getSelection().selectObject(LE3GetActiveScene()->getObject(name));
    }));
    m_buttons.push_back(LE3EditorToolbarButton("PlayerStart", "icon_playerstart", [this]() {
        std::string name = LE3_PLAYERSTART_OBJECT_NAME;
        LE3GetActiveScene()->addPlayerStart();
        LE3GetEditorManager().getSelection().selectObject(LE3GetActiveScene()->getObject(name));
    }));
    m_buttons.push_back(LE3EditorToolbarButton());
    m_buttons.push_back(LE3EditorToolbarButton("AmbientLight", "icon_addambientlight", [this]() {
        std::string name = LE3GetActiveScene()->getNextAvailableName("ambientlight_0");
        LE3GetActiveScene()->addAmbientLight(name);
        LE3GetEditorManager().getSelection().selectObject(LE3GetActiveScene()->getObject(name));
    }));
    m_buttons.push_back(LE3EditorToolbarButton("DirectionalLight", "icon_adddirectionallight", [this]() {
        std::string name = LE3GetActiveScene()->getNextAvailableName("directionallight_0");
        LE3GetActiveScene()->addDirectionalLight(name);
        LE3GetEditorManager().getSelection().selectObject(LE3GetActiveScene()->getObject(name));
        // Add shadow map
        auto pLight = std::dynamic_pointer_cast<LE3DirectionalLight>(LE3GetActiveScene()->getObject(name));
        if (pLight) {
            pLight->addShadowMap(LE3EngineConfig::get<int>("LE3EngineConfig.Rendering.ShadowMapResolution"));
        }
    }));
    m_buttons.push_back(LE3EditorToolbarButton("PointLight", "icon_addpointlight", [this]() {
        std::string name = LE3GetActiveScene()->getNextAvailableName("pointlight_0");
        LE3GetActiveScene()->addPointLight(name);
        LE3GetEditorManager().getSelection().selectObject(LE3GetActiveScene()->getObject(name));
    }));
    m_buttons.push_back(LE3EditorToolbarButton("SpotLight", "icon_addspotlight", [this]() {
        std::string name = LE3GetActiveScene()->getNextAvailableName("spotlight_0");
        LE3GetActiveScene()->addSpotLight(name);
        LE3GetEditorManager().getSelection().selectObject(LE3GetActiveScene()->getObject(name));
        // Add shadow map
        auto pLight = std::dynamic_pointer_cast<LE3SpotLight>(LE3GetActiveScene()->getObject(name));
        if (pLight) {
            pLight->addShadowMap(LE3EngineConfig::get<int>("LE3EngineConfig.Rendering.ShadowMapResolution"));
        }
    }));
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