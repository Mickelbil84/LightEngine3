function duplicate_object(scene, object_type, object_name, new_name)
    local object = LE3Scene.get_object(scene, object_name)
    local tbl = _G[object_type].save(object)
    tbl.Name = new_name
    _G[object_type].load(scene, tbl, nil)
end