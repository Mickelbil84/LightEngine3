#include "le3_script_bindings.h"
#include "le3_engine_systems.h"
using namespace le3;

FBIND_ASSET_GETTER_STRING(LE3Shader, get_name, getName)
FBIND_ASSET_SETTER_STRING(LE3Shader, set_name, setName)

LIB(LE3Shader, 
    get_name, set_name
)