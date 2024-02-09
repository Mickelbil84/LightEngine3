LE3ScriptObject.__base = LE3DrawableObject
LE3ScriptObject._refs = {}
LE3ScriptObject.load = function (scene, tbl, res)
    assert(res == nil) -- cannot be inherited
    LE3Scene.add_script_object(scene, tbl.Name, tbl.Classname)
    res = LE3Scene.get_object(scene, tbl.Name)
    LE3ScriptObject.__base.load(scene, tbl, res)
end

function LE3ScriptObject:new()
    obj = {}
    setmetatable(obj, self)
    self.__index = self
    return obj
end

function LE3ScriptObject:init() end
function LE3ScriptObject:update(deltaTime) end
function LE3ScriptObject:draw() end