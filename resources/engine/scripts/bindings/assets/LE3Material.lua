LE3Material.load = function(tbl)
    LE3AssetManager.add_material(tbl.Name, tbl.ShaderName)
    local material = LE3AssetManager.get_material(tbl.Name)
    LE3Material.rebuild(material, tbl)
end
LE3Material.rebuild = function(material, tbl)
    if tbl.DiffuseColor ~= nil then LE3Material.set_diffuse_color(material, table.unpack(tbl.DiffuseColor))  end
    if tbl.DiffuseTexture ~= nil then LE3Material.set_diffuse_texture(material, LE3AssetManager.get_texture(tbl.DiffuseTexture)) end

    if tbl.SpecularColor ~= nil then LE3Material.set_specular_color(material, table.unpack(tbl.SpecularColor))  end
    if tbl.SpecularIntensity ~= nil then LE3Material.set_specular_intensity(material, tbl.SpecularIntensity)  end
    if tbl.Shininess ~= nil then LE3Material.set_shininess(material, tbl.Shininess)  end
    if tbl.SpecularTexture ~= nil then LE3Material.set_specular_texture(material, LE3AssetManager.get_texture(tbl.SpecularTexture)) end

    if tbl.NormalTexture ~= nil then LE3Material.set_normal_texture(material, LE3AssetManager.get_texture(tbl.NormalTexture)) end

    if tbl.Cubemap ~= nil then LE3Material.set_cubemap(material, LE3AssetManager.get_texture(tbl.Cubemap)) end
    if tbl.ReflectionIntensity ~= nil then LE3Material.set_reflection_intensity(material, tbl.ReflectionIntensity) end

    if tbl.Tiling ~= nil then LE3Material.set_tiling(material, table.unpack(tbl.Tiling)) end
end
LE3Material.save = function(material) 
    local tbl = {}

    -- tbl.Name = LE3Material.get_name(material)
    -- tbl.ShaderName = LE3Material.get_shader_name(material)

    tbl.DiffuseColor = table.pack(LE3Material.get_diffuse_color(material))
    -- tbl.DiffuseTexture = LE3Material.get_diffuse_texture(material)

    tbl.SpecularColor = table.pack(LE3Material.get_specular_color(material))
    tbl.SpecularIntensity = LE3Material.get_specular_intensity(material)
    tbl.Shininess = LE3Material.get_shininess(material)
    -- tbl.SpecularTexture = LE3Material.get_specular_texture(material)

    -- tbl.NormalTexture = LE3Material.get_normal_texture(material)

    -- tbl.Cubemap = LE3Material.get_cubemap(material)
    tbl.ReflectionIntensity = LE3Material.get_reflection_intensity(material)

    tbl.Tiling = table.pack(LE3Material.get_tiling(material))

    return tbl
end
LE3Material.title = "LE3Material"
LE3Material.properties = {
    -- {name = "Name", type = "string"},
    -- {name = "ShaderName", type = "string"},

    {name = "DiffuseColor", type = "color4"},
    -- {name = "DiffuseTexture", type = "string"},

    {name = "SpecularColor", type = "color"},
    {name = "SpecularIntensity", type = "float"},
    {name = "Shininess", type = "float"},
    -- {name = "SpecularTexture", type = "string"},

    -- {name = "NormalTexture", type = "string"},

    -- {name = "Cubemap", type = "string"},
    {name = "ReflectionIntensity", type = "float"},

    {name = "Tiling", type = "float2"}
}