---@return table
local function save_LE3Scene_assets()
    return {}
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
    return Scene
end