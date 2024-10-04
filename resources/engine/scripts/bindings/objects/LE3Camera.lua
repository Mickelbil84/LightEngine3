LE3Camera.__base = LE3Object
LE3Camera.load = function (scene, tbl, res)
    assert(res ~= nil)
    LE3Camera.__base.load(scene, tbl, res)

    if tbl.FOV ~= nil then LE3Camera.set_fov(res, tbl.FOV) end
end
LE3Camera.rebuild = function (object, tbl)
    LE3Camera.__base.rebuild(object, tbl)
    if tbl.FOV ~= nil then LE3Camera.set_fov(object, tbl.FOV) end
end
LE3Camera.save = function (object)
    local tbl = LE3Camera.__base.save(object)
    tbl.FOV = LE3Camera.get_fov(object)
    return tbl
end
LE3Camera.title = "LE3Camera"
LE3Camera.properties = {
    {name = "FOV", type = "float"}
}


LE3FreeCamera.__base = LE3Camera
LE3FreeCamera.load = function (scene, tbl, res)
    if (res == nil) then 
        LE3Scene.add_free_camera(scene, tbl.Name)
        res = LE3Scene.get_object(scene, tbl.Name)
    end
    LE3FreeCamera.__base.load(scene, tbl, res)
    return {ptr = res, name = tbl.Name}
end
LE3FreeCamera.rebuild = function (object, tbl)
    LE3FreeCamera.__base.rebuild(object, tbl)
end
LE3FreeCamera.save = function (object)
    local tbl = LE3FreeCamera.__base.save(object)
    return tbl
end
LE3FreeCamera.title = "LE3FreeCamera"


LE3OrbitCamera.__base = LE3Camera
LE3OrbitCamera.load = function (scene, tbl, res)
    if (res == nil) then 
        LE3Scene.add_orbit_camera(scene, tbl.Name)
        res = LE3Scene.get_object(scene, tbl.Name)
    end
    LE3OrbitCamera.__base.load(scene, tbl, res)

    if tbl.Offset ~= nil then LE3OrbitCamera.set_offset(res, tbl.Offset) end
    if tbl.Origin ~= nil then LE3OrbitCamera.set_origin(res, table.unpack(tbl.Origin)) end
    return {ptr = res, name = tbl.Name}
end
LE3OrbitCamera.rebuild = function (object, tbl)
    LE3OrbitCamera.__base.rebuild(object, tbl)
    if tbl.Offset ~= nil then LE3OrbitCamera.set_offset(object, tbl.Offset) end
    if tbl.Origin ~= nil then LE3OrbitCamera.set_origin(object, table.unpack(tbl.Origin)) end
end
LE3OrbitCamera.save = function (object)
    local tbl = LE3OrbitCamera.__base.save(object)
    tbl.Offset = LE3OrbitCamera.get_offset(object)
    tbl.Origin = {LE3OrbitCamera.get_origin(object)}
    return tbl
end
LE3OrbitCamera.title = "LE3OrbitCamera"
LE3OrbitCamera.properties = {
    {name = "Offset", type = "float"},
    {name = "Origin", type = "float3"}
}