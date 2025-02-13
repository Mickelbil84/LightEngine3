function init_editor_cache()
    print("Hi! :)")
    if LE3EditorCache == nil then
        LE3EditorCache = {}
        LE3EditorCache.MostRecent = ""
        LE3EditorCache.RecentProjects = 3
    end
end