LE3SkeletalMesh.load = function(mesh)
    LE3AssetManager.add_skeletal_mesh(mesh.Name, mesh.Path)

    if mesh.Animations ~= nil then 
        for _, anim in ipairs(mesh.Animations) do 
            LE3AssetManager.add_skeletal_animation(anim.Name, anim.Path, mesh.Name)
        end
    end
end