local function load_LE3Scene_assets(scene, scene_data_table)
    local asset_classes = {
        [1] = {Shaders = LE3Shader, Textures = LE3Texture, StaticMeshes = LE3StaticMesh},
        [2] = {Materials = LE3Material}
    }
    for _, class_dict in pairs(asset_classes) do
        for key, class in pairs(class_dict) do
            for _, tbl in ipairs(scene_data_table[key]) do
                class.load(scene, tbl)
            end
        end
    end
end

function load_LE3Scene(scene, scene_data_table)
    load_LE3Scene_assets(scene, scene_data_table)
end