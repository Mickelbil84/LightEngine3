_engine_deleted_object_history = {}
_engine_deleted_object_history_index = 0x13e -- some arbitrary initial magic number (can be anything else, doesn't matter)

---@param scene LE3Scene
---@param object string
function delete_object(scene, object)
    _engine_deleted_object_history_index = _engine_deleted_object_history_index + 1
    local dump = dump_object(scene, object)
    local ticket = _engine_deleted_object_history_index
    _engine_deleted_object_history[ticket] = dump
    LE3Scene.delete_object(scene, object)
    return ticket
end

---@param scene LE3Scene
---@param ticket number
function restore_object(scene, ticket)
    load_LE3Scene_objects(scene, _engine_deleted_object_history[ticket])
end