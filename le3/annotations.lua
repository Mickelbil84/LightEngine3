---@meta

---@class LE3DrawableObject
LE3DrawableObject = {}
---@class LE3SpotLight
LE3SpotLight = {}
---@class LE3SceneRoot
LE3SceneRoot = {}
---@class LE3EngineConfig
LE3EngineConfig = {}
---@class LE3AssetManager
LE3AssetManager = {}
---@class LE3Texture
LE3Texture = {}
---@class LE3Input
LE3Input = {}
---@class LE3FreeCamera
LE3FreeCamera = {}
---@class LE3Transform
LE3Transform = {}
---@class LE3Material
LE3Material = {}
---@class LE3StaticModel
LE3StaticModel = {}
---@class LE3Light
LE3Light = {}
---@class LE3AmbientLight
LE3AmbientLight = {}
---@class LE3DirectionalLight
LE3DirectionalLight = {}
---@class LE3StaticMesh
LE3StaticMesh = {}
---@class LE3Shader
LE3Shader = {}
---@class LE3PointLight
LE3PointLight = {}
---@class LE3Object
LE3Object = {}
---@class LE3Scene
LE3Scene = {}
---@class LE3Box
LE3Box = {}
---@class LE3Camera
LE3Camera = {}
---@class LE3OrbitCamera
LE3OrbitCamera = {}

--------------------------------------

---@param obj LE3Object
---@return LE3Transform
function LE3Object.get_transform(obj) end

---@param attn_exp number
function LE3PointLight.set_attn_exp(attn_exp) end

---@param material LE3Material
---@return LE3Texture
function LE3Material.get_specular_texture(material) end

---@param scene LE3Scene
---@param name string
function LE3Scene.add_empty_object(scene, name) end

---@param material LE3Material
---@return number
function LE3Material.get_reflection_intensity(material) end

---@return number
---@return number
---@return number
---@return number
function LE3Transform.get_rotation() end

---@param material LE3Material
---@return LE3Texture
function LE3Material.get_normal_texture(material) end

---@return number
function LE3PointLight.get_attn_const() end

---@param scene LE3Scene
---@param name string
function LE3Scene.add_free_camera(scene, name) end

---@param material LE3Material
---@param val number
function LE3Material.set_specular_intensity(material, val) end

---@param material LE3Material
---@param color_x number
---@param color_y number
---@param color_z number
---@param color_w number
function LE3Material.set_diffuse_color(material, color_x, color_y, color_z, color_w) end

---@param name string
---@return LE3Texture
function LE3AssetManager.get_texture(name) end

---@param background_color_x number
---@param background_color_y number
---@param background_color_z number
function LE3Scene.set_background_color(background_color_x, background_color_y, background_color_z) end

---@return number
---@return number
---@return number
function LE3OrbitCamera.get_origin() end

---@param material LE3Material
---@param texture LE3Texture
function LE3Material.set_normal_texture(material, texture) end

---@param material LE3Material
---@return number
---@return number
function LE3Material.get_tiling(material) end

---@return number
function LE3PointLight.get_attn_linear() end

---@return number
---@return number
---@return number
function LE3Light.get_color() end

---@param material LE3Material
---@param val number
function LE3Material.set_shininess(material, val) end

---@param position_x number
---@param position_y number
---@param position_z number
function LE3Transform.set_position(position_x, position_y, position_z) end

---@param draw_priority number
function LE3DrawableObject.set_draw_priority(draw_priority) end

---@param offset number
function LE3OrbitCamera.set_offset(offset) end

---@param material LE3Material
---@return LE3Texture
function LE3Material.get_cubemap(material) end

---@return number
function LE3OrbitCamera.get_offset() end

---@param self LE3DrawableObject
---@return LE3Material
function LE3DrawableObject.get_material(self) end

---@param scene LE3Scene
---@param camera string
function LE3Scene.set_main_camera(scene, camera) end

---@param material LE3Material
---@param texture LE3Texture
function LE3Material.set_cubemap(material, texture) end

---@param color_x number
---@param color_y number
---@param color_z number
function LE3Light.set_color(color_x, color_y, color_z) end

---@param fov number
function LE3Camera.set_fov(fov) end

---@param origin_x number
---@param origin_y number
---@param origin_z number
function LE3OrbitCamera.set_origin(origin_x, origin_y, origin_z) end

---@return number
function LE3SpotLight.get_outer_cutoff() end

---@return number
---@return number
---@return number
function LE3Transform.get_position() end

---@param scene LE3Scene
---@param name string
---@param materialName string
---@param position_x number
---@param position_y number
---@param position_z number
---@param extentX number
---@param extentY number
---@param extentZ number
function LE3Scene.add_box(scene, name, materialName, position_x, position_y, position_z, extentX, extentY, extentZ) end

---@param scene LE3Scene
---@param name string
function LE3Scene.add_directional_light(scene, name) end

---@param tmp number
---@param color_x number
---@param color_y number
---@param color_z number
---@param color_w number
function LE3EngineConfig.set_imgui_style(tmp, color_x, color_y, color_z, color_w) end

---@return boolean
function LE3DrawableObject.get_hidden() end

---@param name string
---@return LE3Material
function LE3AssetManager.get_material(name) end

---@param rotation_w number
---@param rotation_x number
---@param rotation_y number
---@param rotation_z number
function LE3Transform.set_rotation(rotation_w, rotation_x, rotation_y, rotation_z) end

---@param attn_linear number
function LE3PointLight.set_attn_linear(attn_linear) end

---@param material LE3Material
---@return number
function LE3Material.get_specular_intensity(material) end

---@return number
function LE3SpotLight.get_cutoff() end

---@param material LE3Material
---@return number
---@return number
---@return number
---@return number
function LE3Material.get_diffuse_color(material) end

---@return number
---@return number
---@return number
function LE3Scene.get_background_color() end

---@param material LE3Material
---@param texture LE3Texture
function LE3Material.set_diffuse_texture(material, texture) end

---@param hidden boolean
function LE3DrawableObject.set_hidden(hidden) end

---@param scene LE3Scene
---@param name string
function LE3Scene.add_orbit_camera(scene, name) end

---@return number
function LE3PointLight.get_attn_exp() end

---@param outer_cutoff number
function LE3SpotLight.set_outer_cutoff(outer_cutoff) end

---@param material LE3Material
---@param val number
function LE3Material.set_reflection_intensity(material, val) end

---@param scale_x number
---@param scale_y number
---@param scale_z number
function LE3Transform.set_scale(scale_x, scale_y, scale_z) end

---@param material LE3Material
---@return number
function LE3Material.get_shininess(material) end

---@param name string
---@param filename string
---@param interpolate boolean
function LE3AssetManager.add_texture(name, filename, interpolate) end

---@param scene LE3Scene
---@param name string
---@param meshName string
---@param materialName string
function LE3Scene.add_static_model(scene, name, meshName, materialName) end

---@param scene LE3Scene
---@param name string
function LE3Scene.add_ambient_light(scene, name) end

---@param scene LE3Scene
---@param name string
---@return LE3Object
function LE3Scene.get_object(scene, name) end

---@return number
---@return number
---@return number
function LE3Transform.get_scale() end

---@param scene LE3Scene
---@param name string
function LE3Scene.add_point_light(scene, name) end

---@param intensity number
function LE3Light.set_intensity(intensity) end

---@param material LE3Material
---@param texture LE3Texture
function LE3Material.set_specular_texture(material, texture) end

---@param name string
---@return LE3StaticMesh
function LE3AssetManager.get_static_mesh(name) end

---@param attn_const number
function LE3PointLight.set_attn_const(attn_const) end

---@param name string
---@return LE3Shader
function LE3AssetManager.get_shader(name) end

---@param cutoff number
function LE3SpotLight.set_cutoff(cutoff) end

---@param material LE3Material
---@param x number
---@param y number
function LE3Material.set_tiling(material, x, y) end

---@param name string
---@param vertexSource string
---@param fragmentSource string
function LE3AssetManager.add_shader(name, vertexSource, fragmentSource) end

---@param name string
---@param filename string
function LE3AssetManager.add_static_mesh(name, filename) end

---@param scene LE3Scene
---@param name string
function LE3Scene.add_spot_light(scene, name) end

---@param material LE3Material
---@return number
---@return number
---@return number
function LE3Material.get_specular_color(material) end

---@return number
function LE3DrawableObject.get_draw_priority() end

---@return number
function LE3Camera.get_fov() end

---@return number
function LE3Light.get_intensity() end

---@param material LE3Material
---@return LE3Texture
function LE3Material.get_diffuse_texture(material) end

---@param name string
---@param shaderName string
function LE3AssetManager.add_material(name, shaderName) end

---@param scene LE3Scene
---@param child string
---@param parent string
function LE3Scene.reparent(scene, child, parent) end

---@param material LE3Material
---@param color_x number
---@param color_y number
---@param color_z number
function LE3Material.set_specular_color(material, color_x, color_y, color_z) end

