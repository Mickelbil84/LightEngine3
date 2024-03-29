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