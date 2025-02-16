#include "le3_script_bindings.h"
#include "le3_engine_systems.h"
using namespace le3;


FBIND(LE3AssetManager, add_shader) 
    GET_STRING(name)
    GET_STRING(vertexSource)
    GET_STRING(fragmentSource)
    LE3GetAssetManager().addShaderFromFile(name, vertexSource, fragmentSource);
FEND()
FBIND(LE3AssetManager, get_shader_paths) 
    GET_STRING(shaderName)
    LE3ShaderPtr shader = LE3GetAssetManager().getShader(shaderName);
    if (shader.expired()) {
        PUSH_STRING("")
        PUSH_STRING("")
        FBREAK();
    }
    std::pair<std::string, std::string> paths = LE3GetAssetManager().getShadersPaths()[shader.lock()->getName()];
    PUSH_STRING(paths.first)
    PUSH_STRING(paths.second)
FEND()
FBIND(LE3AssetManager, get_shaders)
    std::vector<std::string> shaderNames, shaderVSPaths, shaderFSPaths;
    for (auto& [name, v] : LE3GetAssetManager().getShaders()) {
        if (name.starts_with(DEFAULT_ENGINE_PREFIX)) continue;
        shaderNames.push_back(name);
        std::pair<std::string, std::string> paths = LE3GetAssetManager().getShadersPaths()[name];
        shaderVSPaths.push_back(paths.first);
        shaderFSPaths.push_back(paths.second);
    }
    PUSH_STRING_ARRAY(shaderNames)
    PUSH_STRING_ARRAY(shaderVSPaths)
    PUSH_STRING_ARRAY(shaderFSPaths)
FEND()

FBIND(LE3AssetManager, add_texture)
    GET_STRING(name)
    GET_STRING(filename)
    GET_BOOL(interpolate)
    LE3GetAssetManager().addTexture(name, filename, interpolate);
FEND()
FBIND(LE3AssetManager, has_texture)
    GET_STRING(name)
    PUSH_BOOL(LE3GetAssetManager().hasTexture(name))
FEND()

FBIND(LE3AssetManager, add_material)
    GET_STRING(name)
    GET_STRING(shaderName)
    LE3GetAssetManager().addMaterial(name, shaderName);
FEND()

FBIND(LE3AssetManager, has_material)
    GET_STRING(name)
    PUSH_BOOL(LE3GetAssetManager().hasMaterial(name))
FEND()

FBIND(LE3AssetManager, add_static_mesh)
    GET_STRING(name)
    GET_STRING(filename)
    GET_BOOL(keepData)
    LE3GetAssetManager().addStaticMesh(name, filename, keepData);
FEND()

FBIND(LE3AssetManager, has_static_mesh)
    GET_STRING(name)
    PUSH_BOOL(LE3GetAssetManager().hasStaticMesh(name))
FEND()

FBIND(LE3AssetManager, add_skeletal_mesh)
    GET_STRING(name)
    GET_STRING(filename)
    LE3GetAssetManager().addSkeletalMesh(name, filename);
FEND()

FBIND(LE3AssetManager, add_skeletal_animation)
    GET_STRING(name)
    GET_STRING(animationPath)
    GET_STRING(meshName)
    LE3GetAssetManager().addSkeletalAnimation(name, animationPath, meshName);
FEND()

FBIND(LE3AssetManager, has_skeletal_mesh)
    GET_STRING(name)
    PUSH_BOOL(LE3GetAssetManager().hasSkeletalMesh(name))
FEND()

LIB(LE3AssetManager,
    add_shader, get_shader_paths, get_shaders,
    add_texture, has_texture,
    add_material, has_material,
    add_static_mesh, has_static_mesh,
    add_skeletal_mesh, add_skeletal_animation, has_skeletal_mesh
)