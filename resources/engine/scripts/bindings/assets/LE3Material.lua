LE3Material.load = function(material)
    LE3AssetManager.add_material(material.Name, material.ShaderName)
    local ptr = LE3AssetManager.get_material(material.Name)

    if material.DiffuseColor ~= nil then LE3Material.set_diffuse_color(ptr, table.unpack(material.DiffuseColor))  end
    if material.DiffuseTexture ~= nil then LE3Material.set_diffuse_texture(ptr, LE3AssetManager.get_texture(material.DiffuseTexture)) end

    if material.SpecularColor ~= nil then LE3Material.set_specular_color(ptr, table.unpack(material.SpecularColor))  end
    if material.SpecularIntensity ~= nil then LE3Material.set_specular_intensity(ptr, material.SpecularIntensity)  end
    if material.Shininess ~= nil then LE3Material.set_shininess(ptr, material.Shininess)  end
    if material.SpecularTexture ~= nil then LE3Material.set_specular_texture(ptr, LE3AssetManager.get_texture( material.SpecularTexture)) end

    if material.NormalTexture ~= nil then LE3Material.set_normal_texture(ptr, LE3AssetManager.get_texture(material.NormalTexture)) end

    if material.Cubemap ~= nil then LE3Material.set_cubemap(ptr, LE3AssetManager.get_texture(material.Cubemap)) end
    if material.ReflectionIntensity ~= nil then LE3Material.set_reflection_intensity(ptr, material.ReflectionIntensity) end

    if material.Tiling ~= nil then LE3Material.set_tiling(ptr, table.unpack(material.Tiling)) end

end