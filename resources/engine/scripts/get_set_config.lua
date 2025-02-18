-- Was written as a hack for the LE3EngineConfig::get<T> method, but that function is written better now.
-- Still, we keep the Lua implementation as a reference, because why not.
---@param key string
function get_config(key)
    local keys = {}
    for k in string.gmatch(key, "[^%.]+") do
        table.insert(keys, k)
    end

    local res = LE3EngineConfig
    print(res)
    for _, k in ipairs(keys) do
        res = res[k]
        print(k, res)
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