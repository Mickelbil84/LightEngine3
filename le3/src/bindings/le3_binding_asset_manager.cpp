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

LIB(LE3AssetManager,
    add_shader, get_shader_paths,
    add_texture, has_texture,
    add_material, has_material,
    add_static_mesh, has_static_mesh,
    add_skeletal_mesh, add_skeletal_animation
)