#include "le3_script_bindings.h"
#include "le3_engine_systems.h"
using namespace le3;


FBIND(LE3Texture, set_name)
    GET_STRING(textureName)
    GET_STRING(name)
    std::shared_ptr<LE3Texture> texture = LE3GetAssetManager().getTexture(textureName).lock();
    if (!texture) {FBREAK();}
    texture->setName(name);
FEND()

FBIND(LE3Texture, get_name)
    GET_STRING(textureName)
    std::shared_ptr<LE3Texture> texture = LE3GetAssetManager().getTexture(textureName).lock();
    if (!texture) {PUSH_STRING("")}
    else {PUSH_STRING(texture->getName())}
FEND()

LIB(LE3Texture,
    get_name, set_name
)
