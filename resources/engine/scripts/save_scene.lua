---@return table
local function save_LE3Scene_assets()
    local res = {}

    -- Export shaders
    local shader_names, shader_vss, shader_fss = LE3AssetManager.get_shaders()
    res.Shaders = {}
    for i, _ in ipairs(shader_names) do
        table.insert(res.Shaders, {
            Name = shader_names[i],
            VertexSource = shader_vss[i],
            FragmentSource = shader_fss[i]
        })
    end

    -- Export textures
    local texture_names, texture_paths = LE3AssetManager.get_textures()
    res.Textures = {}
    for i, _ in ipairs(texture_names) do
        table.insert(res.Textures, {
            Name = texture_names[i],
            Path = texture_paths[i]
        })
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
    print(Scene)
    return Scene
end