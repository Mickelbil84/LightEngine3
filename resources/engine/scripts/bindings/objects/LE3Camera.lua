LE3Camera.__base = LE3Object
LE3Camera.load = function (scene, tbl, res)
    assert(res ~= nil)
    LE3Camera.__base.load(scene, tbl, res)

    if tbl.FOV ~= nil then LE3Camera.set_fov(res, tbl.FOV) end
end

LE3FreeCamera.__base = LE3Camera
LE3FreeCamera.load = function (scene, tbl, res)
    if (res == nil) then 
        LE3Scene.add_free_camera(scene, tbl.Name)
        res = LE3Scene.get_object(scene, tbl.Name)
    end
    LE3FreeCamera.__base.load(scene, tbl, res)
    return {ptr = res, name = tbl.Name}
end

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