#include "le3_script_bindings.h"
#include "le3_engine_systems.h"
using namespace le3;

#include <imgui.h>

FBIND(LE3EngineConfig, set_imgui_style)
    GET_NUMBER(tmp)
    ImGuiCol_ col = (ImGuiCol_)(int)tmp;
    GET_VEC4(color)
    ImGuiStyle& style = ImGui::GetStyle();
    style.Colors[col] = ImVec4(color.r, color.g, color.b, color.a);
FEND()

LIB(LE3EngineConfig,
    set_imgui_style
)