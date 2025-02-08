function duplicate_object(scene, object_type, object_name)
    local object = LE3Scene.get_object(scene, object_name)
    local parent = LE3Object.get_parent_name(object)
    local tbl = _G[object_type].save(object)
    tbl.Name = LE3Scene.get_next_available_name(scene, object_name)
    _G[object_type].load(scene, tbl, nil)
    if parent ~= nil then LE3Scene.reparent(scene, tbl.Name, parent) end
    return tbl.Name
end