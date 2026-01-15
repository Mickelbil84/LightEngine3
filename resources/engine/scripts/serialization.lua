-- Returns recursively a list of the object and all its children (recursively),
-- and a list of scene graph relations
-- The format is {Objects = {object1, object2, ...}, ObjectRelations = {{child1, parent1}, {child2, parent2}, ...}}
---@param scene LE3Scene
---@param object string
---@return table?
function dump_object(scene, object)
    if string.find(object, "__ENGINE__") == 1 then return nil end
    
    local dump = {Objects = {}, ObjectRelations = {}}
    local obj = LE3Scene.get_object(scene, object)
    local parent = LE3Object.get_parent_name(obj)
    if _G[LE3Object.get_object_type(obj)].save ~= nil then
        local tbl = _G[LE3Object.get_object_type(obj)].save(obj)
        table.insert(dump.Objects, tbl)
    end
    if parent ~= nil then table.insert(dump.ObjectRelations, {object, parent}) end

    -- only if we should recurse
    local children = table.pack(LE3Object.get_children_names(obj))
    if children[1] ~= nil then
        for _, child in ipairs(children) do
            local child_dump = dump_object(scene, child)
            if child_dump ~= nil then 
                for _, v in ipairs(child_dump.Objects) do table.insert(dump.Objects, v) end
                for _, v in ipairs(child_dump.ObjectRelations) do table.insert(dump.ObjectRelations, v) end
            end
        end
    end
    return dump
end



------------------------------------------------------------------------
-- Inspired/taken/modified from https://www.lua.org/pil/12.1.html
local function _is_valid_identifier(k)
    if type(k) ~= "string" then return false end
    if k == "." then return false end
    local k_, _ = string.gsub(k, "[_%a][_%w]*", ".")
    return k_ == "."
end

local _serialization_tab = "  "

local function _serialize_table(t, indent)
    local res = ""
    local indent_str = string.rep(_serialization_tab, indent)
    res = res .. "{\n"
    for k, v in pairs(t) do
        res = res .. indent_str .. _serialization_tab
        if _is_valid_identifier(k) then
            res = res .. k
        else
            res = res .. "[" .. serialize(k) .. "]"
        end
        res = res .. " = " .. serialize(v, indent + 1) .. ",\n"
    end
    res = res .. indent_str .. "}"
    return res
end

---@param o any
---@param indent? number
---@return string
function serialize(o, indent)
    if indent == nil then indent = 0 end
    local res = ""
    if type(o) == "nil" then
        return "nil"
    elseif type(o) == "boolean" then
        if o then return "true" else return "false" end
    elseif type(o) == "number" then
        return res .. o
    elseif type(o) == "string" then
        return string.format("%q", o)
    elseif type(o) == "table" then
        res = res .. _serialize_table(o, indent)
    else
        error("cannot serialize a " .. type(o))
    end
    return res
end

-- Helper method for counting how many different table values are there
---@param t1 table
---@param t2 table
---@return number
function count_differences(t1, t2)
    local visited = {}
    local cnt = 0
    for k, _ in pairs(t1) do
        if serialize(t1[k]) ~= serialize(t2[k]) then cnt = cnt + 1 end
        visited[k] = 1
    end
    for k, _ in pairs(t2) do
        if (visited[k] ~= 1) and (serialize(t1[k]) ~= serialize(t2[k])) then cnt = cnt + 1 end
    end
    return cnt
end