LE3StaticModel.__base = LE3DrawableObject
LE3StaticModel.load = function (scene, tbl, res) 
    if (res == nil) then 
        LE3Scene.add_static_model(scene, tbl.Name, tbl.MeshName, tbl.MaterialName)
        res = LE3Scene.get_object(scene, tbl.Name)
    end
    LE3StaticModel.__base.load(scene, tbl, res)
    return {ptr = res, name = tbl.Name}
end
LE3StaticModel.rebuild = function (object, tbl)
    LE3StaticModel.__base.rebuild(object, tbl)
    if tbl.MeshName ~= nil and LE3AssetManager.has_static_mesh(tbl.MeshName) then LE3StaticModel.set_mesh(object, tbl.MeshName) end
end
LE3StaticModel.save = function (object)
    local tbl = LE3StaticModel.__base.save(object)
    tbl.MeshName = LE3StaticModel.get_mesh(object)
    return tbl
end
LE3StaticModel.title = "LE3StaticModel"
LE3StaticModel.properties = {
    {name = "MeshName", type = "string"}
}

LE3SkeletalModel.__base = LE3DrawableObject
LE3SkeletalModel.load = function (scene, tbl, res) 
    if (res == nil) then 
        LE3Scene.add_skeletal_model(scene, tbl.Name, tbl.MeshName, tbl.MaterialName)
        res = LE3Scene.get_object(scene, tbl.Name)
    end
    LE3SkeletalModel.__base.load(scene, tbl, res)
    LE3SkeletalModel.rebuild(res, tbl)
    return {ptr = res, name = tbl.Name}
end
LE3SkeletalModel.rebuild = function (object, tbl)
    LE3SkeletalModel.__base.rebuild(object, tbl)
    if tbl.MeshName ~= nil and LE3AssetManager.has_skeletal_mesh(tbl.MeshName) then LE3SkeletalModel.set_mesh(object, tbl.MeshName) end

    if tbl.CurrentAnimation == nil then tbl.CurrentAnimation = "[None]" end
    LE3SkeletalModel.set_current_animation(object, tbl.CurrentAnimation)
end
LE3SkeletalModel.save = function (object)
    local tbl = LE3SkeletalModel.__base.save(object)
    tbl.MeshName = LE3SkeletalModel.get_mesh(object)
    tbl.CurrentAnimation = LE3SkeletalModel.get_current_animation(object)
    return tbl
end
LE3SkeletalModel.title = "LE3SkeletalModel"
LE3SkeletalModel.properties = {
    {name = "MeshName", type = "string"},
    {name = "CurrentAnimation", type = "asset", asset_type = "animation", related_property = function(object) return LE3SkeletalModel.get_mesh(object) end} 
}