#include "le3_script_bindings.h"
#include "le3_engine_systems.h"
using namespace le3;


FBIND(LE3Shader, get_name)
    GET_STRING(shaderName)
    LE3ShaderPtr shader = LE3GetAssetManager().getShader(shaderName);
    PUSH_STRING(shader.lock()->getName())
FEND()
FBIND(LE3Shader, set_name)
    GET_STRING(shaderName)
    GET_STRING(name)
    LE3ShaderPtr shader = LE3GetAssetManager().getShader(shaderName);
    shader.lock()->setName(name);
FEND()

LIB(LE3Shader, 
    get_name, set_name
)