---@return table
local function save_LE3Scene_assets()
    local res = {}

    -- Export shaders
    local shader_names, shader_vss, shader_fss = LE3AssetManager.get_shaders()
    res.Shaders = {}
    for _, name in ipairs(shader_names) do
        table.insert(res.Shaders, LE3Shader.save(name))
    end

    -- Export textures
    local texture_names, texture_paths = LE3AssetManager.get_textures()
    res.Textures = {}
    for _, name in ipairs(texture_names) do
        table.insert(res.Textures, LE3Texture.save(name))
    end

    -- Export meshes
    -- TODO: Export also skeletal animations!
    local mesh_names, mesh_paths, is_skeletal = LE3AssetManager.get_meshes()
    res.StaticMeshes = {}
    res.SkeletalMeshes = {}
    for i, name in ipairs(mesh_names) do
        if is_skeletal[i] then
            table.insert(res.SkeletalMeshes, LE3SkeletalMesh.save(name))
        else
            table.insert(res.StaticMeshes, LE3StaticMesh.save(name))
        end
    end

    -- Export materials
    local material_names = LE3AssetManager.get_materials()
    res.Materials = {}
    for _, name in ipairs(material_names) do
        table.insert(res.Materials, LE3Material.save(name))
    end

    return res
end

---@param scene LE3Scene
---@return table
local function save_LE3Scene_objects(scene)
    return {}
end

---@param scene LE3Scene
---@return table
local function save_LE3Scene_settings(scene)
    return {}
end

---@param scene LE3Scene
---@return table
function save_LE3Scene(scene)
    Scene = {} -- notice that this is a global variable!
    for key, value in pairs(save_LE3Scene_assets()) do Scene[key] = value end
    for key, value in pairs(save_LE3Scene_objects(scene)) do Scene[key] = value end
    Scene.Settings = save_LE3Scene_settings(scene)
    print(serialize(Scene))
    return Scene
end