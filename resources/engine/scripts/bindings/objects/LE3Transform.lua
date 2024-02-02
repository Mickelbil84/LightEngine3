LE3Transform.load = function(transform, tbl)
    if tbl.Position ~= nil then  LE3Transform.set_position(transform, table.unpack(tbl.Position)) end
    if tbl.Rotation ~= nil then LE3Transform.set_rotation(transform, table.unpack(tbl.Rotation)) end
    if tbl.Scale ~= nil then LE3Transform.set_scale(transform, table.unpack(tbl.Scale)) end
end