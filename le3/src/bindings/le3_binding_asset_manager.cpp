#include "le3_script_bindings.h"
#include "le3_engine_systems.h"
using namespace le3;


FBIND(LE3AssetManager, add_shader) 
    GET_STRING(name)
    GET_STRING(vertexSource)
    GET_STRING(fragmentSource)
    LE3GetAssetManager().addShaderFromFile(name, vertexSource, fragmentSource);
FEND()
FBIND(LE3AssetManager, get_shader)
    GET_STRING(name)
    LE3ShaderPtr& shader = LE3GetAssetManager().getShader(name);
    PUSH_UDATA(&shader, LE3ShaderPtr)
FEND()

FBIND(LE3AssetManager, add_texture)
    GET_STRING(name)
    GET_STRING(filename)
    GET_BOOL(interpolate)
    LE3GetAssetManager().addTexture(name, filename, interpolate);
FEND()
FBIND(LE3AssetManager, get_texture)
    GET_STRING(name)
    LE3TexturePtr& texture = LE3GetAssetManager().getTexture(name);
    PUSH_UDATA(&texture, LE3TexturePtr)
FEND()

FBIND(LE3AssetManager, add_material)
    GET_STRING(name)
    GET_STRING(shaderName)
    LE3GetAssetManager().addMaterial(name, shaderName);
FEND()
FBIND(LE3AssetManager, get_material)
    GET_STRING(name)
    LE3MaterialPtr& texture = LE3GetAssetManager().getMaterial(name);
    PUSH_UDATA(&texture, LE3MaterialPtr)
FEND()

FBIND(LE3AssetManager, add_static_mesh)
    GET_STRING(name)
    GET_STRING(filename)
    GET_BOOL(keepData)
    LE3GetAssetManager().addStaticMesh(name, filename, keepData);
FEND()
FBIND(LE3AssetManager, get_static_mesh)
    GET_STRING(name)
    LE3StaticMeshPtr& mesh = LE3GetAssetManager().getStaticMesh(name);
    PUSH_UDATA(&mesh, LE3StaticMeshPtr)
FEND()

FBIND(LE3AssetManager, add_skeletal_mesh)
    GET_STRING(name)
    GET_STRING(filename)
    LE3GetAssetManager().addSkeletalMesh(name, filename);
FEND()
FBIND(LE3AssetManager, get_skeletal_mesh)
    GET_STRING(name)
    LE3SkeletalMeshPtr& mesh = LE3GetAssetManager().getSkeletalMesh(name);
    PUSH_UDATA(&mesh, LE3SkeletalMeshPtr)
FEND()
FBIND(LE3AssetManager, add_skeletal_animation)
    GET_STRING(name)
    GET_STRING(animationPath)
    GET_STRING(meshName)
    LE3GetAssetManager().addSkeletalAnimation(name, animationPath, meshName);
FEND()

LIB(LE3AssetManager,
    add_shader, get_shader,
    add_texture, get_texture,
    add_material, get_material,
    add_static_mesh, get_static_mesh,
    add_skeletal_mesh, get_skeletal_mesh, add_skeletal_animation
)