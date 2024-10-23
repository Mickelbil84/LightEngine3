LE3StaticMesh.load = function(mesh)
    if mesh.KeepData == nil then mesh.KeepData = false end
    LE3AssetManager.add_static_mesh(mesh.Name, mesh.Path, mesh.KeepData)
end
LE3StaticMesh.rebuild = function(mesh, tbl)
    if tbl.Name ~= nil then
        LE3StaticMesh.set_name(mesh, tbl.Name)
        mesh = tbl.Name
    end
    if tbl.Path ~= nil then LE3StaticMesh.set_mesh_path(mesh, tbl.Path) end
    --if tbl.KeepData ~= nil then LE3StaticMesh.set_keep_data(mesh, tbl.KeepData) end
end
LE3StaticMesh.reload = function(mesh)
    LE3StaticMesh.reload_mesh(
        mesh,
        LE3StaticMesh.get_mesh_path(mesh), false)
end
LE3StaticMesh.save = function(mesh)
    local name = LE3StaticMesh.get_name(mesh)
    local path = LE3StaticMesh.get_mesh_path(mesh)
    --local keep_data = LE3StaticMesh.get_keep_data(mesh)
    return {
        Name = name,
        Path = path,
        KeepData = false
    }
end
LE3StaticMesh.title = "LE3StaticMesh"
LE3StaticMesh.properties = {
    {name = "Name", type = "string"},
    {name = "Path", type = "string"},
    --{name = "KeepData", type = "boolean"}
}