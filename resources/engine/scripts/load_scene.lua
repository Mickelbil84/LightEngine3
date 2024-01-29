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

local function load_LE3Scene_materials(scene, material_data_table)
    for _, material in ipairs(material_data_table) do 
        LE3Scene.add_material(scene, material.Name, material.ShaderName)
        local ptr = LE3Scene.get_material(scene, material.Name)

        if material.DiffuseColor ~= nil then LE3Material.set_diffuse_color(ptr, table.unpack(material.DiffuseColor))  end
        if material.DiffuseTexture ~= nil then LE3Material.set_diffuse_texture(ptr, LE3Scene.get_texture(scene, material.DiffuseTexture)) end

        if material.SpecularColor ~= nil then LE3Material.set_specular_color(ptr, table.unpack(material.SpecularColor))  end
        if material.SpecularIntensity ~= nil then LE3Material.set_specular_intensity(ptr, material.SpecularIntensity)  end
        if material.Shininess ~= nil then LE3Material.set_shininess(ptr, material.Shininess)  end
        if material.SpecularTexture ~= nil then LE3Material.set_specular_texture(ptr, LE3Scene.get_texture(scene, material.SpecularTexture)) end

        if material.NormalTexture ~= nil then LE3Material.set_normal_texture(ptr, LE3Scene.get_texture(scene, material.NormalTexture)) end

        if material.Cubemap ~= nil then LE3Material.set_cubemap(ptr, LE3Scene.get_texture(scene, material.Cubemap)) end
        if material.ReflectionIntensity ~= nil then LE3Material.set_reflection_intensity(ptr, material.ReflectionIntensity) end

        if material.Tiling ~= nil then LE3Material.set_tiling(ptr, table.unpack(material.Tiling)) end

    end
end

local function load_LE3Scene_meshes(scene, mesh_data_table) 
    for _, mesh in ipairs(mesh_data_table) do
        LE3Scene.add_static_mesh(scene, mesh.Name, mesh.Path)
    end
end

function load_LE3Scene(scene, scene_data_table)
    if scene_data_table.Shaders ~= nil then load_LE3Scene_shaders(scene, scene_data_table.Shaders) end
    if scene_data_table.Textures ~= nil then load_LE3Scene_textures(scene, scene_data_table.Textures) end
    if scene_data_table.Materials ~= nil then load_LE3Scene_materials(scene, scene_data_table.Materials) end
    if scene_data_table.Meshes ~= nil then load_LE3Scene_meshes(scene, scene_data_table.Meshes) end
end