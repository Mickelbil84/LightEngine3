#include "scripting/le3_script_bindings.h"
#include "core/le3_engine_systems.h"
using namespace le3;

#include <imgui_internal.h>

FBIND(ImGui, CollapsingHeader)
    GET_STRING(label)
    PUSH_BOOL(ImGui::CollapsingHeader(label.c_str(), ImGuiTreeNodeFlags_DefaultOpen))
FEND()
FBIND(ImGui, TreeNode)
    GET_STRING(label)
    PUSH_BOOL(ImGui::TreeNodeEx(label.c_str(), ImGuiTreeNodeFlags_DefaultOpen))
FEND()
FBIND(ImGui, TreePop)
    ImGui::TreePop();
FEND()

FBIND(ImGui, Text)
    GET_STRING(text)
    ImGui::Text("%s", text.c_str());
FEND()

FBIND(ImGui, TextColored)
    GET_VEC4(color)
    GET_STRING(text)
    ImGui::TextColored(ImVec4(color.x, color.y, color.z, color.w), "%s", text.c_str());
FEND()

FBIND(ImGui, TextWrapped)
    GET_STRING(text)
    ImGui::TextWrapped("%s", text.c_str());
FEND()

FBIND(ImGui, Button)
    GET_STRING(label)
    PUSH_BOOL(ImGui::Button(label.c_str()))
FEND()

FBIND(ImGui, SameLine)
    ImGui::SameLine();
FEND()

FBIND(ImGui, InputText)
    GET_STRING(label)
    GET_STRING(prev)
    char buffer[256] = {0};
    prev.copy(buffer, prev.size());
    ImGui::InputText(label.c_str(), buffer, 256);
    PUSH_STRING(std::string(buffer))
FEND()

FBIND(ImGui, ColorEdit3)
    GET_STRING(label)
    GET_VEC3(prev)
    float vec[3] = {prev.x, prev.y, prev.z};
    ImGui::ColorEdit3(label.c_str(), vec);
    glm::vec3 result(vec[0], vec[1], vec[2]);
    PUSH_VEC3(result)
FEND()

FBIND(ImGui, ColorEdit4)
    GET_STRING(label)
    GET_VEC4(prev)
    float vec4[4] = {prev.x, prev.y, prev.z, prev.w};
    ImGui::ColorEdit4(label.c_str(), vec4);
    glm::vec4 result(vec4[0], vec4[1], vec4[2], vec4[3]);
    PUSH_VEC4(result)
FEND()

FBIND(ImGui, Checkbox)
    GET_STRING(label)
    GET_BOOL(prev)
    bool val = prev;
    ImGui::Checkbox(label.c_str(), &val);
    PUSH_BOOL(val)
FEND()

FBIND(ImGui, RadioButtons)
    GET_STRING_ARRAY(labels)
    GET_STRING(prev)

    int val = -1;
    for (int i = 0; i < labels.size(); i++)
        if (labels[i] == prev) {
            val = i; break;
        }
    if (val == -1) val = 0;
    for (int i = 0; i < labels.size(); i++) {
        ImGui::RadioButton(labels[i].c_str(), &val, i);
        if (i < labels.size() - 1 && (i == 0 || i % 2 != 0)) ImGui::SameLine();
    }
    PUSH_STRING(labels[val])
FEND()

FBIND(ImGui, InputInt)
    GET_STRING(label)
    GET_INT(prev)
    int val = prev;
    ImGui::InputInt(label.c_str(), &val);
    PUSH_NUMBER(val)
FEND()

FBIND(ImGui, InputFloat)
    GET_STRING(label)
    GET_NUMBER(prev)
    float val = prev;
    ImGui::InputFloat(label.c_str(), &val);
    PUSH_NUMBER(val)
FEND()

FBIND(ImGui, InputFloat2) 
    GET_STRING(label)
    GET_VEC2(prev)
    float vec[2] = {prev.x, prev.y};
    ImGui::InputFloat2(label.c_str(), vec);
    glm::vec2 result(vec[0], vec[1]);
    PUSH_VEC2(result)
FEND()

FBIND(ImGui, InputFloat3) 
    GET_STRING(label)
    GET_VEC3_(prev)
    float vec[3] = {prev.x, prev.y, prev.z};
    ImGui::InputFloat3(label.c_str(), vec);
    glm::vec3 result(vec[0], vec[1], vec[2]);
    PUSH_VEC3(result)
FEND()

FBIND(ImGui, InputFloat4) 
    GET_STRING(label)
    GET_QUAT(prev)
    float vec[4] = {prev.w, prev.x, prev.y, prev.z};
    ImGui::InputFloat4(label.c_str(), vec);
    glm::quat result(vec[0], vec[1], vec[2], vec[3]);
    PUSH_QUAT(result)
FEND()


FBIND(ImGui, Combo_Animation) 
    GET_STRING(label)
    GET_STRING(meshName)
    GET_STRING(prev)

    LE3SkeletalMeshPtr pSkeletalMesh = LE3GetAssetManager().getSkeletalMesh(meshName);
    std::vector<const char*> animationNames;
    animationNames.push_back(DEFAULT_EMPTY_ANIMATION_NAME.c_str());
    int selected = 0, jdx = 1;
    for (auto& [name, track] : pSkeletalMesh.lock()->getAnimationTracks()) {
        animationNames.push_back(name.c_str());
        if (name == prev) selected = jdx;
        jdx++;
    }
    ImGui::Combo(label.c_str(), &selected, animationNames.data(), animationNames.size());
    std::string result = animationNames[selected];
    PUSH_STRING(result)
FEND()


LIB(ImGui,
    CollapsingHeader, TreeNode, TreePop, Text, TextColored, TextWrapped, Button, SameLine,
    InputText, Checkbox, RadioButtons, ColorEdit3, ColorEdit4,
    InputInt, InputFloat, InputFloat2, InputFloat3, InputFloat4,
    Combo_Animation,
)