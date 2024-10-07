#include "le3_script_bindings.h"
#include "le3_engine_systems.h"
using namespace le3;


FBIND_ASSET_SETTER_STRING(LE3Texture, set_name, setName)

FBIND(LE3Texture, get_name)
    GET_UDATA(texture, LE3TexturePtr)
    if (!(*texture)) {PUSH_STRING("")}
    else {PUSH_STRING((*texture)->getName())}
FEND()

LIB(LE3Texture,
    get_name, set_name
)
