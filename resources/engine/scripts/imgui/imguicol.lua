ImGuiCol_ = {
    "ImGuiCol_Text",
    "ImGuiCol_TextDisabled",
    "ImGuiCol_WindowBg",
    "ImGuiCol_ChildBg",
    "ImGuiCol_PopupBg",
    "ImGuiCol_Border",
    "ImGuiCol_BorderShadow",
    "ImGuiCol_FrameBg",
    "ImGuiCol_FrameBgHovered",
    "ImGuiCol_FrameBgActive",
    "ImGuiCol_TitleBg",
    "ImGuiCol_TitleBgActive",
    "ImGuiCol_TitleBgCollapsed",
    "ImGuiCol_MenuBarBg",
    "ImGuiCol_ScrollbarBg",
    "ImGuiCol_ScrollbarGrab",
    "ImGuiCol_ScrollbarGrabHovered",
    "ImGuiCol_ScrollbarGrabActive",
    "ImGuiCol_CheckMark",
    "ImGuiCol_SliderGrab",
    "ImGuiCol_SliderGrabActive",
    "ImGuiCol_Button",
    "ImGuiCol_ButtonHovered",
    "ImGuiCol_ButtonActive",
    "ImGuiCol_Header",
    "ImGuiCol_HeaderHovered",
    "ImGuiCol_HeaderActive",
    "ImGuiCol_Separator",
    "ImGuiCol_SeparatorHovered",
    "ImGuiCol_SeparatorActive",
    "ImGuiCol_ResizeGrip",
    "ImGuiCol_ResizeGripHovered",
    "ImGuiCol_ResizeGripActive",
    "ImGuiCol_Tab",
    "ImGuiCol_TabHovered",
    "ImGuiCol_TabActive",
    "ImGuiCol_TabUnfocused",
    "ImGuiCol_TabUnfocusedActive",
    "ImGuiCol_DockingPreview",
    "ImGuiCol_DockingEmptyBg",
    "ImGuiCol_PlotLines",
    "ImGuiCol_PlotLinesHovered",
    "ImGuiCol_PlotHistogram",
    "ImGuiCol_PlotHistogramHovered",
    "ImGuiCol_TableHeaderBg",
    "ImGuiCol_TableBorderStrong",
    "ImGuiCol_TableBorderLight",
    "ImGuiCol_TableRowBg",
    "ImGuiCol_TableRowBgAlt",
    "ImGuiCol_TextSelectedBg",
    "ImGuiCol_DragDropTarget",
    "ImGuiCol_NavHighlight",
    "ImGuiCol_NavWindowingHighlight",
    "ImGuiCol_NavWindowingDimBg",
    "ImGuiCol_ModalWindowDimBg",
};
ImGuiCol_inv = {}

for idx, str in ipairs(ImGuiCol_) do
    ImGuiCol_inv[str] = idx - 1
end

-- Set the style

function apply_imgui_style() 
    if LE3EngineConfig.ImGuiStyle ~= nil then
        for str, color in pairs(LE3EngineConfig.ImGuiStyle) do
            LE3EngineConfig.set_imgui_style(ImGuiCol_inv[str], table.unpack(color))
        end
    end
end