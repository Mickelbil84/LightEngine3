LE3Object.__base = nil
LE3Object.load = function (scene, tbl, res)
    if res == nil then 
        LE3Scene.add_empty_object(scene, tbl.Name)
        res = LE3Scene.get_object(scene, tbl.Name)
    end
    LE3Transform.load(LE3Object.get_transform(res), tbl)
    return {ptr = res, name = tbl.Name}
end
LE3Object.rebuild = function(object, tbl)
    -- TODO: Rename should be done via another method
    if tbl.Name ~= LE3Object.get_name(object) then
        LE3Scene.rename_object_global(LE3Object.get_name(object), tbl.Name)
        object = LE3Scene.get_object_global(tbl.Name)
    end
    LE3Transform.rebuild(LE3Object.get_transform(object), tbl)
end
LE3Object.save = function (object)
    local tbl = {}
    tbl.Type = LE3Object.get_object_type(object)
    tbl.Name = LE3Object.get_name(object)
    local transformTbl = LE3Transform.save(LE3Object.get_transform(object))
    for k, v in pairs(transformTbl) do tbl[k] = v end
    return tbl
end
LE3Object.title = "LE3Object"
LE3Object.properties = {
    {name = "Name", type = "string"},
    {name = "Transform", type = "transform"}
}