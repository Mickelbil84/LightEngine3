function duplicate_object(scene, object_type, object_name)
    local object = LE3Scene.get_object(scene, object_name)
    local tbl = _G[object_type].save(object)
    tbl.Name = LE3Scene.get_next_available_name(scene, object_name)
    _G[object_type].load(scene, tbl, nil)
    return tbl.Name
end