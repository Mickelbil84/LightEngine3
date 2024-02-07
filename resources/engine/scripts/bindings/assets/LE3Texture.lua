LE3Texture.load = function(texture_table)
    if texture_table.Interpolate == nil then texture_table.Interpolate = true end
    LE3AssetManager.add_texture(texture_table.Name, texture_table.Path, texture_table.Interpolate)
end