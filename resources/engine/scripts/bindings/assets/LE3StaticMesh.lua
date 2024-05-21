LE3StaticMesh.load = function(mesh)
    if mesh.KeepData == nil then mesh.KeepData = false end
    LE3AssetManager.add_static_mesh(mesh.Name, mesh.Path, mesh.KeepData)
end