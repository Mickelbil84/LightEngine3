LE3Texture.load = function(scene, texture_table)
    if texture_table.Interpolate == nil then texture_table.Interpolate = true end
    LE3Scene.add_texture(scene, texture_table.Name, texture_table.Path, texture_table.Interpolate)
end