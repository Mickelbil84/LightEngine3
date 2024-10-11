#include "le3_script_bindings.h"
#include "le3_engine_systems.h"
using namespace le3;


FBIND(LE3Material, set_diffuse_color)
    GET_STRING(materialName)
    GET_VEC4(color)
    std::shared_ptr<LE3Material> material = LE3GetAssetManager().getMaterial(materialName).lock();
    if (!material) FBREAK();
    material->diffuseColor = color;
FEND()
FBIND(LE3Material, get_diffuse_color)
    GET_STRING(materialName)
    std::shared_ptr<LE3Material> material = LE3GetAssetManager().getMaterial(materialName).lock();
    if (!material) FBREAK();
    PUSH_VEC4(material->diffuseColor)
FEND()

FBIND(LE3Material, set_diffuse_texture)
    GET_STRING(materialName)
    std::shared_ptr<LE3Material> material = LE3GetAssetManager().getMaterial(materialName).lock();
    GET_STRING(textureName)
    std::shared_ptr<LE3Texture> texture = LE3GetAssetManager().getTexture(textureName).lock();
    if (!material) FBREAK();
    material->diffuseTexture = texture;
    material->bUseDiffuseTexture = (texture != nullptr);
FEND()
FBIND(LE3Material, null_diffuse_texture)
    GET_STRING(materialName)
    std::shared_ptr<LE3Material> material = LE3GetAssetManager().getMaterial(materialName).lock();
    if (!material) FBREAK();
    material->diffuseTexture.reset();
    material->bUseDiffuseTexture = false;
FEND()
FBIND(LE3Material, get_diffuse_texture)
    GET_STRING(materialName)
    std::shared_ptr<LE3Material> material = LE3GetAssetManager().getMaterial(materialName).lock();
    if (!material) FBREAK();

    std::shared_ptr<LE3Texture> texture = material->diffuseTexture.lock();
    if (texture) {PUSH_STRING(texture->getName())}
    else { PUSH_STRING("")}
FEND()


FBIND(LE3Material, set_specular_color)
    GET_STRING(materialName)
    std::shared_ptr<LE3Material> material = LE3GetAssetManager().getMaterial(materialName).lock();
    if (!material) FBREAK();
    GET_VEC3(color)
    material->specularColor = color;
FEND()
FBIND(LE3Material, get_specular_color)
    GET_STRING(materialName)
    std::shared_ptr<LE3Material> material = LE3GetAssetManager().getMaterial(materialName).lock();
    if (!material) FBREAK();
    PUSH_VEC3(material->specularColor)
FEND()

FBIND(LE3Material, set_specular_intensity)
    GET_STRING(materialName)
    std::shared_ptr<LE3Material> material = LE3GetAssetManager().getMaterial(materialName).lock();
    if (!material) FBREAK();
    GET_NUMBER(val)
    material->specularIntensity = val;
FEND()
FBIND(LE3Material, get_specular_intensity)
    GET_STRING(materialName)
    std::shared_ptr<LE3Material> material = LE3GetAssetManager().getMaterial(materialName).lock();
    if (!material) FBREAK();
    PUSH_NUMBER(material->specularIntensity)
FEND()

FBIND(LE3Material, set_shininess)
    GET_STRING(materialName)
    std::shared_ptr<LE3Material> material = LE3GetAssetManager().getMaterial(materialName).lock();
    if (!material) FBREAK();
    GET_NUMBER(val)
    material->shininess = val;
FEND()
FBIND(LE3Material, get_shininess)
    GET_STRING(materialName)
    std::shared_ptr<LE3Material> material = LE3GetAssetManager().getMaterial(materialName).lock();
    if (!material) FBREAK();
    PUSH_NUMBER(material->shininess)
FEND()

FBIND(LE3Material, set_specular_texture)
    GET_STRING(materialName)
    std::shared_ptr<LE3Material> material = LE3GetAssetManager().getMaterial(materialName).lock();
    if (!material) FBREAK();
    GET_STRING(textureName)
    std::shared_ptr<LE3Texture> texture = LE3GetAssetManager().getTexture(textureName).lock();
    material->specularTexture = texture;
    material->bUseSpecularTexture = (texture != nullptr);
FEND()
FBIND(LE3Material, get_specular_texture)
    GET_STRING(materialName)
    std::shared_ptr<LE3Material> material = LE3GetAssetManager().getMaterial(materialName).lock();
    if (!material) FBREAK();
    std::shared_ptr<LE3Texture> texture = material->specularTexture.lock();
    if (texture) {PUSH_STRING(texture->getName())}
    else { PUSH_STRING("")}
FEND()
FBIND(LE3Material, null_specular_texture)
    GET_STRING(materialName)
    std::shared_ptr<LE3Material> material = LE3GetAssetManager().getMaterial(materialName).lock();
    if (!material) FBREAK();
    material->specularTexture.reset();
    material->bUseSpecularTexture = false;
FEND()

FBIND(LE3Material, set_normal_texture)
    GET_STRING(materialName)
    std::shared_ptr<LE3Material> material = LE3GetAssetManager().getMaterial(materialName).lock();
    if (!material) FBREAK();
    GET_STRING(textureName)
    std::shared_ptr<LE3Texture> texture = LE3GetAssetManager().getTexture(textureName).lock();
    material->normalTexture = texture;
    material->bUseNormalTexture = (texture != nullptr);
FEND()
FBIND(LE3Material, get_normal_texture)
    GET_STRING(materialName)
    std::shared_ptr<LE3Material> material = LE3GetAssetManager().getMaterial(materialName).lock();
    if (!material) FBREAK();

    std::shared_ptr<LE3Texture> texture = material->normalTexture.lock();
    if (texture) {PUSH_STRING(texture->getName())}
    else { PUSH_STRING("")}
FEND()
FBIND(LE3Material, null_normal_texture)
    GET_STRING(materialName)
    std::shared_ptr<LE3Material> material = LE3GetAssetManager().getMaterial(materialName).lock();
    if (!material) FBREAK();
    material->normalTexture.reset();
    material->bUseNormalTexture = false;
FEND()

FBIND(LE3Material, set_cubemap)
    GET_STRING(materialName)
    std::shared_ptr<LE3Material> material = LE3GetAssetManager().getMaterial(materialName).lock();
    if (!material) FBREAK();
    GET_STRING(textureName)
    std::shared_ptr<LE3Texture> texture = LE3GetAssetManager().getTexture(textureName).lock();
    material->cubemap = texture;
FEND()
FBIND(LE3Material, get_cubemap)
    GET_STRING(materialName)
    std::shared_ptr<LE3Material> material = LE3GetAssetManager().getMaterial(materialName).lock();
    if (!material) FBREAK();

    std::shared_ptr<LE3Texture> texture = material->cubemap.lock();
    if (texture) {PUSH_STRING(texture->getName())}
    else { PUSH_STRING("")}
FEND()
FBIND(LE3Material, null_cubemap)
    GET_STRING(materialName)
    std::shared_ptr<LE3Material> material = LE3GetAssetManager().getMaterial(materialName).lock();
    if (!material) FBREAK();
    material->cubemap.reset();
FEND()

FBIND(LE3Material, set_reflection_intensity)
    GET_STRING(materialName)
    std::shared_ptr<LE3Material> material = LE3GetAssetManager().getMaterial(materialName).lock();
    if (!material) FBREAK();
    GET_NUMBER(val)
    material->reflectionIntensity = val;
FEND()
FBIND(LE3Material, get_reflection_intensity)
    GET_STRING(materialName)
    std::shared_ptr<LE3Material> material = LE3GetAssetManager().getMaterial(materialName).lock();
    if (!material) FBREAK();
    PUSH_NUMBER(material->reflectionIntensity)
FEND()

FBIND(LE3Material, set_tiling)
    GET_STRING(materialName)
    std::shared_ptr<LE3Material> material = LE3GetAssetManager().getMaterial(materialName).lock();
    if (!material) FBREAK();
    GET_NUMBER(x)
    GET_NUMBER(y)
    material->tilingX = x; material->tilingY = y;
FEND()
FBIND(LE3Material, get_tiling)
    GET_STRING(materialName)
    std::shared_ptr<LE3Material> material = LE3GetAssetManager().getMaterial(materialName).lock();
    if (!material) FBREAK();
    PUSH_NUMBER(material->tilingX)
    PUSH_NUMBER(material->tilingY)
FEND()

FBIND(LE3Material, get_name)
    GET_STRING(materialName)
    std::shared_ptr<LE3Material> material = LE3GetAssetManager().getMaterial(materialName).lock();
    if (!material) FBREAK();
    PUSH_STRING(material->name)
FEND()

FBIND(LE3Material, get_shader)
    GET_STRING(materialName)
    std::shared_ptr<LE3Material> material = LE3GetAssetManager().getMaterial(materialName).lock();
    if (!material) FBREAK();

    std::shared_ptr<LE3Shader> shader = material->shader.lock();
    if (shader) {PUSH_STRING(shader->getName())}
    else { PUSH_STRING("") }
FEND()
FBIND(LE3Material, set_shader)
    GET_STRING(materialName)
    GET_STRING(shaderName)
    std::shared_ptr<LE3Material> material = LE3GetAssetManager().getMaterial(materialName).lock();
    if (!material) FBREAK();
    if (!LE3AssetManager().hasShader(shaderName)) {
        // material->shader.reset();
        FBREAK();
    }
    material->shader = LE3AssetManager().getShader(shaderName);
FEND()

LIB(LE3Material,
    get_name, get_shader, set_shader,
    set_diffuse_color, get_diffuse_color,
    set_diffuse_texture, get_diffuse_texture, null_diffuse_texture,
    set_specular_color, get_specular_color,
    set_specular_intensity, get_specular_intensity,
    set_shininess, get_shininess,
    set_specular_texture, get_specular_texture, null_specular_texture,
    set_normal_texture, get_normal_texture, null_normal_texture,
    set_cubemap, get_cubemap, null_cubemap,
    set_reflection_intensity, get_reflection_intensity,
    set_tiling, get_tiling
)