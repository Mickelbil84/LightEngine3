#include "le3_script_bindings.h"
#include "le3_engine_systems.h"
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

LIB(ImGui,
    CollapsingHeader, TreeNode, TreePop,
    InputText, Checkbox, ColorEdit3, ColorEdit4,
    InputInt, InputFloat, InputFloat2, InputFloat3, InputFloat4
)