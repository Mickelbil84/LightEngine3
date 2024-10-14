LE3Sprite.__base = LE3StaticModel
LE3Sprite.load = function (scene, tbl, res)
    if (res == nil) then
        LE3Scene.add_sprite(scene, tbl.Name, tbl.TextureName)
        res = LE3Scene.get_object(scene, tbl.Name)
    end
    LE3Sprite.__base.load(scene, tbl, res)
    return {ptr = res, name = tbl.Name}
end
LE3Sprite.rebuild = function (object, tbl)
    LE3Sprite.__base.rebuild(object, tbl)
end
LE3Sprite.save = function (object)
    local tbl = LE3Sprite.__base.save(object)
    return tbl
end
LE3Sprite.title = "LE3Sprite"