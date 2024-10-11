#include "le3_shader.h"
#include "le3_engine_systems.h"
using namespace le3;

#include <stdexcept>

#include <fmt/core.h>

#ifdef __linux__
#include <GL/glew.h>
#else
#include <gl/glew.h>
#endif
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>


LE3Shader::LE3Shader(std::string vertexShaderSource, std::string fragmentShaderSource) {
    recompile(vertexShaderSource, fragmentShaderSource);
}
LE3Shader::~LE3Shader() {
    glDeleteProgram(m_program);
}

std::pair<bool, std::string> LE3Shader::recompile(std::string vertexShaderSource, std::string fragmentShaderSource) {
    m_uniformLocation.clear();
    unsigned int vertexShader = compileShaderFromSource(vertexShaderSource, GL_VERTEX_SHADER, m_shaderOk, m_errorMessage);
    if (!m_shaderOk) {
        recompileToErrorShader();
        // TODO: Use logging system
        fmt::print("{}\n", m_errorMessage);
        return std::make_pair(false, m_errorMessage);
    }
    unsigned int fragmentShader = compileShaderFromSource(fragmentShaderSource, GL_FRAGMENT_SHADER, m_shaderOk, m_errorMessage);
    if (!m_shaderOk) {
        recompileToErrorShader();
        // TODO: Use logging system
        fmt::print("{}\n", m_errorMessage);
        return std::make_pair(false, m_errorMessage);
    }

    m_program = glCreateProgram();
    glAttachShader(m_program, vertexShader);
    glAttachShader(m_program, fragmentShader);
    glLinkProgram(m_program);

    int status;
    glGetProgramiv(m_program, GL_LINK_STATUS, &status);
    if (status != GL_TRUE) {
        char infoLog[2048];
        glGetProgramInfoLog(m_program, 2048, nullptr, infoLog);
        recompileToErrorShader();
        // TODO: Use logging system
        m_shaderOk = false;
        m_errorMessage = fmt::format("Link error:\n\n{}\n", infoLog);
        fmt::print("{}\n", m_errorMessage);
        return std::make_pair(false, m_errorMessage);
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    m_shaderOk = true;
    m_errorMessage = "";
    return std::make_pair(true, "");
}

void LE3Shader::recompile() {
    recompileToErrorShader();
}

void LE3Shader::use() const{
    glUseProgram(m_program);
}

void LE3Shader::uniform(std::string uniformName, glm::vec3 v) {
    glUniform3f(getUniformLocation(uniformName), v.x, v.y, v.z);
}
void LE3Shader::uniform(std::string uniformName, glm::vec4 v) {
    glUniform4f(getUniformLocation(uniformName), v.x, v.y, v.z, v.w);
}
void LE3Shader::uniform(std::string uniformName, glm::mat4 m) {
    glUniformMatrix4fv(getUniformLocation(uniformName), 1, GL_FALSE, glm::value_ptr(m));
}
void LE3Shader::uniform(std::string uniformName, unsigned int i) {
    glUniform1i(getUniformLocation(uniformName), i);
}
void LE3Shader::uniform(std::string uniformName, float x) {
    glUniform1f(getUniformLocation(uniformName), x);
}

unsigned int LE3Shader::compileShaderFromSource(std::string shaderSource, int type, bool& success, std::string& error) {
    const char* shaderSource_cstr = shaderSource.c_str();

    unsigned int shader = glCreateShader(type);
    glShaderSource(shader, 1, & shaderSource_cstr, nullptr);
    glCompileShader(shader);

    int status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if (status != GL_TRUE) {
        char infoLog[2048];
        glGetShaderInfoLog(shader, 2048, nullptr, infoLog);
        success = false;
        error = fmt::format("Compile error:\n\n{}\n", infoLog);
        return 0;
    }
    success = true;
    error = "";
    return shader;
}
int LE3Shader::getUniformLocation(std::string uniformName) {
    if (!m_uniformLocation.contains(uniformName)) 
        m_uniformLocation[uniformName] = glGetUniformLocation(m_program, uniformName.c_str());
    return m_uniformLocation[uniformName];
}

void LE3Shader::recompileToErrorShader() {
    std::string prevErr = m_errorMessage;
    recompile(
        LE3GetDatFileSystem().getFileContent(ERROR_SHADER_VERTEX_PATH).toString(),
        LE3GetDatFileSystem().getFileContent(ERROR_SHADER_FRAGMENT_PATH).toString()
    );
    m_errorMessage = prevErr;
    m_shaderOk = false;
}