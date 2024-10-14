function update_object_properties_panel(obj)
    local ttype = LE3Object.get_object_type(obj)
    if _G[ttype] == nil or _G[ttype].save == nil then 
        ImGui.Text("Unsupported object type: " .. ttype)
        return 
    end
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
                show_property(property, tbl, obj)
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
    ptr = tbl.Name -- in case of renames, update the "pointer"
    if (type.reload ~= nil) then 
        if (ImGui.Button("Save")) then
            print("!!!!!!!!!!!!")
            print(type.reload)
            print("!!!!!!!!!!!!")
            type.reload(ptr, tbl)
        end
    end
end


function update_shader_properties_panel(shader)
    update_asset_properties_panel(shader, LE3Shader)

    if (ImGui.TreeNode("Shader Compile Status")) then 
        ImGui.Text("Status:")
        ImGui.SameLine()
        local is_ok = LE3Shader.is_ok(shader)
        if is_ok then 
            ImGui.TextColored(0, 0.6, 0, 1, "OK")
        else
            ImGui.TextColored(0.6, 0, 0, 1, "ERROR")
            ImGui.TextWrapped(LE3Shader.get_error(shader))
        end

        ImGui.TreePop()
    end
end

function update_material_properties_panel(material)
    update_asset_properties_panel(material, LE3Material)
end

function update_texture_properties_panel(texture)
    update_asset_properties_panel(texture, LE3Texture)
end

function update_static_mesh_properties_panel(static_mesh)
    ImGui.CollapsingHeader("LE3StaticMesh")
end

function update_skeletal_mesh_properties_panel(skeletal_mesh)
    ImGui.CollapsingHeader("LE3SkeletalMesh")
end

function update_animation_properties_panel(skeletal_mesh, animation_track)
    ImGui.CollapsingHeader("LE3Animation")
end


function show_property(property, tbl, obj)
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
    if property.type == "asset" then
        show_asset_property(property, tbl, obj)
    end
end

function show_asset_property(property, tbl, obj)
    if property.asset_type == "animation" then
        if (ImGui.TreeNode(property.name)) then
            tbl[property.name] = ImGui.Combo_Animation(property.name, tbl[property.related_property], tbl[property.name])
            if (ImGui.Button("Play")) then
                LE3SkeletalModel.set_animation_playing(obj, true)
            end
            ImGui.SameLine()
            if (ImGui.Button("Pause")) then 
                LE3SkeletalModel.set_animation_playing(obj, false)
            end
            ImGui.SameLine()
            if (ImGui.Button("Stop")) then 
                LE3SkeletalModel.set_animation_playing(obj, false)
                LE3SkeletalModel.reset_animation(obj)
            end

            ImGui.TreePop()

        end
    end
end