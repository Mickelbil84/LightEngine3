LE3DrawableObject.__base = LE3Object
LE3DrawableObject.load = function (scene, tbl, res)
    assert(res ~= nil) -- must be called from deriving class
    LE3DrawableObject.__base.load(scene, tbl, res)

    if tbl.DrawPriority ~= nil then LE3DrawableObject.set_draw_priority(res, tbl.DrawPriority) end
    if tbl.Hidden ~= nil then LE3DrawableObject.set_hidden(res, tbl.Hidden) end
    if tbl.CastShadow ~= nil then LE3DrawableObject.set_cast_shadow(res, tbl.CastShadow) end
    return {ptr = res, name = tbl.Name}
end