LE3Box.__base = LE3StaticModel
LE3Box.load = function (scene, tbl, res)
    if (res == nil) then
        local x0, y0, z0 = table.unpack(tbl.BoxPosition)
        local width, height, depth = table.unpack(tbl.BoxExtent)
        LE3Scene.add_box(scene, tbl.Name, tbl.MaterialName, x0, y0, z0, width, height, depth)
        res = LE3Scene.get_object(scene, tbl.Name)
    end
    LE3Box.__base.load(scene, tbl, res)
    return {ptr = res, name = tbl.Name}
end

LE3Cylinder.__base = LE3StaticModel
LE3Cylinder.load = function (scene, tbl, res)
    if (res == nil) then
        LE3Scene.add_cylinder(scene, tbl.Name, tbl.MaterialName, 0, 0, 0, tbl.Radius, tbl.Height, tbl.Resolution, tbl.WithCaps)
        res = LE3Scene.get_object(scene, tbl.Name)
    end
    LE3Cylinder.__base.load(scene, tbl, res)
    return {ptr = res, name = tbl.Name}
end

LE3Cone.__base = LE3StaticModel
LE3Cone.load = function (scene, tbl, res)
    if (res == nil) then
        LE3Scene.add_cone(scene, tbl.Name, tbl.MaterialName, 0, 0, 0, tbl.Radius, tbl.Height, tbl.Resolution, tbl.WithCaps)
        res = LE3Scene.get_object(scene, tbl.Name)
    end
    LE3Cone.__base.load(scene, tbl, res)
    return {ptr = res, name = tbl.Name}
end