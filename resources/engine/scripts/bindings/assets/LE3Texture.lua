LE3Texture.load = function(texture_table)
    if texture_table.Interpolate == nil then texture_table.Interpolate = true end
    LE3AssetManager.add_texture(texture_table.Name, texture_table.Path, texture_table.Interpolate)
end
LE3Texture.rebuild = function(texture, tbl)
    if tbl.Name ~= nil then 
        LE3Texture.set_name(texture, tbl.Name) 
        texture = tbl.Name -- reassign texture to the new name!
    end
    if tbl.Path ~= nil then LE3Texture.set_texture_path(texture, tbl.Path) end
    if tbl.Interpolate ~= nil then LE3Texture.set_interpolate(texture, tbl.Interpolate) end
end
LE3Texture.reload = function (texture)
    LE3Texture.reload_texture(
        texture, 
        LE3Texture.get_texture_path(texture), 
        LE3Texture.get_interpolate(texture))
end
LE3Texture.save = function(texture)
    local name = LE3Texture.get_name(texture)
    local path = LE3Texture.get_texture_path(texture)
    local interpolate = LE3Texture.get_interpolate(texture)
    return {
        Name = name,
        Path = path,
        Interpolate = interpolate
    }
end
LE3Texture.title = "LE3Texture"
LE3Texture.properties = {
    {name = "Name", type = "string"},
    {name = "Path", type = "string"},
    {name = "Interpolate", type = "boolean"}
}