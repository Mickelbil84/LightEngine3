local function load_LE3Scene_shaders(scene, shader_data_table)
    for _, shader in ipairs(shader_data_table) do
        LE3Scene.add_shader(scene, shader.Name, shader.VertexSource, shader.FragmentSource)
    end
end

local function load_LE3Scene_textures(scene, texture_data_table)
    for _, texture in ipairs(texture_data_table) do
        if texture.Interpolate == nil then texture.Interpolate = true end
        LE3Scene.add_texture(scene, texture.Name, texture.Path, texture.Interpolate)
    end
end

function load_LE3Scene(scene, scene_data_table)
    if scene_data_table.Shaders ~= nil then load_LE3Scene_shaders(scene, scene_data_table.Shaders) end
    if scene_data_table.Textures ~= nil then load_LE3Scene_textures(scene, scene_data_table.Textures) end
end