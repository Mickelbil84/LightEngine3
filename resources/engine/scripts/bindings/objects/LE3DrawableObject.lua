LE3DrawableObject.__base = LE3Object
LE3DrawableObject.load = function (scene, tbl, res)
    assert(res ~= nil) -- must be called from deriving class
    LE3DrawableObject.__base.load(scene, tbl, res)

    if tbl.DrawPriority ~= nil then LE3DrawableObject.set_draw_priority(res, tbl.DrawPriority) end
    if tbl.Hidden ~= nil then LE3DrawableObject.set_hidden(res, tbl.Hidden) end
    if tbl.CastShadow ~= nil then LE3DrawableObject.set_cast_shadow(res, tbl.CastShadow) end
    if tbl.MaterialName ~= nil then LE3DrawableObject.set_material(res, tbl.MaterialName) end
    return {ptr = res, name = tbl.Name}
end
LE3DrawableObject.rebuild = function (object, tbl)
    LE3DrawableObject.__base.rebuild(object, tbl)
    if tbl.DrawPriority ~= nil then LE3DrawableObject.set_draw_priority(object, tbl.DrawPriority) end
    if tbl.Hidden ~= nil then LE3DrawableObject.set_hidden(object, tbl.Hidden) end
    if tbl.CastShadow ~= nil then LE3DrawableObject.set_cast_shadow(object, tbl.CastShadow) end
    if tbl.MaterialName ~= nil and LE3AssetManager.has_material(tbl.MaterialName) then LE3DrawableObject.set_material(object, tbl.MaterialName) end
end
LE3DrawableObject.save = function (object)
    local tbl = LE3DrawableObject.__base.save(object)
    tbl.DrawPriority = LE3DrawableObject.get_draw_priority(object)
    tbl.Hidden = LE3DrawableObject.get_hidden(object)
    tbl.CastShadow = LE3DrawableObject.get_cast_shadow(object)
    tbl.MaterialName = LE3DrawableObject.get_material(object)
    return tbl
end
LE3DrawableObject.title = "LE3DrawableObject"
LE3DrawableObject.properties = {
    {name = "MaterialName", type = "string"},
    {name = "DrawPriority", type = "int"},
    {name = "Hidden", type = "bool"},
    {name = "CastShadow", type = "bool"},
}