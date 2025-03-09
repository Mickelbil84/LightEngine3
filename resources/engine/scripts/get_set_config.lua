---@param key string
function get_config(key)
    local keys = {}
    for k in string.gmatch(key, "[^%.]+") do
        table.insert(keys, k)
    end

    local res = _G[keys[1]]
    if res == nil then return nil end

    for i = 2, #keys do
        local k = keys[i]
        res = res[k]
        if res == nil then return nil end
    end

    return res
end

---@param key string
---@param value any
function set_config(key, value)
    local keys = {}
    for k in string.gmatch(key, "[^%.]+") do
        table.insert(keys, k)
    end

    local res = _G[keys[1]]
    for i = 2, #keys - 1 do
        res = res[keys[i]]
    end

    res[keys[#keys]] = value
end