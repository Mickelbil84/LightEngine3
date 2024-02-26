#include "le3_script_bindings.h"
#include "le3_engine_systems.h"
using namespace le3;


FBIND(LE3Material, set_diffuse_color)
    GET_UDATA(material, LE3MaterialPtr)
    GET_VEC4(color)
    (*material)->diffuseColor = color;
FEND()
FBIND(LE3Material, get_diffuse_color)
    GET_UDATA(material, LE3MaterialPtr)
    PUSH_VEC4((*material)->diffuseColor)
FEND()

FBIND(LE3Material, set_diffuse_texture)
    GET_UDATA(material, LE3MaterialPtr)
    GET_UDATA(texture, LE3TexturePtr)
    (*material)->diffuseTexture = *texture;
    (*material)->bUseDiffuseTexture = (texture != nullptr);
FEND()
FBIND(LE3Material, get_diffuse_texture)
    GET_UDATA(material, LE3MaterialPtr)
    PUSH_UDATA(&((*material)->diffuseTexture), LE3TexturePtr)
FEND()


FBIND(LE3Material, set_specular_color)
    GET_UDATA(material, LE3MaterialPtr)
    GET_VEC3(color)
    (*material)->specularColor = color;
FEND()
FBIND(LE3Material, get_specular_color)
    GET_UDATA(material, LE3MaterialPtr)
    PUSH_VEC3((*material)->specularColor)
FEND()

FBIND(LE3Material, set_specular_intensity)
    GET_UDATA(material, LE3MaterialPtr)
    GET_NUMBER(val)
    (*material)->specularIntensity = val;
FEND()
FBIND(LE3Material, get_specular_intensity)
    GET_UDATA(material, LE3MaterialPtr)
    PUSH_NUMBER((*material)->specularIntensity)
FEND()

FBIND(LE3Material, set_shininess)
    GET_UDATA(material, LE3MaterialPtr)
    GET_NUMBER(val)
    (*material)->shininess = val;
FEND()
FBIND(LE3Material, get_shininess)
    GET_UDATA(material, LE3MaterialPtr)
    PUSH_NUMBER((*material)->shininess)
FEND()

FBIND(LE3Material, set_specular_texture)
    GET_UDATA(material, LE3MaterialPtr)
    GET_UDATA(texture, LE3TexturePtr)
    (*material)->specularTexture = *texture;
    (*material)->bUseSpecularTexture = (texture != nullptr);
FEND()
FBIND(LE3Material, get_specular_texture)
    GET_UDATA(material, LE3MaterialPtr)
    PUSH_UDATA(&((*material)->specularTexture), LE3TexturePtr)
FEND()

FBIND(LE3Material, set_normal_texture)
    GET_UDATA(material, LE3MaterialPtr)
    GET_UDATA(texture, LE3TexturePtr)
    (*material)->normalTexture = *texture;
    (*material)->bUseNormalTexture = (texture != nullptr);
FEND()
FBIND(LE3Material, get_normal_texture)
    GET_UDATA(material, LE3MaterialPtr)
    PUSH_UDATA(&((*material)->normalTexture), LE3TexturePtr)
FEND()

FBIND(LE3Material, set_cubemap)
    GET_UDATA(material, LE3MaterialPtr)
    GET_UDATA(texture, LE3TexturePtr)
    (*material)->cubemap = *texture;
FEND()
FBIND(LE3Material, get_cubemap)
    GET_UDATA(material, LE3MaterialPtr)
    PUSH_UDATA(&((*material)->cubemap), LE3TexturePtr)
FEND()

FBIND(LE3Material, set_reflection_intensity)
    GET_UDATA(material, LE3MaterialPtr)
    GET_NUMBER(val)
    (*material)->reflectionIntensity = val;
FEND()
FBIND(LE3Material, get_reflection_intensity)
    GET_UDATA(material, LE3MaterialPtr)
    PUSH_NUMBER((*material)->reflectionIntensity)
FEND()

FBIND(LE3Material, set_tiling)
    GET_UDATA(material, LE3MaterialPtr)
    GET_NUMBER(x)
    GET_NUMBER(y)
    (*material)->tilingX = x; (*material)->tilingY = y;
FEND()
FBIND(LE3Material, get_tiling)
    GET_UDATA(material, LE3MaterialPtr)
    PUSH_NUMBER((*material)->tilingX)
    PUSH_NUMBER((*material)->tilingY)
FEND()

LIB(LE3Material,
    set_diffuse_color, get_diffuse_color,
    set_diffuse_texture, get_diffuse_texture,
    set_specular_color, get_specular_color,
    set_specular_intensity, get_specular_intensity,
    set_shininess, get_shininess,
    set_specular_texture, get_specular_texture,
    set_normal_texture, get_normal_texture,
    set_cubemap, get_cubemap,
    set_reflection_intensity, get_reflection_intensity,
    set_tiling, get_tiling
)