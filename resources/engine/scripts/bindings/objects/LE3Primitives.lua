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
LE3Box.save = function (object)
    local tbl = LE3Box.__base.save(object)
    tbl.BoxPosition = {LE3Box.get_box_position(object)}
    tbl.BoxExtent = {LE3Box.get_box_extent(object)}
    return tbl
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
LE3Cylinder.save = function (object)
    local tbl = LE3Cylinder.__base.save(object)
    tbl.Radius = LE3Cylinder.get_radius(object)
    tbl.Height = LE3Cylinder.get_height(object)
    tbl.Resolution = LE3Cylinder.get_resolution(object)
    tbl.WithCaps = LE3Cylinder.get_with_caps(object)
    return tbl
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
LE3Cone.save = function (object)
    local tbl = LE3Cone.__base.save(object)
    tbl.Radius = LE3Cone.get_radius(object)
    tbl.Height = LE3Cone.get_height(object)
    tbl.Resolution = LE3Cone.get_resolution(object)
    tbl.WithCaps = LE3Cone.get_with_caps(object)
    return tbl
end