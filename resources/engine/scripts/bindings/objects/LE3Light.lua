LE3Light.__base = LE3Object
LE3Light.load = function (scene, tbl, res)
    assert(res ~= nil)
    LE3Light.__base.load(scene, tbl, res)

    if (tbl.Color ~= nil) then LE3Light.set_color(res, table.unpack(tbl.Color)) end
    if (tbl.Intensity ~= nil) then LE3Light.set_intensity(res, tbl.Intensity) end
    return {ptr = res, name = tbl.Name}
end
LE3Light.rebuild = function (object, tbl)
    object = LE3Light.__base.rebuild(object, tbl)
    if (tbl.Color ~= nil) then LE3Light.set_color(object, table.unpack(tbl.Color)) end
    if (tbl.Intensity ~= nil) then LE3Light.set_intensity(object, tbl.Intensity) end
    return object
end
LE3Light.save = function (object)
    local tbl = LE3Light.__base.save(object)
    tbl.Color = {LE3Light.get_color(object)}
    tbl.Intensity = LE3Light.get_intensity(object)
    return tbl
end
LE3Light.title = "LE3Light"
LE3Light.properties = {
    {name = "Color", type = "color"},
    {name = "Intensity", type = "float"}
}


LE3AmbientLight.__base = LE3Light
LE3AmbientLight.load = function (scene, tbl, res)
    if (res == nil) then 
        LE3Scene.add_ambient_light(scene, tbl.Name)
        res = LE3Scene.get_object(scene, tbl.Name)
    end
    LE3AmbientLight.__base.load(scene, tbl, res)
    return {ptr = res, name = tbl.Name}
end
LE3AmbientLight.rebuild = function (object, tbl)
    LE3AmbientLight.__base.rebuild(object, tbl)
end
LE3AmbientLight.save = function (object)
    local tbl = LE3AmbientLight.__base.save(object)
    return tbl
end
LE3AmbientLight.title = "LE3AmbientLight"


LE3DirectionalLight.__base = LE3Light
LE3DirectionalLight.load = function (scene, tbl, res)
    if (res == nil) then
        LE3Scene.add_directional_light(scene, tbl.Name)
        res = LE3Scene.get_object(scene, tbl.Name)
    end
    LE3DirectionalLight.__base.load(scene, tbl, res)

    if (tbl.HasShadowMap) then LE3DirectionalLight.add_shadow_map(res, LE3EngineConfig.Rendering.ShadowMapResolution) end
    return {ptr = res, name = tbl.Name}
end
LE3DirectionalLight.rebuild = function (object, tbl)
    LE3DirectionalLight.__base.rebuild(object, tbl)
end
LE3DirectionalLight.save = function (object)
    local tbl = LE3DirectionalLight.__base.save(object)
    tbl.HasShadowMap = LE3DirectionalLight.has_shadow_map(object)
    return tbl
end
LE3DirectionalLight.title = "LE3DirectionalLight"


LE3PointLight.__base = LE3Light
LE3PointLight.load = function (scene, tbl, res)
    if (res == nil) then 
        LE3Scene.add_point_light(scene, tbl.Name)
        res = LE3Scene.get_object(scene, tbl.Name)
    end
    LE3PointLight.__base.load(scene, tbl, res)

    if (tbl.AttnConst ~= nil) then LE3PointLight.set_attn_const(res, tbl.AttnConst) end
    if (tbl.AttnLinear ~= nil) then LE3PointLight.set_attn_linear(res, tbl.AttnLinear) end
    if (tbl.AttnExp ~= nil) then LE3PointLight.set_attn_exp(res, tbl.AttnExp) end
    return {ptr = res, name = tbl.Name}
end
LE3PointLight.rebuild = function (object, tbl)
    LE3PointLight.__base.rebuild(object, tbl)
    if (tbl.AttnConst ~= nil) then LE3PointLight.set_attn_const(object, tbl.AttnConst) end
    if (tbl.AttnLinear ~= nil) then LE3PointLight.set_attn_linear(object, tbl.AttnLinear) end
    if (tbl.AttnExp ~= nil) then LE3PointLight.set_attn_exp(object, tbl.AttnExp) end
end
LE3PointLight.save = function (object)
    local tbl = LE3PointLight.__base.save(object)
    tbl.AttnConst = LE3PointLight.get_attn_const(object)
    tbl.AttnLinear = LE3PointLight.get_attn_linear(object)
    tbl.AttnExp = LE3PointLight.get_attn_exp(object)
    return tbl
end
LE3PointLight.title = "LE3PointLight"
LE3PointLight.properties = {
    {name = "AttnConst", type = "float"},
    {name = "AttnLinear", type = "float"},
    {name = "AttnExp", type = "float"}
}


LE3SpotLight.__base = LE3Light
LE3SpotLight.load = function (scene, tbl, res)
    if (res == nil) then 
        LE3Scene.add_spot_light(scene, tbl.Name)
        res = LE3Scene.get_object(scene, tbl.Name)
    end
    LE3SpotLight.__base.load(scene, tbl, res)

    if (tbl.Cutoff ~= nil) then LE3SpotLight.set_cutoff(res, tbl.Cutoff) end
    if (tbl.OuterCutoff ~= nil) then LE3SpotLight.set_outer_cutoff(res, tbl.OuterCutoff) end

    if (tbl.HasShadowMap) then LE3SpotLight.add_shadow_map(res, LE3EngineConfig.Rendering.ShadowMapResolution) end
    return {ptr = res, name = tbl.Name}
end
LE3SpotLight.rebuild = function (object, tbl)
    LE3SpotLight.__base.rebuild(object, tbl)
    if (tbl.Cutoff ~= nil) then LE3SpotLight.set_cutoff(object, tbl.Cutoff) end
    if (tbl.OuterCutoff ~= nil) then LE3SpotLight.set_outer_cutoff(object, tbl.OuterCutoff) end
end
LE3SpotLight.save = function (object)
    local tbl = LE3SpotLight.__base.save(object)
    tbl.Cutoff = LE3SpotLight.get_cutoff(object)
    tbl.OuterCutoff = LE3SpotLight.get_outer_cutoff(object)
    tbl.HasShadowMap = LE3SpotLight.has_shadow_map(object)
    return tbl
end
LE3SpotLight.title = "LE3SpotLight"
LE3SpotLight.properties = {
    {name = "Cutoff", type = "float"},
    {name = "OuterCutoff", type = "float"}
}