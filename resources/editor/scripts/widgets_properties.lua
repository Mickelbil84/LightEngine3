function update_properties_panel(obj) 
    local ttype = LE3Object.get_object_type(obj)
    local tbl = _G[ttype].save(obj)

    ImGui.CollapsingHeader("Object")

    tbl.Position = table.pack(ImGui.InputFloat3("Position", table.unpack(tbl.Position)))
    LE3Transform.load(LE3Object.get_transform(obj), tbl)
end