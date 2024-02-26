LE3Light.__base = LE3Object
LE3Light.load = function (scene, tbl, res)
    assert(res ~= nil)
    LE3Light.__base.load(scene, tbl, res)

    if (tbl.Color ~= nil) then LE3Light.set_color(res, table.unpack(tbl.Color)) end
    if (tbl.Intensity ~= nil) then LE3Light.set_intensity(res, tbl.Intensity) end
    return {ptr = res, name = tbl.Name}
end

LE3AmbientLight.__base = LE3Light
LE3AmbientLight.load = function (scene, tbl, res)
    if (res == nil) then 
        LE3Scene.add_ambient_light(scene, tbl.Name)
        res = LE3Scene.get_object(scene, tbl.Name)
    end
    LE3AmbientLight.__base.load(scene, tbl, res)
    return {ptr = res, name = tbl.Name}
end

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