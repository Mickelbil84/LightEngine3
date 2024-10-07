function update_object_properties_panel(obj)
    local ttype = LE3Object.get_object_type(obj)
    if _G[ttype] == nil then return end
    local tbl = _G[ttype].save(obj)

    local hierarchy = {}
    local curr = _G[ttype]
    while curr ~= nil do
        table.insert(hierarchy, 1, curr)
        curr = curr.__base
    end

    for _, v in ipairs(hierarchy) do
        if (v.properties == nil) then goto continue end

        if (ImGui.CollapsingHeader(v.title)) then
            for _, property in ipairs(v.properties) do
                show_property(property, tbl)
            end
        end
        ::continue::
    end

    _G[ttype].rebuild(obj, tbl)
end

function update_asset_properties_panel(ptr, type)
    local tbl = type.save(ptr)
    if (ImGui.CollapsingHeader(type.title)) then 
        for _, property in ipairs(type.properties) do
            show_property(property, tbl)
        end
    end
    type.rebuild(ptr, tbl)
end

function update_shader_properties_panel(shader)
    update_asset_properties_panel(shader, LE3Shader)
end

function update_material_properties_panel(material)
    update_asset_properties_panel(material, LE3Material)
end

function update_texture_properties_panel(texture)
    ImGui.CollapsingHeader("LE3Texture")
end

function update_static_mesh_properties_panel(static_mesh)
    ImGui.CollapsingHeader("LE3StaticMesh")
end

function update_skeletal_mesh_properties_panel(skeletal_mesh)
    ImGui.CollapsingHeader("LE3SkeletalMesh")
end


function show_property(property, tbl)
    if property.type == "string" then
        local value = tbl[property.name]
        tbl[property.name]  = ImGui.InputText(property.name, value)
    end
    if property.type == "bool" then
        local value = tbl[property.name]
        tbl[property.name]  = ImGui.Checkbox(property.name, value)
    end
    if property.type == "int" then
        local value = tbl[property.name]
        tbl[property.name]  = ImGui.InputInt(property.name, value)
    end
    if property.type == "float" then
        local value = tbl[property.name]
        tbl[property.name]  = ImGui.InputFloat(property.name, value)
    end
    if property.type == "float2" then
        local value = tbl[property.name]
        tbl[property.name]  = table.pack(ImGui.InputFloat2(property.name, table.unpack(value)))
    end
    if property.type == "float3" then
        local value = tbl[property.name]
        tbl[property.name]  = table.pack(ImGui.InputFloat3(property.name, table.unpack(value)))
    end
    if property.type == "float4" then
        local value = tbl[property.name]
        tbl[property.name]  = table.pack(ImGui.InputFloat4(property.name, table.unpack(value)))
    end
    if property.type == "color" then
        local value = tbl[property.name]
        tbl[property.name]  = table.pack(ImGui.ColorEdit3(property.name, table.unpack(value)))
    end
    if property.type == "color4" then 
        local value = tbl[property.name]
        tbl[property.name]  = table.pack(ImGui.ColorEdit4(property.name, table.unpack(value)))
    end
    if property.type == "transform" then
        if (ImGui.TreeNode(property.name)) then
            for _, property_ in ipairs(LE3Transform.properties) do
                show_property(property_, tbl)
            end
            ImGui.TreePop()
        end
    end
    if property.type == "group" then 
        if (ImGui.TreeNode(property.name)) then
            for _, property_ in ipairs(property.properties) do
                show_property(property_, tbl)
            end
            ImGui.TreePop()
        end
    end
end