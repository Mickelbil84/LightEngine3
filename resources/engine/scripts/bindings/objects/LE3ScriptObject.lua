LE3ScriptObject.__base = LE3DrawableObject
LE3ScriptObject._refs = {}
LE3ScriptObject.load = function (scene, tbl, res)
    -- assert(res == nil) -- cannot be inherited
    if (res == nil) then LE3Scene.add_script_object(scene, tbl.Name, tbl.Classname) end
    res = LE3Scene.get_object(scene, tbl.Name)
    LE3ScriptObject.__base.load(scene, tbl, res)
    
    -- Add relevant pointers to the lua object class
    if _G[tbl.Classname] ~= nil and _G[tbl.Classname]._refs[tbl.Name] ~= nil then
        _G[tbl.Classname]._refs[tbl.Name].object = res
        _G[tbl.Classname]._refs[tbl.Name].transform = LE3Object.get_transform(res)
        _G[tbl.Classname]._refs[tbl.Name].scene = scene
        _G[tbl.Classname]._refs[tbl.Name].name = tbl.Name
        _G[tbl.Classname]._refs[tbl.Name].classname = tbl.Classname
        _G[tbl.Classname]._refs[tbl.Name]:init()
    end
    return {ptr = res, name = tbl.Name}
end
LE3ScriptObject.rebuild = function (object, tbl)
    object = LE3ScriptObject.__base.rebuild(object, tbl)
    LE3ScriptObject.update_internals(object, tbl.Classname, tbl.Name)
    return object
end
LE3ScriptObject.save = function (object)
    local tbl = LE3ScriptObject.__base.save(object)
    tbl.Classname = LE3ScriptObject.get_classname(object)
    return tbl
end
LE3ScriptObject.title = "LE3ScriptObject"
LE3ScriptObject.properties = {
    {name = "Classname", type = "string"},
}

function LE3ScriptObject:new()
    obj = {}
    setmetatable(obj, self)
    self.__index = self
    return obj
end

function LE3ScriptObject:init() end
function LE3ScriptObject:update(deltaTime) end
function LE3ScriptObject:draw() end