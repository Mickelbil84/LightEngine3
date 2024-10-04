#include "le3_script_bindings.h"
#include "le3_engine_systems.h"
using namespace le3;

#include <imgui_internal.h>

FBIND(ImGui, CollapsingHeader)
    GET_STRING(label)
    PUSH_BOOL(ImGui::CollapsingHeader(label.c_str(), ImGuiTreeNodeFlags_None))
FEND()

FBIND(ImGui, InputFloat3) 
    GET_STRING(label)
    GET_VEC3_(prev)
    float vec[3] = {prev.x, prev.y, prev.z};
    ImGui::InputFloat3(label.c_str(), vec);
    glm::vec3 result(vec[0], vec[1], vec[2]);
    PUSH_VEC3(result)
FEND()

LIB(ImGui,
    CollapsingHeader,
    InputFloat3,
)