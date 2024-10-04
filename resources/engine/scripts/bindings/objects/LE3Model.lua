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
    LE3StaticModel.set_mesh_name(object, tbl.MeshName)
    LE3StaticModel.set_material_name(object, tbl.MaterialName)
end
LE3StaticModel.save = function (object)
    local tbl = LE3StaticModel.__base.save(object)
    tbl.MeshName = LE3StaticModel.get_mesh_name(object)
    tbl.MaterialName = LE3StaticModel.get_material_name(object)
    return tbl
end
LE3StaticModel.title = "LE3StaticModel"
LE3StaticModel.properties = {
    {name = "MeshName", type = "string"},
    {name = "MaterialName", type = "string"}
}

LE3SkeletalModel.__base = LE3DrawableObject
LE3SkeletalModel.load = function (scene, tbl, res) 
    if (res == nil) then 
        LE3Scene.add_skeletal_model(scene, tbl.Name, tbl.MeshName, tbl.MaterialName)
        res = LE3Scene.get_object(scene, tbl.Name)
    end
    LE3SkeletalModel.__base.load(scene, tbl, res)
    return {ptr = res, name = tbl.Name}
end
LE3SkeletalModel.rebuild = function (object, tbl)
    LE3SkeletalModel.__base.rebuild(object, tbl)
    LE3SkeletalModel.set_mesh_name(object, tbl.MeshName)
    LE3SkeletalModel.set_material_name(object, tbl.MaterialName)
end
LE3SkeletalModel.save = function (object)
    local tbl = LE3SkeletalModel.__base.save(object)
    tbl.MeshName = LE3SkeletalModel.get_mesh_name(object)
    tbl.MaterialName = LE3SkeletalModel.get_material_name(object)
    return tbl
end
LE3SkeletalModel.title = "LE3SkeletalModel"
LE3SkeletalModel.properties = {
    {name = "MeshName", type = "string"},
    {name = "MaterialName", type = "string"}
}