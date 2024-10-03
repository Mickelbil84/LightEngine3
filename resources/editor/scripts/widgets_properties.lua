function update_properties_panel(obj) 
    local ttype = LE3Object.get_object_type(obj)
    local tbl = _G[ttype].save(obj)

    ImGui.CollapsingHeader("Object")

    print(tbl.Name)
end