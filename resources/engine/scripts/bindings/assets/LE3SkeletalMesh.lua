LE3SkeletalMesh.load = function(mesh)
    LE3AssetManager.add_skeletal_mesh(mesh.Name, mesh.Path)

    if mesh.Animations ~= nil then 
        for _, anim in ipairs(mesh.Animations) do 
            LE3AssetManager.add_skeletal_animation(anim.Name, anim.Path, mesh.Name)
        end
    end

    if mesh.ColliderType == nil then mesh.ColliderType = "Box" end
    LE3SkeletalMesh.set_collider_type(mesh.Name, mesh.ColliderType)
end
LE3SkeletalMesh.rebuild = function(mesh, tbl)
    if tbl.Name ~= nil then
        LE3SkeletalMesh.set_name(mesh, tbl.Name)
        mesh = tbl.Name
    end
    if tbl.Path ~= nil then LE3SkeletalMesh.set_mesh_path(mesh, tbl.Path) end
    if tbl.ColliderType ~= nil then LE3SkeletalMesh.set_collider_type(mesh, tbl.ColliderType) end
    -- if tbl.Animations ~= nil then 
    --     for _, anim in ipairs(tbl.Animations) do 
    --         LE3AssetManager.add_skeletal_animation(anim.Name, anim.Path, mesh)
    --     end
    -- end
end
LE3SkeletalMesh.reload = function(mesh)
    LE3SkeletalMesh.reload_mesh(
        mesh,
        LE3SkeletalMesh.get_mesh_path(mesh))
end
LE3SkeletalMesh.save = function(mesh)
    local name = LE3SkeletalMesh.get_name(mesh)
    local path = LE3SkeletalMesh.get_mesh_path(mesh)
    local collider_type = LE3SkeletalMesh.get_collider_type(mesh)
    local animations = {}
    for i = 1, LE3SkeletalMesh.get_num_animations(mesh) do
        local animName, animPath = LE3SkeletalMesh.get_animation_at_idx(mesh, i-1)
        animations[#animations+1] = {Name = animName, Path = animPath}
    end
    return {
        Name = name,
        Path = path,
        Animations = animations,
        ColliderType = collider_type
    }
end
LE3SkeletalMesh.title = "LE3SkeletalMesh"
LE3SkeletalMesh.properties = {
    {name = "Name", type = "string"},
    {name = "Path", type = "string"},
    {name = "ColliderType", type = "radio", labels = {"Box", "Sphere", "Cone", "Cylinder", "Capsule", "ConvexHull"}},
}