function init_editor_cache()
    if LE3EditorCache == nil then
        LE3EditorCache = {}
        LE3EditorCache.MostRecent = ""
        LE3EditorCache.RecentProjects = {}
    end
end

function set_most_recent_project(project)
    LE3EditorCache.MostRecent = project

    -- Also add the project to the recent projects list
    local tmp = {}
    for i = 1, #LE3EditorCache.RecentProjects do
        if LE3EditorCache.RecentProjects[i] ~= project then
            table.insert(tmp, LE3EditorCache.RecentProjects[i])
        end
    end
    table.insert(tmp, project)
end