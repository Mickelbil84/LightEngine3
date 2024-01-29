---@meta

---@class LE3Scene
LE3Scene = {}
---@class LE3Shader
LE3Shader = {}
---@class LE3Texture
LE3Texture = {}
---@class LE3Material
LE3Material = {}

-----------------------------------------------------------------

---@param scene LE3Scene
---@param name string
---@param vertex_source string
---@param fragment_source string
function LE3Scene.add_shader(scene, name, vertex_source, fragment_source) end

---@param scene LE3Scene
---@param name string
---@return LE3Shader
function LE3Scene.get_shader(scene, name) end

---@param scene LE3Scene
---@param name string
---@param filename string
---@param interpolate boolean
function LE3Scene.add_texture(scene, name, filename, interpolate) end

---@param scene LE3Scene
---@param name string
---@return LE3Texture
function LE3Scene.get_texture(scene, name) end

---@param scene LE3Scene
---@param name string
---@param shader_name string
function LE3Scene.add_material(scene, name, shader_name) end

---@param scene LE3Scene
---@param name string
---@return LE3Material
function LE3Scene.get_material(scene, name) end

-----------------------------------------------------------------
