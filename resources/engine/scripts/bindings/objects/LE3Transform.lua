LE3Transform.load = function(transform, tbl)
    if tbl.Position ~= nil then  LE3Transform.set_position(transform, table.unpack(tbl.Position)) end
    if tbl.Rotation ~= nil then LE3Transform.set_rotation(transform, table.unpack(tbl.Rotation)) end
    if tbl.Scale ~= nil then LE3Transform.set_scale(transform, table.unpack(tbl.Scale)) end
end
LE3Transform.rebuild = function(transform, tbl)
    LE3Transform.load(transform, tbl)
end
LE3Transform.save = function(transform)
    local tbl = {}
    tbl.Position = {LE3Transform.get_position(transform)}
    tbl.Rotation = {LE3Transform.get_rotation(transform)}
    tbl.Scale = {LE3Transform.get_scale(transform)}
    return tbl
end
LE3Transform.title = "LE3Transform"
LE3Transform.properties = {
    {name = "Position", type = "float3"},
    {name = "Rotation", type = "float4"},
    {name = "Scale", type = "float3"}
}