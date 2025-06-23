LE3PhysicsComponent.load = function(component, tbl)
    if tbl.IsTrigger ~= nil then LE3PhysicsComponent.set_is_trigger(component, tbl.IsTrigger) end
    if tbl.IsRigidBody ~= nil then LE3PhysicsComponent.set_is_rigidbody(component, tbl.IsRigidBody) end
    if tbl.Mass ~= nil then LE3PhysicsComponent.set_mass(component, tbl.Mass) end
    if tbl.ColliderOverride ~= nil then LE3PhysicsComponent.set_manual_collider_override(component, tbl.ColliderOverride) end
    if tbl.ColliderType ~= nil then LE3PhysicsComponent.set_manual_collider_type(component, tbl.ColliderType) end
    if tbl.Centroid ~= nil then LE3PhysicsComponent.set_manual_centroid(component, table.unpack(tbl.Centroid)) end
    if tbl.Extent ~= nil then LE3PhysicsComponent.set_manual_extent(component, table.unpack(tbl.Extent)) end
    if tbl.Radius ~= nil then LE3PhysicsComponent.set_manual_radius(component, tbl.Radius) end
end
LE3PhysicsComponent.rebuild = function(component, tbl)
    LE3PhysicsComponent.load(component, tbl)
end
LE3PhysicsComponent.save = function(component)
    local tbl = {}
    tbl.IsTrigger = LE3PhysicsComponent.is_trigger(component)
    tbl.IsRigidBody = LE3PhysicsComponent.is_rigidbody(component)
    tbl.Mass = LE3PhysicsComponent.get_mass(component)
    tbl.ColliderOverride = LE3PhysicsComponent.is_manual_collider_override(component)
    tbl.ColliderType = LE3PhysicsComponent.get_manual_collider_type(component)
    tbl.Centroid = table.pack(LE3PhysicsComponent.get_manual_centroid(component))
    tbl.Extent = table.pack(LE3PhysicsComponent.get_manual_extent(component))
    tbl.Radius = LE3PhysicsComponent.get_manual_radius(component)
    return tbl
end
LE3PhysicsComponent.title = "LE3PhysicsComponent"
LE3PhysicsComponent.properties = {
    {name = "IsTrigger", type = "bool"},
    {name = "IsRigidBody", type = "bool"},
    {name = "Mass", type = "float"},
    {name = "ColliderOverride", type = "bool"},
    {name = "ColliderType", type = "radio", labels = {"Box", "Sphere", "Cone", "Cylinder", "Capsule"}},
    {name = "Centroid", type = "float3"},
    {name = "Extent", type = "float3"},
    {name = "Radius", type = "float"}
}