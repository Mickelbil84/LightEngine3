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
LE3Box.rebuild = function (object, tbl)
    LE3Box.__base.rebuild(object, tbl)
    -- local x0, y0, z0 = table.unpack(tbl.BoxPosition)
    -- local width, height, depth = table.unpack(tbl.BoxExtent)
    -- LE3Box.set_box_position(object, x0, y0, z0)
    -- LE3Box.set_box_extent(object, width, height, depth)
end
LE3Box.save = function (object)
    local tbl = LE3Box.__base.save(object)
    tbl.BoxPosition = {LE3Box.get_box_position(object)}
    tbl.BoxExtent = {LE3Box.get_box_extent(object)}
    return tbl
end
LE3Box.title = "LE3Box"
LE3Box.parent_blacklist = {LE3StaticModel = 1}

LE3Cylinder.__base = LE3StaticModel
LE3Cylinder.load = function (scene, tbl, res)
    if (res == nil) then
        LE3Scene.add_cylinder(scene, tbl.Name, tbl.MaterialName, 0, 0, 0, tbl.Radius, tbl.Height, tbl.Resolution, tbl.WithCaps)
        res = LE3Scene.get_object(scene, tbl.Name)
    end
    LE3Cylinder.__base.load(scene, tbl, res)
    return {ptr = res, name = tbl.Name}
end
LE3Cylinder.rebuild = function (object, tbl)
    LE3Cylinder.__base.rebuild(object, tbl)
end
LE3Cylinder.save = function (object)
    local tbl = LE3Cylinder.__base.save(object)
    tbl.Radius = LE3Cylinder.get_radius(object)
    tbl.Height = LE3Cylinder.get_height(object)
    tbl.Resolution = LE3Cylinder.get_resolution(object)
    tbl.WithCaps = LE3Cylinder.get_with_caps(object)
    return tbl
end
LE3Cylinder.title = "LE3Cylinder"
LE3Cylinder.parent_blacklist = {LE3StaticModel = 1}

LE3Cone.__base = LE3StaticModel
LE3Cone.load = function (scene, tbl, res)
    if (res == nil) then
        LE3Scene.add_cone(scene, tbl.Name, tbl.MaterialName, 0, 0, 0, tbl.Radius, tbl.Height, tbl.Resolution, tbl.WithCaps)
        res = LE3Scene.get_object(scene, tbl.Name)
    end
    LE3Cone.__base.load(scene, tbl, res)
    return {ptr = res, name = tbl.Name}
end
LE3Cone.rebuild = function (object, tbl)
    LE3Cone.__base.rebuild(object, tbl)
end
LE3Cone.save = function (object)
    local tbl = LE3Cone.__base.save(object)
    tbl.Radius = LE3Cone.get_radius(object)
    tbl.Height = LE3Cone.get_height(object)
    tbl.Resolution = LE3Cone.get_resolution(object)
    tbl.WithCaps = LE3Cone.get_with_caps(object)
    return tbl
end
LE3Cone.title = "LE3Cone"
LE3Cone.parent_blacklist = {LE3StaticModel = 1}

LE3Torus.__base = LE3StaticModel
LE3Torus.load = function (scene, tbl, res)
    if (res == nil) then
        LE3Scene.add_torus(scene, tbl.Name, tbl.MaterialName, 0, 0, 0, tbl.MajorRadius, tbl.MinorRadius, tbl.Resolution)
        res = LE3Scene.get_object(scene, tbl.Name)
    end
    LE3Torus.__base.load(scene, tbl, res)
    return {ptr = res, name = tbl.Name}
end
LE3Torus.rebuild = function (object, tbl)
    LE3Torus.__base.rebuild(object, tbl)
end
LE3Torus.save = function (object)
    local tbl = LE3Torus.__base.save(object)
    tbl.MajorRadius = LE3Torus.get_major_radius(object)
    tbl.MinorRadius = LE3Torus.get_minor_radius(object)
    tbl.Resolution = LE3Torus.get_resolution(object)
    return tbl
end
LE3Torus.title = "LE3Torus"
LE3Torus.parent_blacklist = {LE3StaticModel = 1}