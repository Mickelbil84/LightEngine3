LE3PlayerStart.__base = LE3ScriptObject
LE3PlayerStart.load = function (scene, tbl, res)
    LE3Scene.add_playerstart(scene, tbl.Classname)
    res = LE3Scene.get_object(scene, tbl.Name)
    LE3PlayerStart.__base.load(scene, tbl, res)
    return {ptr = res, name = tbl.Name}
end
LE3PlayerStart.rebuild = function (object, tbl)
    return LE3PlayerStart.__base.rebuild(object, tbl)
end 
LE3PlayerStart.save = function (object)
    return LE3PlayerStart.__base.save(object)
end
LE3PlayerStart.title = "LE3PlayerStart"