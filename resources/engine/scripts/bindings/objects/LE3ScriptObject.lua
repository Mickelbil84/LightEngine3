LE3ScriptObject.__base = LE3DrawableObject
LE3ScriptObject._refs = {}
LE3ScriptObject.load = function (scene, tbl, res)
    assert(res == nil) -- cannot be inherited
    LE3Scene.add_script_object(scene, tbl.Name, tbl.Classname)
    res = LE3Scene.get_object(scene, tbl.Name)
    LE3ScriptObject.__base.load(scene, tbl, res)
    
    -- Add relevant pointers to the lua object class
    _G[tbl.Classname]._refs[tbl.Name].object = res
    _G[tbl.Classname]._refs[tbl.Name].transform = LE3Object.get_transform(res)
    _G[tbl.Classname]._refs[tbl.Name].scene = scene
    _G[tbl.Classname]._refs[tbl.Name].name = tbl.Name
    _G[tbl.Classname]._refs[tbl.Name].classname = tbl.Classname
    _G[tbl.Classname]._refs[tbl.Name]:init()
    return {ptr = res, name = tbl.Name}
end
LE3ScriptObject.rebuild = function (object, tbl)
    LE3ScriptObject.__base.rebuild(object, tbl)
end
LE3ScriptObject.save = function (object)
    local tbl = LE3ScriptObject.__base.save(object)
    tbl.Classname = object.classname
    return tbl
end
LE3ScriptObject.title = "LE3ScriptObject"

function LE3ScriptObject:new()
    obj = {}
    setmetatable(obj, self)
    self.__index = self
    return obj
end

function LE3ScriptObject:init() end
function LE3ScriptObject:update(deltaTime) end
function LE3ScriptObject:draw() end