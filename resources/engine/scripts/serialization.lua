-- Returns recursively a list of the object and all its children (recursively),
-- and a list of scene graph relations
-- The format is {Objects = {object1, object2, ...}, ObjectRelations = {{child1, parent1}, {child2, parent2}, ...}}
---@param scene LE3Scene
---@param object string
function dump_object(scene, object)
    local dump = {Objects = {}, ObjectRelations = {}}
    local obj = LE3Scene.get_object(scene, object)
    local tbl = _G[LE3Object.get_object_type(obj)].save(obj)
    table.insert(dump.Objects, tbl)
    dump.Objects["__testVariable"] = 3.14159265
    dump.Objects["3__anotherTestVariable"] = 3.14159265 / 2

    print(serialize(dump))
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

