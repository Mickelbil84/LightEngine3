#include "le3_script_bindings.h"
#include "le3_engine_systems.h"
using namespace le3;

#include <imgui.h>

static int bnd_LE3EngineConfig_setImGuiStyle(lua_State* L) {
    int idx = 1;
    ImGuiCol_ col = (ImGuiCol_)(int)LE3GetScriptSystem().getNumber(idx++);
    float r = LE3GetScriptSystem().getNumber(idx++);
    float g = LE3GetScriptSystem().getNumber(idx++);
    float b = LE3GetScriptSystem().getNumber(idx++);
    float a = LE3GetScriptSystem().getNumber(idx++);
    ImGuiStyle& style = ImGui::GetStyle();
    style.Colors[col] = ImVec4(r, g, b, a);
    return 0;
}

static const luaL_Reg LE3EngineConfigLib[] = {
    {"set_imgui_style", bnd_LE3EngineConfig_setImGuiStyle},
    {NULL, NULL}
};

int le3::luaopen_LE3EngineConfig(lua_State* L) {
    luaL_newlib(L, LE3EngineConfigLib);
    return 1;
}