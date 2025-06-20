LE3PhysicsComponent.load = function(component, tbl)
    if tbl.IsTrigger ~= nil then LE3PhysicsComponent.set_is_trigger(component, tbl.IsTrigger) end
    if tbl.IsRigidBody ~= nil then LE3PhysicsComponent.set_is_rigidbody(component, tbl.IsRigidBody) end
    if tbl.Mass ~= nil then LE3PhysicsComponent.set_mass(component, tbl.Mass) end
end
LE3PhysicsComponent.rebuild = function(component, tbl)
    LE3PhysicsComponent.load(component, tbl)
end
LE3PhysicsComponent.save = function(component)
    local tbl = {}
    tbl.IsTrigger = LE3PhysicsComponent.is_trigger(component)
    tbl.IsRigidBody = LE3PhysicsComponent.is_rigidbody(component)
    tbl.Mass = LE3PhysicsComponent.get_mass(component)
    return tbl
end
LE3PhysicsComponent.title = "LE3PhysicsComponent"
LE3PhysicsComponent.properties = {
    {name = "IsTrigger", type = "bool"},
    {name = "IsRigidBody", type = "bool"},
    {name = "Mass", type = "float"}
}