#include "le3_shader.h"
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
    unsigned int vertexShader = compileShaderFromSource(vertexShaderSource, GL_VERTEX_SHADER);
    unsigned int fragmentShader = compileShaderFromSource(fragmentShaderSource, GL_FRAGMENT_SHADER);

    m_program = glCreateProgram();
    glAttachShader(m_program, vertexShader);
    glAttachShader(m_program, fragmentShader);
    glLinkProgram(m_program);

    int status;
    glGetProgramiv(m_program, GL_LINK_STATUS, &status);
    if (status != GL_TRUE) {
        char infoLog[2048];
        glGetProgramInfoLog(m_program, 2048, nullptr, infoLog);
        throw std::runtime_error(fmt::format("Link error:\n\n{}\n", infoLog));
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}
LE3Shader::~LE3Shader() {
    glDeleteProgram(m_program);
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

unsigned int LE3Shader::compileShaderFromSource(std::string shaderSource, int type) {
    const char* shaderSource_cstr = shaderSource.c_str();

    unsigned int shader = glCreateShader(type);
    glShaderSource(shader, 1, & shaderSource_cstr, nullptr);
    glCompileShader(shader);

    int status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if (status != GL_TRUE) {
        char infoLog[2048];
        glGetShaderInfoLog(shader, 2048, nullptr, infoLog);
        throw std::runtime_error(fmt::format("Compile error:\n\n{}\n", infoLog));
    }
    return shader;
}
int LE3Shader::getUniformLocation(std::string uniformName) {
    if (!m_uniformLocation.contains(uniformName)) 
        m_uniformLocation[uniformName] = glGetUniformLocation(m_program, uniformName.c_str());
    return m_uniformLocation[uniformName];
}