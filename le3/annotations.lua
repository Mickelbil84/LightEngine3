---@meta

---@class LE3Scene
LE3Scene = {}
---@class LE3Shader
LE3Shader = {}
---@class LE3Texture
LE3Texture = {}
---@class LE3Material
LE3Material = {}
---@class LE3StaticMesh
LE3StaticMesh = {}

---@class LE3Transform
LE3Transform = {}
---@class LE3SceneRoot
LE3SceneRoot = {}
---@class LE3StaticModel
LE3StaticModel = {}
---@class LE3Input
LE3Input = {}
---@class LE3DrawableObject
LE3DrawableObject = {}
---@class LE3Camera
LE3Camera = {}
---@class LE3OrbitCamera
LE3OrbitCamera = {}
---@class LE3FreeCamera
LE3FreeCamera = {}


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

---@param scene LE3Scene
---@param name string
---@param filename string
function LE3Scene.add_static_mesh(scene, name, filename) end

---@param scene LE3Scene
---@param name string
---@return LE3StaticMesh
function LE3Scene.get_static_mesh(scene, name) end

---@param scene LE3Scene
---@param name string
function LE3Scene.add_empty_object(scene, name) end

---@param scene LE3Scene
---@param name string
---@param materialName string
function LE3Scene.add_cube(scene, name, materialName) end

---@param scene LE3Scene
---@param name string
---@param meshName string
---@param materialName string
function LE3Scene.add_static_model(scene, name, meshName, materialName) end

---@param scene LE3Scene
---@param name string
function LE3Scene.add_free_camera(scene, name) end

---@param scene LE3Scene
---@param name string
function LE3Scene.add_orbit_camera(scene, name) end

---@param scene LE3Scene
---@param name string
function LE3Scene.set_main_camera(scene, name) end

---@param scene LE3Scene
---@param child string
---@param parent string
function LE3Scene.reparent(scene, child, parent) end

-----------------------------------------------------------------

---@param material LE3Material
---@param r number
---@param g number
---@param b number
---@param a number
function LE3Material.set_diffuse_color(material, r, g, b, a) end

---@param material LE3Material
---@param texture LE3Texture
function LE3Material.set_diffuse_texture(material, texture) end

---@param material LE3Material
---@param r number
---@param g number
---@param b number
---@param a number
function LE3Material.set_specular_color(material, r, g, b, a) end

---@param material LE3Material
---@param val number
function LE3Material.set_specular_intensity(material, val) end

---@param material LE3Material
---@param val number
function LE3Material.set_shininess(material, val) end

---@param material LE3Material
---@param texture LE3Texture
function LE3Material.set_specular_texture(material, texture) end

---@param material LE3Material
---@param texture LE3Texture
function LE3Material.set_normal_texture(material, texture) end

---@param material LE3Material
---@param texture LE3Texture
function LE3Material.set_cubemap(material, texture) end

---@param material LE3Material
---@param val number
function LE3Material.set_reflection_intensity(material, val) end

---@param material LE3Material
---@param x number
---@param y number
function LE3Material.set_tiling(material, x, y) end

