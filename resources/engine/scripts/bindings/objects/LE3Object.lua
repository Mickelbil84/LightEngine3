LE3Object.load = function (scene, tbl, res)
    if res == nil then 
        LE3Scene.add_empty_object(scene, tbl.Name)
        res = LE3Scene.get_object(scene, tbl.Name)
    end
    LE3Transform.load(LE3Object.get_transform(res), tbl)
    return {ptr = res, name = tbl.Name}
end