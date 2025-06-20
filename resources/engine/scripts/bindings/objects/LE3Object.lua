LE3Object.__base = nil
LE3Object.load = function (scene, tbl, res)
    if res == nil then 
        LE3Scene.add_empty_object(scene, tbl.Name)
        res = LE3Scene.get_object(scene, tbl.Name)
    end
    LE3Transform.load(LE3Object.get_transform(res), tbl)
    LE3PhysicsComponent.load(LE3Object.get_physics_component(res), tbl)
    return {ptr = res, name = tbl.Name}
end

---@return LE3Object
LE3Object.rebuild = function(object, tbl)
    -- TODO: Rename should be done via another method
    if tbl.Name ~= LE3Object.get_name(object) and not LE3Scene.has_object_global(tbl.Name) then
        LE3Scene.rename_object_global(LE3Object.get_name(object), tbl.Name)
        object = LE3Scene.get_object_global(tbl.Name)
    end
    LE3Transform.rebuild(LE3Object.get_transform(object), tbl)
    LE3PhysicsComponent.rebuild(LE3Object.get_physics_component(object), tbl)
    return object
end
LE3Object.save = function (object)
    local tbl = {}
    tbl.Type = LE3Object.get_object_type(object)
    tbl.Name = LE3Object.get_name(object)
    local transformTbl = LE3Transform.save(LE3Object.get_transform(object))
    for k, v in pairs(transformTbl) do tbl[k] = v end
    local physicsTbl = LE3PhysicsComponent.save(LE3Object.get_physics_component(object))
    for k, v in pairs(physicsTbl) do tbl[k] = v end
    return tbl
end
LE3Object.title = "LE3Object"
LE3Object.properties = {
    {name = "Name", type = "string"},
    {name = "Transform", type = "subtable", subtable = LE3Transform},
    {name = "RigidBody", type = "subtable", subtable = LE3PhysicsComponent},
}