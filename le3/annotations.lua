---@meta

---@class ImGui
ImGui = {}
---@class LE3AmbientLight
LE3AmbientLight = {}
---@class LE3AssetManager
LE3AssetManager = {}
---@class LE3Box
LE3Box = {}
---@class LE3Camera
LE3Camera = {}
---@class LE3Cone
LE3Cone = {}
---@class LE3Cylinder
LE3Cylinder = {}
---@class LE3DirectionalLight
LE3DirectionalLight = {}
---@class LE3DrawableObject
LE3DrawableObject = {}
---@class LE3EngineConfig
LE3EngineConfig = {}
---@class LE3FreeCamera
LE3FreeCamera = {}
---@class LE3Input
LE3Input = {}
---@class LE3Light
LE3Light = {}
---@class LE3Material
LE3Material = {}
---@class LE3Object
LE3Object = {}
---@class LE3OrbitCamera
LE3OrbitCamera = {}
---@class LE3PointCloud
LE3PointCloud = {}
---@class LE3PointLight
LE3PointLight = {}
---@class LE3Scene
LE3Scene = {}
---@class LE3SceneRoot
LE3SceneRoot = {}
---@class LE3ScriptObject
LE3ScriptObject = {}
---@class LE3Shader
LE3Shader = {}
---@class LE3SkeletalMesh
LE3SkeletalMesh = {}
---@class LE3SkeletalModel
LE3SkeletalModel = {}
---@class LE3SpotLight
LE3SpotLight = {}
---@class LE3Sprite
LE3Sprite = {}
---@class LE3StaticMesh
LE3StaticMesh = {}
---@class LE3StaticModel
LE3StaticModel = {}
---@class LE3Texture
LE3Texture = {}
---@class LE3Torus
LE3Torus = {}
---@class LE3Transform
LE3Transform = {}
---@class LE3VisualDebug
LE3VisualDebug = {}

--------------------------------------

---@param label string
---@return boolean
function ImGui.Button(label) end

---@param label string
---@param prev boolean
---@return boolean
function ImGui.Checkbox(label, prev) end

---@param label string
---@return boolean
function ImGui.CollapsingHeader(label) end

---@param label string
---@param prev_x number
---@param prev_y number
---@param prev_z number
---@return number
---@return number
---@return number
function ImGui.ColorEdit3(label, prev_x, prev_y, prev_z) end

---@param label string
---@param prev_x number
---@param prev_y number
---@param prev_z number
---@param prev_w number
---@return number
---@return number
---@return number
---@return number
function ImGui.ColorEdit4(label, prev_x, prev_y, prev_z, prev_w) end

---@param label string
---@param meshName string
---@param prev string
---@return string
function ImGui.Combo_Animation(label, meshName, prev) end

---@param label string
---@param prev number
---@return number
function ImGui.InputFloat(label, prev) end

---@param label string
---@param prev_x number
---@param prev_y number
---@return number
---@return number
function ImGui.InputFloat2(label, prev_x, prev_y) end

---@param label string
---@param prev_x number
---@param prev_y number
---@param prev_z number
---@return number
---@return number
---@return number
function ImGui.InputFloat3(label, prev_x, prev_y, prev_z) end

---@param label string
---@param prev_w number
---@param prev_x number
---@param prev_y number
---@param prev_z number
---@return number
---@return number
---@return number
---@return number
function ImGui.InputFloat4(label, prev_w, prev_x, prev_y, prev_z) end

---@param label string
---@param prev number
---@return number
function ImGui.InputInt(label, prev) end

---@param label string
---@param prev string
---@return string
function ImGui.InputText(label, prev) end

function ImGui.SameLine() end

---@param text string
function ImGui.Text(text) end

---@param color_x number
---@param color_y number
---@param color_z number
---@param color_w number
---@param text string
function ImGui.TextColored(color_x, color_y, color_z, color_w, text) end

---@param text string
function ImGui.TextWrapped(text) end

---@param label string
---@return boolean
function ImGui.TreeNode(label) end

function ImGui.TreePop() end

---@param name string
---@param shaderName string
function LE3AssetManager.add_material(name, shaderName) end

---@param name string
---@param vertexSource string
---@param fragmentSource string
function LE3AssetManager.add_shader(name, vertexSource, fragmentSource) end

---@param name string
---@param animationPath string
---@param meshName string
function LE3AssetManager.add_skeletal_animation(name, animationPath, meshName) end

---@param name string
---@param filename string
function LE3AssetManager.add_skeletal_mesh(name, filename) end

---@param name string
---@param filename string
---@param keepData boolean
function LE3AssetManager.add_static_mesh(name, filename, keepData) end

---@param name string
---@param filename string
---@param interpolate boolean
function LE3AssetManager.add_texture(name, filename, interpolate) end

---@param shaderName string
---@return string
---@return string
---@return string
---@return string
function LE3AssetManager.get_shader_paths(shaderName) end

---@param name string
---@return boolean
function LE3AssetManager.has_texture(name) end

---@param self LE3Box
---@return number
---@return number
---@return number
function LE3Box.get_box_extent(self) end

---@param self LE3Box
---@return number
---@return number
---@return number
function LE3Box.get_box_position(self) end

---@param self LE3Camera
---@return number
function LE3Camera.get_fov(self) end

---@param self LE3Camera
---@param fov number
function LE3Camera.set_fov(self, fov) end

---@param self LE3Cone
---@return number
function LE3Cone.get_height(self) end

---@param self LE3Cone
---@return number
function LE3Cone.get_radius(self) end

---@param self LE3Cone
---@return number
function LE3Cone.get_resolution(self) end

---@param self LE3Cone
---@return boolean
function LE3Cone.get_with_caps(self) end

---@param self LE3Cone
---@return number
function LE3Cone.get_x0(self) end

---@param self LE3Cone
---@return number
function LE3Cone.get_y0(self) end

---@param self LE3Cone
---@return number
function LE3Cone.get_z0(self) end

---@param self LE3Cylinder
---@return number
function LE3Cylinder.get_height(self) end

---@param self LE3Cylinder
---@return number
function LE3Cylinder.get_radius(self) end

---@param self LE3Cylinder
---@return number
function LE3Cylinder.get_resolution(self) end

---@param self LE3Cylinder
---@return boolean
function LE3Cylinder.get_with_caps(self) end

---@param self LE3Cylinder
---@return number
function LE3Cylinder.get_x0(self) end

---@param self LE3Cylinder
---@return number
function LE3Cylinder.get_y0(self) end

---@param self LE3Cylinder
---@return number
function LE3Cylinder.get_z0(self) end

---@param light LE3DirectionalLight
---@param resolution number
function LE3DirectionalLight.add_shadow_map(light, resolution) end

---@param self LE3DirectionalLight
---@return number
---@return number
---@return number
function LE3DirectionalLight.get_direction(self) end

---@param self LE3DirectionalLight
---@return boolean
function LE3DirectionalLight.has_shadow_map(self) end

---@param self LE3DrawableObject
---@return boolean
function LE3DrawableObject.get_cast_shadow(self) end

---@param self LE3DrawableObject
---@return number
function LE3DrawableObject.get_draw_priority(self) end

---@param self LE3DrawableObject
---@return boolean
function LE3DrawableObject.get_hidden(self) end

---@param self LE3DrawableObject
---@return LE3Material
function LE3DrawableObject.get_material(self) end

---@param self LE3DrawableObject
---@param cast_shadow boolean
function LE3DrawableObject.set_cast_shadow(self, cast_shadow) end

---@param self LE3DrawableObject
---@param draw_priority number
function LE3DrawableObject.set_draw_priority(self, draw_priority) end

---@param self LE3DrawableObject
---@param hidden boolean
function LE3DrawableObject.set_hidden(self, hidden) end

---@param tmp number
---@param color_x number
---@param color_y number
---@param color_z number
---@param color_w number
function LE3EngineConfig.set_imgui_style(tmp, color_x, color_y, color_z, color_w) end

---@param self LE3Light
---@return number
---@return number
---@return number
function LE3Light.get_color(self) end

---@param self LE3Light
---@return number
function LE3Light.get_intensity(self) end

---@param self LE3Light
---@param color_x number
---@param color_y number
---@param color_z number
function LE3Light.set_color(self, color_x, color_y, color_z) end

---@param self LE3Light
---@param intensity number
function LE3Light.set_intensity(self, intensity) end

---@param materialName string
function LE3Material.get_cubemap(materialName) end

---@param materialName string
---@return number
---@return number
---@return number
---@return number
function LE3Material.get_diffuse_color(materialName) end

---@param materialName string
function LE3Material.get_diffuse_texture(materialName) end

---@param materialName string
---@return string
function LE3Material.get_name(materialName) end

---@param materialName string
function LE3Material.get_normal_texture(materialName) end

---@param materialName string
---@return number
function LE3Material.get_reflection_intensity(materialName) end

---@param materialName string
function LE3Material.get_shader(materialName) end

---@param materialName string
---@return number
function LE3Material.get_shininess(materialName) end

---@param materialName string
---@return number
---@return number
---@return number
function LE3Material.get_specular_color(materialName) end

---@param materialName string
---@return number
function LE3Material.get_specular_intensity(materialName) end

---@param materialName string
function LE3Material.get_specular_texture(materialName) end

---@param materialName string
---@return number
---@return number
function LE3Material.get_tiling(materialName) end

---@param materialName string
function LE3Material.null_cubemap(materialName) end

---@param materialName string
function LE3Material.null_diffuse_texture(materialName) end

---@param materialName string
function LE3Material.null_normal_texture(materialName) end

---@param materialName string
function LE3Material.null_specular_texture(materialName) end

---@param materialName string
---@param textureName string
function LE3Material.set_cubemap(materialName, textureName) end

---@param materialName string
---@param color_x number
---@param color_y number
---@param color_z number
---@param color_w number
function LE3Material.set_diffuse_color(materialName, color_x, color_y, color_z, color_w) end

---@param materialName string
---@param textureName string
function LE3Material.set_diffuse_texture(materialName, textureName) end

---@param materialName string
---@param textureName string
function LE3Material.set_normal_texture(materialName, textureName) end

---@param materialName string
---@param val number
function LE3Material.set_reflection_intensity(materialName, val) end

---@param materialName string
---@param shaderName string
function LE3Material.set_shader(materialName, shaderName) end

---@param materialName string
---@param val number
function LE3Material.set_shininess(materialName, val) end

---@param materialName string
---@param color_x number
---@param color_y number
---@param color_z number
function LE3Material.set_specular_color(materialName, color_x, color_y, color_z) end

---@param materialName string
---@param val number
function LE3Material.set_specular_intensity(materialName, val) end

---@param materialName string
---@param textureName string
function LE3Material.set_specular_texture(materialName, textureName) end

---@param materialName string
---@param x number
---@param y number
function LE3Material.set_tiling(materialName, x, y) end

---@param obj LE3Object
---@return string
function LE3Object.get_name(obj) end

---@param obj LE3Object
---@return string
function LE3Object.get_object_type(obj) end

---@param obj LE3Object
---@return LE3Transform
function LE3Object.get_transform(obj) end

---@param self LE3OrbitCamera
---@return number
function LE3OrbitCamera.get_offset(self) end

---@param self LE3OrbitCamera
---@return number
---@return number
---@return number
function LE3OrbitCamera.get_origin(self) end

---@param self LE3OrbitCamera
---@param offset number
function LE3OrbitCamera.set_offset(self, offset) end

---@param self LE3OrbitCamera
---@param origin_x number
---@param origin_y number
---@param origin_z number
function LE3OrbitCamera.set_origin(self, origin_x, origin_y, origin_z) end

---@param obj LE3PointCloud
---@param position_x number
---@param position_y number
---@param position_z number
---@param normal_x number
---@param normal_y number
---@param normal_z number
function LE3PointCloud.add_point(obj, position_x, position_y, position_z, normal_x, normal_y, normal_z) end

---@param obj LE3PointCloud
function LE3PointCloud.create(obj) end

---@param self LE3PointCloud
---@param point_size number
function LE3PointCloud.set_point_size(self, point_size) end

---@param self LE3PointLight
---@return number
function LE3PointLight.get_attn_const(self) end

---@param self LE3PointLight
---@return number
function LE3PointLight.get_attn_exp(self) end

---@param self LE3PointLight
---@return number
function LE3PointLight.get_attn_linear(self) end

---@param self LE3PointLight
---@param attn_const number
function LE3PointLight.set_attn_const(self, attn_const) end

---@param self LE3PointLight
---@param attn_exp number
function LE3PointLight.set_attn_exp(self, attn_exp) end

---@param self LE3PointLight
---@param attn_linear number
function LE3PointLight.set_attn_linear(self, attn_linear) end

---@param scene LE3Scene
---@param name string
function LE3Scene.add_ambient_light(scene, name) end

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
---@param materialName string
---@param position_x number
---@param position_y number
---@param position_z number
---@param radius number
---@param height number
---@param resolution number
---@param withCaps boolean
function LE3Scene.add_cone(scene, name, materialName, position_x, position_y, position_z, radius, height, resolution, withCaps) end

---@param scene LE3Scene
---@param name string
---@param materialName string
---@param position_x number
---@param position_y number
---@param position_z number
---@param radius number
---@param height number
---@param resolution number
---@param withCaps boolean
function LE3Scene.add_cylinder(scene, name, materialName, position_x, position_y, position_z, radius, height, resolution, withCaps) end

---@param scene LE3Scene
---@param name string
function LE3Scene.add_directional_light(scene, name) end

---@param scene LE3Scene
---@param name string
function LE3Scene.add_empty_object(scene, name) end

---@param scene LE3Scene
---@param name string
function LE3Scene.add_free_camera(scene, name) end

---@param scene LE3Scene
---@param name string
function LE3Scene.add_orbit_camera(scene, name) end

---@param scene LE3Scene
---@param name string
---@param materialName string
function LE3Scene.add_point_cloud(scene, name, materialName) end

---@param scene LE3Scene
---@param name string
function LE3Scene.add_point_light(scene, name) end

---@param scene LE3Scene
---@param name string
---@param classname string
function LE3Scene.add_script_object(scene, name, classname) end

---@param scene LE3Scene
---@param name string
---@param meshName string
---@param materialName string
function LE3Scene.add_skeletal_model(scene, name, meshName, materialName) end

---@param scene LE3Scene
---@param name string
function LE3Scene.add_spot_light(scene, name) end

---@param scene LE3Scene
---@param name string
---@param textureName string
function LE3Scene.add_sprite(scene, name, textureName) end

---@param scene LE3Scene
---@param name string
---@param meshName string
---@param materialName string
function LE3Scene.add_static_model(scene, name, meshName, materialName) end

---@param scene LE3Scene
---@param name string
---@param materialName string
---@param position_x number
---@param position_y number
---@param position_z number
---@param majorRadius number
---@param minorRadius number
---@param resolution number
function LE3Scene.add_torus(scene, name, materialName, position_x, position_y, position_z, majorRadius, minorRadius, resolution) end

---@param self LE3Scene
---@return number
---@return number
---@return number
function LE3Scene.get_background_color(self) end

---@param scene LE3Scene
---@param name string
---@return LE3Object
function LE3Scene.get_object(scene, name) end

---@param scene LE3Scene
---@param child string
---@param parent string
function LE3Scene.reparent(scene, child, parent) end

---@param self LE3Scene
---@param background_color_x number
---@param background_color_y number
---@param background_color_z number
function LE3Scene.set_background_color(self, background_color_x, background_color_y, background_color_z) end

---@param self LE3Scene
---@param culling boolean
function LE3Scene.set_culling(self, culling) end

---@param scene LE3Scene
---@param camera string
function LE3Scene.set_main_camera(scene, camera) end

---@param shaderName string
---@return string
---@return string
function LE3Shader.get_error(shaderName) end

---@param shaderName string
---@return string
function LE3Shader.get_name(shaderName) end

---@param shaderName string
---@return boolean
---@return boolean
function LE3Shader.is_ok(shaderName) end

---@param shaderName string
function LE3Shader.recompile(shaderName) end

---@param shaderName string
---@param name string
function LE3Shader.set_name(shaderName, name) end

---@param shaderName string
---@param vertexShaderPath string
---@param fragmentShaderPath string
function LE3Shader.set_shader_paths(shaderName, vertexShaderPath, fragmentShaderPath) end

---@param self LE3SkeletalModel
---@return string
function LE3SkeletalModel.get_current_animation(self) end

---@param self LE3SkeletalModel
---@return string
function LE3SkeletalModel.get_material_name(self) end

---@param self LE3SkeletalModel
---@return string
function LE3SkeletalModel.get_mesh_name(self) end

---@param self LE3SkeletalModel
---@return boolean
function LE3SkeletalModel.is_animation_playing(self) end

---@param self LE3SkeletalModel
function LE3SkeletalModel.reset_animation(self) end

---@param self LE3SkeletalModel
---@param animation_playing boolean
function LE3SkeletalModel.set_animation_playing(self, animation_playing) end

---@param self LE3SkeletalModel
---@param current_animation string
function LE3SkeletalModel.set_current_animation(self, current_animation) end

---@param self LE3SkeletalModel
---@param material_name string
function LE3SkeletalModel.set_material_name(self, material_name) end

---@param self LE3SkeletalModel
---@param mesh_name string
function LE3SkeletalModel.set_mesh_name(self, mesh_name) end

---@param light LE3SpotLight
---@param resolution number
function LE3SpotLight.add_shadow_map(light, resolution) end

---@param self LE3SpotLight
---@return number
function LE3SpotLight.get_cutoff(self) end

---@param self LE3SpotLight
---@return number
function LE3SpotLight.get_outer_cutoff(self) end

---@param self LE3SpotLight
---@return boolean
function LE3SpotLight.has_shadow_map(self) end

---@param self LE3SpotLight
---@param cutoff number
function LE3SpotLight.set_cutoff(self, cutoff) end

---@param self LE3SpotLight
---@param outer_cutoff number
function LE3SpotLight.set_outer_cutoff(self, outer_cutoff) end

---@param meshName string
---@return string
function LE3StaticMesh.get_mesh_path(meshName) end

---@param meshName string
function LE3StaticMesh.get_name(meshName) end

---@param meshName string
---@param path string
---@param keepData boolean
function LE3StaticMesh.reload_mesh(meshName, path, keepData) end

---@param meshName string
---@param path string
function LE3StaticMesh.set_mesh_path(meshName, path) end

---@param meshName string
---@param name string
function LE3StaticMesh.set_name(meshName, name) end

---@param self LE3StaticModel
---@return string
function LE3StaticModel.get_material_name(self) end

---@param self LE3StaticModel
---@return string
function LE3StaticModel.get_mesh_name(self) end

---@param self LE3StaticModel
---@param material_name string
function LE3StaticModel.set_material_name(self, material_name) end

---@param self LE3StaticModel
---@param mesh_name string
function LE3StaticModel.set_mesh_name(self, mesh_name) end

---@param textureName string
function LE3Texture.get_interpolate(textureName) end

---@param textureName string
function LE3Texture.get_name(textureName) end

---@param textureName string
---@return string
function LE3Texture.get_texture_path(textureName) end

---@param textureName string
---@param path string
---@param interpolate boolean
function LE3Texture.reload_texture(textureName, path, interpolate) end

---@param textureName string
---@param interpolate boolean
function LE3Texture.set_interpolate(textureName, interpolate) end

---@param textureName string
---@param name string
function LE3Texture.set_name(textureName, name) end

---@param textureName string
---@param path string
function LE3Texture.set_texture_path(textureName, path) end

---@param self LE3Torus
---@return number
function LE3Torus.get_major_radius(self) end

---@param self LE3Torus
---@return number
function LE3Torus.get_minor_radius(self) end

---@param self LE3Torus
---@return number
function LE3Torus.get_resolution(self) end

---@param self LE3Torus
---@return number
function LE3Torus.get_x0(self) end

---@param self LE3Torus
---@return number
function LE3Torus.get_y0(self) end

---@param self LE3Torus
---@return number
function LE3Torus.get_z0(self) end

---@param self LE3Transform
---@return number
---@return number
---@return number
function LE3Transform.get_position(self) end

---@param self LE3Transform
---@return number
---@return number
---@return number
---@return number
function LE3Transform.get_rotation(self) end

---@param self LE3Transform
---@return number
---@return number
---@return number
function LE3Transform.get_scale(self) end

---@param self LE3Transform
---@param position_x number
---@param position_y number
---@param position_z number
function LE3Transform.set_position(self, position_x, position_y, position_z) end

---@param self LE3Transform
---@param rotation_w number
---@param rotation_x number
---@param rotation_y number
---@param rotation_z number
function LE3Transform.set_rotation(self, rotation_w, rotation_x, rotation_y, rotation_z) end

---@param self LE3Transform
---@param scale_x number
---@param scale_y number
---@param scale_z number
function LE3Transform.set_scale(self, scale_x, scale_y, scale_z) end

---@param position_x number
---@param position_y number
---@param position_z number
---@param rotation_w number
---@param rotation_x number
---@param rotation_y number
---@param rotation_z number
---@param scale_x number
---@param scale_y number
---@param scale_z number
---@param color_x number
---@param color_y number
---@param color_z number
function LE3VisualDebug.draw_debug_box(position_x, position_y, position_z, rotation_w, rotation_x, rotation_y, rotation_z, scale_x, scale_y, scale_z, color_x, color_y, color_z) end

---@param start_x number
---@param start_y number
---@param start_z number
---@param end_x number
---@param end_y number
---@param end_z number
---@param color_x number
---@param color_y number
---@param color_z number
function LE3VisualDebug.draw_debug_line(start_x, start_y, start_z, end_x, end_y, end_z, color_x, color_y, color_z) end

