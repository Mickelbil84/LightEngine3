local function load_LE3Scene_assets(scene, scene_data_table)
    local asset_classes = {
        [1] = {Shaders = LE3Shader, Textures = LE3Texture, StaticMeshes = LE3StaticMesh, SkeletalMeshes = LE3SkeletalMesh},
        [2] = {Materials = LE3Material}
    }
    for _, class_dict in pairs(asset_classes) do
        for key, class in pairs(class_dict) do
            for _, tbl in ipairs(scene_data_table[key]) do
                class.load(tbl)
            end
        end
    end
end

local function load_LE3Scene_objects(scene, scene_data_table)
    local object_classes = {
        Empty = LE3Object, ScriptObject = LE3ScriptObject,
        FreeCamera = LE3FreeCamera, OrbitCamera = LE3OrbitCamera,
        AmbientLight = LE3AmbientLight, DirectionalLight = LE3DirectionalLight,
        PointLight = LE3PointLight, SpotLight = LE3SpotLight,
        StaticModel = LE3StaticModel, SkeletalModel = LE3SkeletalModel,
        Box = LE3Box, Cylinder = LE3Cylinder, Cone = LE3Cone
    }
    for _, object in ipairs(scene_data_table.Objects) do
        assert(object.Type ~= nil)
        assert(object.Name ~= nil)
        if object_classes[object.Type] ~= nil then
            object_classes[object.Type].load(scene, object, nil)
        end
    end
    for _, edge in ipairs(scene_data_table.ObjectRelations) do
        local child = edge[1]; local parent = edge[2]
        LE3Scene.reparent(scene, child, parent)
    end
end

function load_LE3Scene_settings(scene, settings)
    if settings.BackgroundColor ~= nil then LE3Scene.set_background_color(scene, table.unpack(settings.BackgroundColor)) end
    if settings.Culling ~= nil then LE3Scene.set_culling(scene, settings.Culling) end
end

function load_LE3Scene(scene, scene_data_table)
    load_LE3Scene_assets(scene, scene_data_table)
    load_LE3Scene_objects(scene, scene_data_table)
    load_LE3Scene_settings(scene, scene_data_table.Settings)
end
