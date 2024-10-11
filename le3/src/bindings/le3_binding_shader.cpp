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

FBIND(LE3Shader, set_shader_paths)
    GET_STRING(shaderName)
    GET_STRING(vertexShaderPath)
    GET_STRING(fragmentShaderPath)
    LE3GetAssetManager().setShaderPaths(shaderName, vertexShaderPath, fragmentShaderPath);
FEND()

FBIND(LE3Shader, recompile)
    GET_STRING(shaderName)
    std::pair<std::string, std::string> p = LE3GetAssetManager().getShaderPaths(shaderName);
    std::shared_ptr<LE3Shader> shader = LE3GetAssetManager().getShader(shaderName).lock();
    try {
        std::string vertexShaderSource = LE3GetDatFileSystem().getFileContent(p.first).toString();
        std::string fragmentShaderSource = LE3GetDatFileSystem().getFileContent(p.second).toString();
        shader->recompile(vertexShaderSource, fragmentShaderSource);
    }
    catch (std::exception& e) {
        fmt::print("Error recompiling shader [{}]: {}\n", shaderName, e.what());
        shader->recompile();
    }
FEND()

FBIND(LE3Shader, is_ok)
    GET_STRING(shaderName)
    LE3ShaderPtr shader = LE3GetAssetManager().getShader(shaderName);
    PUSH_BOOL(shader.lock()->isOk())
FEND()

FBIND(LE3Shader, get_error) 
    GET_STRING(shaderName)
    LE3ShaderPtr shader = LE3GetAssetManager().getShader(shaderName);
    PUSH_STRING(shader.lock()->getErrorMessage())
FEND()

LIB(LE3Shader, 
    get_name, set_name,
    set_shader_paths, recompile,
    is_ok, get_error
)