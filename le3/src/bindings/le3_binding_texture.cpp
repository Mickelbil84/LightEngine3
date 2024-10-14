#include "le3_script_bindings.h"
#include "le3_engine_systems.h"
using namespace le3;


FBIND(LE3Texture, set_name)
    GET_STRING(textureName)
    GET_STRING(name)
    LE3GetAssetManager().renameTexture(textureName, name);
FEND()

FBIND(LE3Texture, get_name)
    GET_STRING(textureName)
    std::shared_ptr<LE3Texture> texture = LE3GetAssetManager().getTexture(textureName).lock();
    if (!texture) {PUSH_STRING("")}
    else {PUSH_STRING(texture->getName())}
FEND()

FBIND(LE3Texture, reload_texture)
    GET_STRING(textureName)
    GET_STRING(path)
    GET_BOOL(interpolate)
    LE3GetAssetManager().reloadTexture(textureName, path, interpolate);
FEND()

FBIND(LE3Texture, get_texture_path)
    GET_STRING(textureName)
    PUSH_STRING(LE3GetAssetManager().getTexturePath(textureName))
FEND()
FBIND(LE3Texture, set_texture_path)
    GET_STRING(textureName)
    GET_STRING(path)
    LE3GetAssetManager().setTexturePath(textureName, path);
FEND()

FBIND(LE3Texture, get_interpolate)
    GET_STRING(textureName)
    std::shared_ptr<LE3Texture> texture = LE3GetAssetManager().getTexture(textureName).lock();
    if (!texture) {PUSH_BOOL(false)}
    else {PUSH_BOOL(texture->getInterpolate())}
FEND()

FBIND(LE3Texture, set_interpolate)
    GET_STRING(textureName)
    GET_BOOL(interpolate)
    std::shared_ptr<LE3Texture> texture = LE3GetAssetManager().getTexture(textureName).lock();
    if (!texture) {FBREAK();}
    texture->setInterpolate(interpolate);
FEND()

LIB(LE3Texture,
    get_name, set_name,
    get_texture_path, set_texture_path,
    get_interpolate, set_interpolate,
    reload_texture
)
