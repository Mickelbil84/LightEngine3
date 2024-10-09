#include "widgets/le3ed_settings_panel.h"
using namespace le3;

void LE3EditorSettingsPanel::init() {

}
void LE3EditorSettingsPanel::update() {
    updateSnapSettings();
    updateSceneSettings();
}


void LE3EditorSettingsPanel::updateSnapSettings() {
    LE3EditorSnap& snap = LE3GetEditorManager().getSnap();
    if (ImGui::CollapsingHeader("Snap Settings", ImGuiTreeNodeFlags_DefaultOpen)) {
        ImGui::InputFloat("Snap Translation", &snap.snapTranslation);
        ImGui::InputFloat("Snap Rotation [deg]", &snap.snapRotation);
        ImGui::InputFloat("Snap Scale", &snap.snapScale);
    }
}

void LE3EditorSettingsPanel::updateSceneSettings() {
    if (ImGui::CollapsingHeader("Scene Settings", ImGuiTreeNodeFlags_DefaultOpen)) {
        glm::vec3 bg = LE3GetActiveScene()->getBackgroundColor();
        float tmp[3] = {bg.r, bg.g, bg.b};
        ImGui::ColorEdit3("Background Color", tmp);
        LE3GetActiveScene()->setBackgroundColor(glm::vec3(tmp[0], tmp[1], tmp[2]));
    }
}