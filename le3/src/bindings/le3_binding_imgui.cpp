#include "le3_script_bindings.h"
#include "le3_engine_systems.h"
using namespace le3;

#include <imgui_internal.h>

FBIND(ImGui, CollapsingHeader)
    GET_STRING(label)
    PUSH_BOOL(ImGui::CollapsingHeader(label.c_str(), ImGuiTreeNodeFlags_None))
FEND()

LIB(ImGui,
    CollapsingHeader
)