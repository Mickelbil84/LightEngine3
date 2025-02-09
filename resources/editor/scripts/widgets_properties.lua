_engine_property_change_history = {}
_engine_property_change_history_index = 0x17f -- some arbitrary initial magic number (can be anything else, doesn't matter)

function property_change_execute_ticket(ticket)
    local cmd = _engine_property_change_history[ticket]
    if cmd.Type == "object" then 
        local name = cmd.Old.Name
        if not LE3Scene.has_object_global(name) then name = cmd.New.Name end -- HOTFIX: first rename
        local obj = LE3Scene.get_object_global(name)
        _G[cmd.ttype].rebuild(obj, cmd.New)
    else
        cmd.Type.rebuild(cmd.Ptr, cmd.New)
    end
end

function property_change_undo_ticket(ticket)
    local cmd = _engine_property_change_history[ticket]
    if cmd.Type == "object" then 
        print("UNDO:: " .. cmd.New.Name .. " " .. cmd.Old.Name)
        local obj = LE3Scene.get_object_global(cmd.New.Name)
        _G[cmd.ttype].rebuild(obj, cmd.Old)
    else
        cmd.Type.rebuild(cmd.Ptr, cmd.Old)
    end
end

local function _publish_command(cmd)
    if serialize(cmd.Old) == serialize(cmd.New) then return end

    -- If only a single change was made, then don't append a new command to the stack
    -- (And of course, do this only if there is even a "last ticket")
    local last_ticket_valid = (_engine_property_change_history[_engine_property_change_history_index] ~= nil)
    if last_ticket_valid then
        last_ticket_valid = count_differences(cmd.New, _engine_property_change_history[_engine_property_change_history_index].New) == 1
    end

    if last_ticket_valid then
        local ticket = _engine_property_change_history_index
        cmd.Old = _engine_property_change_history[ticket].Old
        _engine_property_change_history[ticket] = cmd
    else
        _engine_property_change_history_index = _engine_property_change_history_index + 1
        local ticket = _engine_property_change_history_index
        _engine_property_change_history[ticket] = cmd
        LE3EditorComPropertyChange.addNew(ticket)
    end
end

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
        if _G[ttype].parent_blacklist == nil or _G[ttype].parent_blacklist[curr.title] == nil then
            table.insert(hierarchy, 1, curr)
        end
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

    local cmd = {}
    cmd.Old = _G[ttype].save(obj)
        _G[ttype].rebuild(obj, tbl)
    cmd.New = _G[ttype].save(obj)
    cmd.Type = "object"
    cmd.ttype = ttype
    _publish_command(cmd)

end

function update_asset_properties_panel(ptr, type)
    local tbl = type.save(ptr)
    if (ImGui.CollapsingHeader(type.title)) then 
        for _, property in ipairs(type.properties) do
            show_property(property, tbl)
        end
    end

    local cmd = {}
    cmd.Ptr = ptr
    cmd.Old = type.save(ptr)
    type.rebuild(ptr, tbl)
    cmd.New = type.save(ptr)
    cmd.Type = type
    _publish_command(cmd)

    ptr = tbl.Name -- in case of renames, update the "pointer"
    if (type.reload ~= nil) then 
        if (ImGui.Button("Reload")) then
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
    update_asset_properties_panel(static_mesh, LE3StaticMesh)
end

function update_skeletal_mesh_properties_panel(skeletal_mesh)
    update_asset_properties_panel(skeletal_mesh, LE3SkeletalMesh)
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
            tbl[property.name] = ImGui.Combo_Animation(property.name, property.related_property(obj), tbl[property.name])
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